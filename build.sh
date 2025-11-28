#!/bin/sh

if [ ! -d "./data" ]; then
    mkdir data
    cd data
    touch map.bin
    touch game.bin
    cd ..
fi
    

cd src/
g++ Game.cpp EVL.cpp GUI.cpp constant.cpp main.cpp -o ../tmpmain

cd ..

#./tmptest
