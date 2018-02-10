#!/bin/sh 
# based on frater's https://www.dd-wrt.com/phpBB2/viewtopic.php?t=37958
# adjusted for installation on /jffs (by Coert Vonk)
# make sure to run "chmod +x" on this script to make it executable

prefix="/jffs" 
cfg=/tmp/pound/pound.cfg 

PATH=${prefix}/bin:${prefix}/sbin:/sbin:/bin:/usr/sbin:/usr/bin 
NAME=pound 
AS_USER=pound 
DAEMON=${prefix}/sbin/${NAME} 
POUND_CTL_DIR="/tmp" 
POUNDCTL_BIN="${prefix}/sbin/poundctl" 

test -x $DAEMON || exit 0 

if [ -z "$1" ] ; then 
    case `echo "$0" | sed 's:^.*/\(.*\):\1:g'` in 
        S??*) rc="start" ;; 
        K??*) rc="stop" ;; 
        *) rc="usage" ;; 
    esac 
else 
    rc="$1" 
fi 

grep -q ${AS_USER} /etc/passwd || echo "${AS_USER}:x:33:33:${AS_USER}:/jffs:" >> /etc/passwd 
grep -q ${AS_USER} /etc/group  || echo "${AS_USER}:x:33:" >> /etc/group 

case "$rc" in 
    start) 
        echo "Writing $cfg" 
        /jffs/sbin/write_pound_cfg 
        echo "Starting $NAME" 
        if [ -n "`pidof $NAME`" ]; then 
            echo "$NAME already running" 
        else 
            if [ ! -e $cfg ]; then 
              echo "missing $cfg" 
              exit 1 
            fi 
            $DAEMON -v -f $cfg 
        fi 
        ;; 
    stop) 
        if [ -n "`pidof $NAME`" ]; then 
            echo "Stopping $NAME" 
            killall $NAME 2> /dev/null 
        else 
            echo "$NAME already stopped" 
            exit 1 
        fi 
        ;; 
    restart) 
        "$0" stop 
        sleep 1 
        "$0" start 
        ;; 
    status) 
        if [ -n "`pidof $NAME`" ]; then 
            $POUNDCTL_BIN -c /tmp/pound.ctl 
        else 
            echo "$NAME is not running" 
            exit 1 
        fi 
        ;; 
    *) 
        echo "Usage: $0 (start|stop|restart|usage|status)" 
        ;; 
esac 

exit 0 
