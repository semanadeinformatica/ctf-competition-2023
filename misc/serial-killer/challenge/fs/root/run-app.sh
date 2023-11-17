#!/bin/sh

cd /home/ella

while true; do
    su ella --session-command '/home/ella/serial-killer.sh'
    sleep 10
done
