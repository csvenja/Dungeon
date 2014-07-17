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
#include <algorithm>
#include "Room.h"

typedef struct point {
    int x;
    int y;
} Point;

typedef struct overlap {
    int start;
    int end;
} Overlap;

const int kRoadWidth = 3;

class Dungeon {
private:
    int w;
    int h;
    int seed;
    char **map;
    Point entry;
    Point exit;
    int totalRoomCount;
    int generatedRoomCount;
    Room *rooms;

    int getRand(int min, int max);
    void generateRooms();
    void makeRoom();
    void makeRoad(int a, int b);
    void setMap(int x, int y, int w, int h);
    void connectLastRoom();

    bool isCorner(int x, int y);
    bool isVertical(int x, int y);
    bool isHorizontal(int x, int y);
    void generateEntry();
    void generateExit();

public:
    Dungeon(int w, int h, int seed);
    void print();
};

#endif /* defined(__Dungeon__Dungeon__) */
