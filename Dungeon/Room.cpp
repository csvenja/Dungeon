//
//  Room.cpp
//  Dungeon
//
//  Created by Svenja on 2014-07-17.
//  Copyright (c) 2014 Shan Cao. All rights reserved.
//

#include "Room.h"

Room::Room()
{}

Room::Room(int x, int y, int w, int h) : x(x), y(y), w(w), h(h)
{}

bool isCollide(int start1, int length1, int start2, int length2)
{
    int end1 = start1 + length1 - 1;
    int end2 = start2 + length2 - 1;

    if ((start2 > start1 && start2 < end1) ||
        (end2 > start1 && end2 < end1)) {
        return true;
    }
    
    return false;
}

bool Room::isCollideHorizontal(Room &room)
{
    return isCollide(x, w, room.getX(), room.getW());
}

bool Room::isCollideVertical(Room &room)
{
    return isCollide(y, h, room.getY(), room.getH());
}

bool Room::isCollideWithRoom(Room &room)
{
    if (isCollideHorizontal(room) &&
        isCollideVertical(room)) {
        return true;
    }
    return false;
}

int Room::getX()
{
    return x;
}

int Room::getY()
{
    return y;
}

int Room::getW()
{
    return w;
}

int Room::getH()
{
    return h;
}