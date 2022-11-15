#!/bin/sh
clear
cc pong.c `pkg-config --libs --cflags raylib` -o pong
./pong