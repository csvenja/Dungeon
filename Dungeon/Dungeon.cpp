//
//  Dungeon.cpp
//  Dungeon
//
//  Created by Svenja on 2014-07-16.
//  Copyright (c) 2014 Shan Cao. All rights reserved.
//

#include "Dungeon.h"

Dungeon::Dungeon(int w, int h, int seed) : w(w), h(h), seed(seed)
{
    srand(seed);

    map = new char* [h];
    for (int i = 0; i < h; ++i) {
        map[i] = new char[w]();
    }

    generateRooms();
    generateEntry();
    generateExit();
}

void Dungeon::print()
{
    for (int j = 0; j < h; ++j) {
        for (int i = 0; i < w; ++i) {
            std::cout << map[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int Dungeon::getRand(int min, int max)
{
    return rand() % (max - min);
}

void Dungeon::generateRooms()
{
    
}

void Dungeon::generateEntry()
{
    entry.x = getRand(0, w);
    entry.y = getRand(0, h);
}

void Dungeon::generateExit()
{
    exit.x = getRand(0, w);
    exit.y = getRand(0, h);
}