#!/bin/bash
DEV=/dev/ttyUSB1
tty -F $DEV 115200
sz $1 > $DEV < $DEV
