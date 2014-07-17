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

bool Dungeon::isCorner(int i, int j)
{
    return false;
}

bool Dungeon::isVertical(int i, int j)
{
    return (i > 0 && map[i - 1][j] == '\0') || (i < h && map[i + 1][j] == '\0');
}

bool Dungeon::isHorizontal(int i, int j)
{
    return (j > 0 && map[i][j - 1] == '\0') || (j < w && map[i][j + 1] == '\0');
}

void Dungeon::print()
{
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (map[i][j] == ' ') {
                if (isVertical(i, j)) {
                    std::cout << '-' << ' ';
                } else if (isHorizontal(i, j)) {
                    std::cout << '|' << ' ';
                } else if (isCorner(i, j)) {
                    std::cout << '-' << ' ';
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
    totalRoomCount = getRand((w + h) / 7, (w + h) / 5);
    rooms = new Room [totalRoomCount];

    for (int i = 0; i < totalRoomCount; ++i) {
        makeRoom();
        connectLastRoom();
    }
}

void Dungeon::makeRoom()
{
    const int MIN_WIDTH = 5;
    int x = getRand(1, w - MIN_WIDTH - 2);
    int y = getRand(1, h - MIN_WIDTH - 2);
    int _w = getRand(MIN_WIDTH, std::min(w - x - 2, 10));
    int _h = getRand(MIN_WIDTH, std::min(h - y - 2, 10));

    rooms[generatedRoomCount] = Room(x, y, _w, _h);
    generatedRoomCount++;
    setMap(x, y, _w, _h);
}

void Dungeon::setMap(int x, int y, int w, int h)
{
    for (int j = 0; j < h; ++j) {
        for (int i = 0; i < w; ++i) {
            map[y + j][x + i] = ' ';
        }
    }
}

void Dungeon::connectLastRoom()
{
    if (generatedRoomCount == 1) {
        return;
    }

    for (int i; i < generatedRoomCount - 1; ++i) {
        if (rooms[i].isCollideWithRoom(rooms[generatedRoomCount - 1])) {
            return;
        }
    }

    makeRoad(generatedRoomCount - 1, getRand(0, generatedRoomCount - 2));
}

Overlap getOverlap(int start1, int length1, int start2, int length2)
{
    Overlap overlap;

    if (start1 < start2) {
        overlap.start = start2;
        overlap.end = start1 + length1 - 1;
    } else {
        overlap.start = start1;
        overlap.end = start2 + length2 - 1;
    }

    return overlap;
}

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void Dungeon::makeRoad(int a, int b)
{
    int roadX = 0, roadY = 0, roadLength = 0;

    if (rooms[a].isCollideHorizontal(rooms[b])) {
        if (rooms[a].getY() > rooms[b].getY()) {
            swap(a, b);
        }

        Overlap overlap = getOverlap(rooms[a].getX(), rooms[a].getW(), rooms[b].getX(), rooms[b].getW());

        if (overlap.end - overlap.start >= 2) {
            roadX = getRand(overlap.start, overlap.end - kRoadWidth + 1);
            roadY = rooms[a].getY() + rooms[a].getH();
            roadLength = rooms[b].getY() - rooms[a].getY() - rooms[a].getH();
            setMap(roadX, roadY, kRoadWidth, roadLength);
            return;
        }
    } else if (rooms[a].isCollideVertical(rooms[b])) {
        if (rooms[a].getX() > rooms[b].getX()) {
            swap(a, b);
        }

        Overlap overlap = getOverlap(rooms[a].getY(), rooms[a].getH(), rooms[b].getY(), rooms[b].getH());

        if (overlap.end - overlap.start >= 2) {
            roadX = rooms[a].getX() + rooms[a].getW();
            roadY = getRand(overlap.start, overlap.end - kRoadWidth + 1);
            roadLength = rooms[b].getX() - rooms[a].getX() - rooms[a].getW();
            setMap(roadX, roadY, roadLength, kRoadWidth);
            return;
        }
    }

    // Build L-shape road
    if (rooms[a].getX() > rooms[b].getX()) {
        swap(a, b);
    }

    int cornerX = rooms[a].getX() + rooms[a].getW() / 2;
    int cornerY = rooms[b].getY() + rooms[b].getH() / 2;
    if (rooms[a].getY() > rooms[b].getY()) {
        roadX = cornerX;
        roadY = cornerY;
        roadLength = rooms[a].getY() - cornerY;
        setMap(roadX, roadY, kRoadWidth, roadLength);
        roadLength = rooms[b].getX() - cornerX + 1;
        setMap(roadX, roadY, roadLength, kRoadWidth);
    } else {
        roadX = cornerX;
        roadY = cornerY;
        roadLength = rooms[b].getX() - cornerX;
        setMap(roadX, roadY, roadLength, kRoadWidth);
        roadY = rooms[a].getY() + rooms[a].getH() - 1;
        roadLength = cornerY - roadY + 1;
        setMap(roadX, roadY, kRoadWidth, roadLength);
    }
}

void Dungeon::generateEntry()
{
    while (true) {
        entry.x = getRand(0, h - 1);
        entry.y = getRand(0, w - 1);
        if (map[entry.x][entry.y] != '\0') {
            map[entry.x][entry.y] = '*';
            break;
        }
    }
}

void Dungeon::generateExit()
{
    while (true) {
        exit.x = getRand(0, h - 1);
        exit.y = getRand(0, w - 1);
        if (map[exit.x][exit.y] != '\0') {
            map[exit.x][exit.y] = '*';
            break;
        }
    }
}