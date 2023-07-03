#!/bin/bash

sudo docker build -t graphics_engine .
# docker run --rm -it -e --env="Display" --net=host  graphics_engine

sudo docker run -it --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix --net=host graphics_engine