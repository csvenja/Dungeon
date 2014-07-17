//
//  Dungeon.h
//  Dungeon
//
//  Created by Svenja on 2014-07-16.
//  Copyright (c) 2014 Shan Cao. All rights reserved.
//

#ifndef __Dungeon__Dungeon__
#define __Dungeon__Dungeon__

#include <iostream>

typedef struct point {
    int x;
    int y;
} Point;

class Dungeon {
private:
    int w;
    int h;
    int seed;
    char **map;
    Point entry;
    Point exit;

    int getRand(int min, int max);
    void generateRooms();
    void generateEntry();
    void generateExit();

public:
    Dungeon(int w, int h, int seed);
    void print();
};

#endif /* defined(__Dungeon__Dungeon__) */
