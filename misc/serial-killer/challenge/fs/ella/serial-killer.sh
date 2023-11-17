#!/bin/sh

set -e

$HOME/serial-killer/bin/app $*
wait $!