// This file is part of the Motodriver project.
//
// Feel free to use, copy, modify, merge, and publish this software

#pragma once

/**
* @brief Supporting Drivers:    
* L298N 2X Motor Shield, 
* Other.
*/
typedef enum {
    MX1508 = 3,
    L298N = 2, 
    TB6612 = 1,
    OTHER = 0
} ShieldDriversNames;

/**
 * @brief Supporting directions: 
 * Forward, Backward, Shutdown
 */
typedef enum {
    CLOCKWISE = 1, 
    COUNTERCLOCKWISE = 0,
    HALT = -1
} RotorDirection;