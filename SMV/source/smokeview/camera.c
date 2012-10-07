// $Date$ 
// $Revision$
// $Author$

// svn revision character string
char camera_revision[]="$Revision$";

#include "options.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "string_util.h"
#include "smokeviewvars.h"

/* ------------------ zoom2aperture ------------------------ */

float zoom2aperture(float zoom0){
  float ap;
  // note tan(46*PI/360)~(W/2)/D  where W=17==monitor width
  //                                D=20==distance from eye to monitor
  // (rounded off to 45 degrees)

  ap = 2.0*RAD2DEG*atan(tan(45.0*DEG2RAD/2.0)/zoom0);
  return ap;
}

/* ------------------ aperture2zoom ------------------------ */

float aperture2zoom(float ap){
  float zoom0;
  zoom0 = tan(45.0*DEG2RAD/2.0)/tan(ap*DEG2RAD/2.0);
  return zoom0;
}

/* ------------------ init_camera_list ------------------------ */

void init_camera_list(void){
  camera *cb, *ca;

  if(init_camera_list_flag==0)return;
  cb=&camera_list_first;
  ca=&camera_list_last;
  init_camera(cb,"first");
  init_camera(ca,"last");

  cb->prev=NULL;
  cb->next=ca;

  ca->prev=cb;
  ca->next=NULL;
  init_camera_list_flag=0;

}

/* ------------------ add_default_views ------------------------ */

void add_default_views(void){
  camera *cb, *ca;

  cb=&camera_list_first;
  ca=cb->next;

  cb->next=camera_external;
  camera_external->next=camera_internal;
  camera_internal->next=ca;

  ca->prev=camera_internal;
  camera_internal->prev=camera_external;
  camera_external->prev=cb;
}

/* ------------------ update_camera_ypos ------------------------ */

void update_camera_ypos(camera *camera_data){
  float local_aperture_default;
  float width;
  float asp;
  
  local_aperture_default=zoom2aperture(1.0);
  asp=(float)screenHeight/(float)screenWidth;
  width=xbar;
  if(zbar/asp>xbar){
    width=zbar/asp;
  }
  eyeyfactor = -1.10*width/2.0/tan(local_aperture_default*DEG2RAD/2.0);
  camera_data->eye[1]=eyeyfactor*xyzbox;
  if(viscolorbarpath==1){
    camera_data->eye[0]=0.7;
    camera_data->eye[1]=-2.25;
    camera_data->eye[2]=0.5;
  }
  camera_data->isometric_y=(eyeyfactor-1.0)*xyzbox;
}

/* ------------------ init_camera ------------------------ */

void init_camera(camera *camera_data,char *name){
  float *x;
  int i;

  strcpy(camera_data->name,name);
  camera_data->rotation_index=nmeshes;
  camera_data->defined=1;
  camera_data->azimuth=0.0;
  camera_data->view_angle=0.0;
  camera_data->eye[0]=eyexfactor*xbar;
  update_camera_ypos(camera_data);
  camera_data->eye[2]=eyezfactor*zbar;
  camera_data->eye_save[0]=camera_data->eye[0];
  camera_data->eye_save[1]=camera_data->eye[1];
  camera_data->eye_save[2]=camera_data->eye[2];
  camera_data->quat_defined=0;
  camera_data->quaternion[0]=1.0;
  camera_data->quaternion[0]=0.0;
  camera_data->quaternion[0]=0.0;
  camera_data->quaternion[0]=0.0;

  x=camera_data->modelview;
  for(i=0;i<16;i++){
    x[i]=0.0;
  }
  for(i=0;i<16;i+=5){
    x[i]=1.0;
  }
  camera_data->az_elev[0]=0.0;
  camera_data->az_elev[1]=0.0;
  camera_data->up[0]=0.0;
  camera_data->up[1]=0.0;
  camera_data->up[2]=1.0;
  camera_data->view[0]=0.0;
  camera_data->view[1]=0.0;
  camera_data->view[2]=0.0;
  camera_data->xcen=xbar/2.0;
  camera_data->ycen=ybar/2.0;
  camera_data->zcen=zbar/2.0;
  camera_data->rotation_type=rotation_type;

  camera_data->azimuth=0.0;
  camera_data->cos_azimuth=1.0;
  camera_data->sin_azimuth=0.0;

  camera_data->elevation=0.0;
  camera_data->cos_elevation=1.0;
  camera_data->sin_elevation=0.0;

  camera_data->view_angle=0.0;
  camera_data->cos_view_angle=1.0;
  camera_data->sin_view_angle=0.0;
  camera_data->next=NULL;
  camera_data->prev=NULL;
  camera_data->view_id=-1;
  camera_data->zoom=1.0;
  camera_data->projection_type=projection_type;
  camera_data->dirty=0;

  clip2cam(camera_data);
}

/* ------------------ clip2cam ------------------------ */

  void clip2cam(camera *cam){
    cam->xyz_clipplane=xyz_clipplane;
    cam->clip_x=clip_x;
    cam->clip_y=clip_y;
    cam->clip_z=clip_z;
  
    cam->clip_X=clip_X;
    cam->clip_Y=clip_Y;
    cam->clip_Z=clip_Z;

    cam->clip_x_val=clip_x_val;
    cam->clip_y_val=clip_y_val;
    cam->clip_z_val=clip_z_val;

    cam->clip_X_val=clip_X_val;
    cam->clip_Y_val=clip_Y_val;
    cam->clip_Z_val=clip_Z_val;
  }


/* ------------------ clip2cam ------------------------ */

  void cam2clip(camera *cam){
    xyz_clipplane = cam->xyz_clipplane;
    clip_x = cam->clip_x;
    clip_y = cam->clip_y;
    clip_z = cam->clip_z;
  
    clip_X = cam->clip_X;
    clip_Y = cam->clip_Y;
    clip_Z = cam->clip_Z;

    clip_x_val = cam->clip_x_val;
    clip_y_val = cam->clip_y_val;
    clip_z_val = cam->clip_z_val;

    clip_X_val = cam->clip_X_val;
    clip_Y_val = cam->clip_Y_val;
    clip_Z_val = cam->clip_Z_val;
    Update_Glui_Clip();

  }

/* ------------------ copy_camera ------------------------ */

void copy_camera(camera *to, camera *from){

  memcpy(to,from,sizeof(camera));
  if(to==camera_current){
    zoom=camera_current->zoom;
    update_glui_zoom();
  }
  to->dirty=1;
  if(to==camera_current&&updateclipvals==0){
    cam2clip(camera_current);
  }
  if(to==camera_current&&to->quat_defined==1){
    quat_general[0]=to->quaternion[0];
    quat_general[1]=to->quaternion[1];
    quat_general[2]=to->quaternion[2];
    quat_general[3]=to->quaternion[3];
  }
}

/* ------------------ update_camera ------------------------ */

void update_camera(camera *ca){
  float local_angle;

  local_angle = ca->azimuth*DEG2RAD;
  ca->cos_azimuth=cos(local_angle);
  ca->sin_azimuth=sin(local_angle);

  local_angle = ca->view_angle*DEG2RAD;
  ca->cos_view_angle=cos(local_angle);
  ca->sin_view_angle=sin(local_angle);

  local_angle = ca->elevation*DEG2RAD;
  ca->cos_elevation=cos(local_angle);
  ca->sin_elevation=sin(local_angle);

  if(ca==camera_current){
    rotation_type=ca->rotation_type;
    if(ca->rotation_index>=0&&ca->rotation_index<nmeshes){
      update_current_mesh(meshinfo + ca->rotation_index);
    }
    else{
      update_current_mesh(meshinfo);
    }
    highlight_mesh = current_mesh-meshinfo;
    handle_rotation_type(EYE_CENTERED);
    update_meshlist1(ca->rotation_index);
    update_trainer_moves();

    ca->xyz_clipplane=xyz_clipplane;
    ca->clip_x=clip_x;
    ca->clip_y=clip_y;
    ca->clip_z=clip_z;
  
    ca->clip_x_val=clip_x_val;
    ca->clip_y_val=clip_y_val;
    ca->clip_z_val=clip_z_val;

    ca->clip_X_val=clip_X_val;
    ca->clip_Y_val=clip_Y_val;
    ca->clip_Z_val=clip_Z_val;
  }
  update_glui_set_view_xyz(ca->eye);
  ca->dirty=0;
}

/* ------------------ set_camera_current ------------------------ */

void set_camera_current(float angles[2], float eye[3], float zzoom){
  float azimuth, elevation;
  float eyex, eyey, eyez;
  char name_current[32];

  strcpy(name_current,"current");
  init_camera(camera_current,name_current);

  azimuth = angles[0];
  elevation = angles[1];
  eyex = eye[0];
  eyey = eye[1];
  eyez = eye[2];

  camera_current->azimuth=azimuth;
  camera_current->view_angle=0.0;
  camera_current->elevation=elevation;

  camera_current->eye[0]=eyex;
  camera_current->eye[1]=eyey;
  camera_current->eye[2]=eyez;

  camera_current->rotation_type=EYE_CENTERED;

  camera_current->zoom=zzoom;

  update_camera(camera_current);
}

/* ------------------ insert_camera ------------------------ */

camera *insert_camera(camera *cb,camera *source, char *name){
  camera *cam,*ca;

  for(ca=camera_list_first.next;ca->next!=NULL;ca=ca->next){
    if(strcmp(ca->name,name)==0)return NULL;
  }

  if(NewMemory((void **)&cam,sizeof(camera))==0)return NULL;
  init_camera(cam,name);
  if(source!=NULL){
    copy_camera(cam,source);
  }
  strcpy(cam->name,name);
  ca=cb->next;
  cb->next=cam;
  ca->prev=cam;
  cam->prev=cb;
  cam->next=ca;
  cam->view_id=camera_max_id;
  camera_max_id++;
  updatemenu=1;
  return cam;
}

/* ------------------ delete_camera ------------------------ */

void delete_camera(camera *cam){
  camera *ca, *cb;

  cb=cam->prev;
  ca=cam->next;
  cb->next=ca;
  ca->prev=cb;
  FREEMEMORY(cam);
  updatemenu=1;
}

/* ------------------ get_camera ------------------------ */

camera *get_camera(char *name){
  camera *ca;

  for(ca=camera_list_first.next;ca->next!=NULL;ca=ca->next){
    if(strcmp(ca->name,name)==0){
      return ca;
    }
  }
  return NULL;
}

/* ------------------ get_camera_label ------------------------ */

char *get_camera_label(int index){
  camera *ca;

  for(ca=camera_list_first.next;ca->next!=NULL;ca=ca->next){
    if(ca->view_id==index){
      return ca->name;
    }
  }
  return NULL;
}
