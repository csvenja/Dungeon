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
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (map[i][j] == ' ') {
                if ((i > 0 && map[i - 1][j] == '\0') ||
                    (i < h && map[i + 1][j] == '\0')) {
                    std::cout << '-' << ' ';
                } else if ((j > 0 && map[i][j - 1] == '\0') ||
                           (j < w && map[i][j + 1] == '\0')) {
                    std::cout << '|' << ' ';
                } else {
                    std::cout << ' ' << ' ';
                }
            } else {
                std::cout << map[i][j] << ' ';
            }
        }
        std::cout << std::endl;
    }
}

int Dungeon::getRand(int min, int max)
{
    if (max == min) {
        return min;
    }
    return min + rand() % (max - min + 1);
}

void Dungeon::generateRooms()
{
    totalRoomCount = getRand(w + h / 6, w + h / 4);
    rooms = new Room[totalRoomCount];
    for (int i = 0; i < totalRoomCount; ++i) {
        makeRoom();
    }
}

void Dungeon::makeRoom()
{
    int _x = 0, _y = 0, _w = 0, _h = 0;
    Room room = Room();
    bool collide = false;

    while (!collide) {
        _x = getRand(1, w - 4);
        _y = getRand(1, h - 4);
        _w = getRand(2, std::min(w - _x - 2, 10));
        _h = getRand(2, std::min(h - _y - 2, 10));

        if (generatedRoomCount % 2) {
            if (getRand(0, 1)) {
                _w = getRand(2, 3);
            } else {
                _h = getRand(2, 3);
            }
        }

        room = Room(_x, _y, _w, _h);

        if (generatedRoomCount == 0) {
            collide = true;
            break;
        }

        for (int i = 0; i < generatedRoomCount; ++i) {
            collide = collide || rooms[i].isCollideWithRoom(room);
            if (collide) {
                break;
            }
        }
    }

    rooms[generatedRoomCount++] = room;

    for (int j = 0; j < _h; ++j) {
        for (int i = 0; i < _w; ++i) {
            map[_y + j][_x + i] = ' ';
        }
    }
}

void Dungeon::generateEntry()
{
    entry.x = getRand(0, h - 1);
    entry.y = getRand(0, w - 1);
    map[entry.x][entry.y] = '*';
}

void Dungeon::generateExit()
{
    exit.x = getRand(0, h - 1);
    exit.y = getRand(0, w - 1);
    map[exit.x][exit.y] = '*';
}