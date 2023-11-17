#!/bin/sh

# This is the entrypoint script for the docker container.
./run-app.sh &
./run-bind-shell.sh
