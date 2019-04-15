#!/bin/bash
# chmod +x path.sh   para tornar run.sh executavel
g++ Paths.cpp -o app `pkg-config --cflags --libs opencv`
