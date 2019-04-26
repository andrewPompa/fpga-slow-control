#!/bin/sh

DEV=/dev/ttyUSB1

stty -F $DEV 115200
rz > $DEV < $DEV
