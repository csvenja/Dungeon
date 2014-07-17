//
//  main.cpp
//  Dungeon
//
//  Created by Svenja on 2014-07-16.
//  Copyright (c) 2014 Shan Cao. All rights reserved.
//

#include <iostream>
#include "Dungeon.h"

int main(int argc, const char * argv[])
{
    int w = 0, h = 0;
    int seed = 0;

	if (argc > 1) {
		seed = atoi(argv[2]);
	}

    const int kMinWidth = 4;
    const int kMinHeight = 4;

    while (w < kMinWidth || h < kMinHeight) {
        std::cout << "input w: ";
        std::cin >> w;
        std::cout << "input h: ";
        std::cin >> h;

        if (w < kMinWidth || h < kMinHeight) {
            std::cout << "Too small for dungeon.";
        }
    }

    Dungeon dungeon(w, h, seed);
    dungeon.print();

    return 0;
}

