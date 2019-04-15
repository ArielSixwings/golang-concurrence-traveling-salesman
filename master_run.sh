#!/bin/bash
# chmod +x run.sh   para tornar run.sh executavel

go run process.go
./app >imagegraph.txt
./a.out <imagegraph.txt >path.txt
./app finaly <path.txt

