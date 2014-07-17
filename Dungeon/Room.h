//
//  Room.h
//  Dungeon
//
//  Created by Svenja on 2014-07-17.
//  Copyright (c) 2014 Shan Cao. All rights reserved.
//

#ifndef __Dungeon__Room__
#define __Dungeon__Room__

#include <iostream>

class Room {
    int x;
    int y;
    int w;
    int h;
public:
    Room();
    Room(int x, int y, int w, int h);
    bool isCollideWithRoom(Room& room);
    int getX();
    int getY();
    int getW();
    int getH();
};

#endif /* defined(__Dungeon__Room__) */
