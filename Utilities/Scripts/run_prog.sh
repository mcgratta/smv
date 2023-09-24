#!/bin/bash
EXE=$1
input=$2

LOCKBASE=`whoami`_fdslock
LOCKFILE=/tmp/${input}_${LOCKBASE}$$

NPROCS=`grep processor /proc/cpuinfo | wc -l`
NJOBS=`ls -l /tmp/*${LOCKBASE}* | wc -l`

while [ $NJOBS -gt $NPROCS ]; do
 sleep 10
done
sleep 1

touch $LOCKFILE
$EXE $input
rm -f $LOCKFILE
