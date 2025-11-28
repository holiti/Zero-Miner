#include <iostream>
#include <thread>
#include <chrono>
#include "GUI.h"
#include "Game.h"
#include "EVL.h"

Game game;
GUI window;
EVL evloop;

int32_t main(){
    while(1){
        window.Rander();
        evloop.process();

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
}
