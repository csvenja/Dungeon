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

bool isCollide(int start1, int end1, int start2, int end2)
{
    if ((start2 >= start1 && start2 <= end1) ||
        (end2 >= start1 && end2 <= end1)) {
        return true;
    }
    return false;
}

bool Room::isCollideWithRoom(Room &room)
{
    if (isCollide(x, x + w - 1, room.getX(), room.getX() + room.getW() - 1) &&
        isCollide(y, y + h - 1, room.getY(), room.getY() + room.getH() - 1)) {
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