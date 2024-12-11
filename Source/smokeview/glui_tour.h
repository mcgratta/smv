#ifndef IGLUI_TOUR_H_DEFINED
#define IGLUI_TOUR_H_DEFINED

#define TOUR_CLOSE 99
#define KEYFRAME_tXYZ 1
#define KEYFRAME_INSERT 2
#define KEYFRAME_DELETE 3
#define KEYFRAME_PREVIOUS 4
#define KEYFRAME_NEXT 5
#define SAVE_SETTINGS_TOUR 7
#define SHOWTOURROUTE 8
#define VIEWTOURFROMPATH 9
#define VIEWTOURFROMPATH1 41
#ifdef pp_TOUR
#define TOUR_CONSTANT_VELOCITY 46
#endif
#define VIEWTOURFROMPATH2 42
#define TOUR_SNAP 43
#define SHOWTOURROUTE1 39
#define SHOWTOURROUTE2 40
#define TOUR_INSERT_NEW 32
#define TOUR_INSERT_COPY 33
#define TOUR_PREVIOUS 17
#define TOUR_NEXT 18
#define TOUR_DELETE 34
#define TOUR_LABEL 19
#define TOUR_HIDE 20
#define KEYFRAME_viewXYZ 22
#define VIEW_ALL_NODES 44
#define VIEW_NEXT_NODE 45
#define TOUR_LIST 24
#define TOUR_AVATAR 31
#define VIEW1 26
#define VIEW_times 27
#define TOUR_UPDATELABEL 28
#define TOUR_USECURRENT 29
#define TOUR_REVERSE 35
#define TOUR_CIRCULAR_UPDATE 36
#define KEYFRAME_UPDATE_ALL 38

#define TOURMENU(f) callfrom_tourglui=1;TourMenu(f);callfrom_tourglui=0;

#define SETTINGS_TOURS_ROLLOUT 0
#define KEYFRAME_TOURS_ROLLOUT 1
#define MODIFY_TOURS_ROLLOUT 2

#endif

