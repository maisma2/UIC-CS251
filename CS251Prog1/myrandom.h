//
//  myrandom.h
//  RandomWriter
//
//  Created by Shanon Reckinger.
//  Copyright © 2020 Shanon Reckinger. All rights reserved.
//

#pragma once

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

bool useAutograder = true;
int seed = 15;
    
int randomInteger(int low, int high) {
    static bool initialized = false;
    if (!initialized) {
        if (useAutograder) {
            srand(seed);
            rand();
        } else {
            srand(int(time(NULL)));
            rand();   // throwaway call to get randomness going
        }
        initialized = true;
    }
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (double(high) - low + 1);
    return int(floor(low + s));
}
