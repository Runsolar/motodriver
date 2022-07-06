// This file is part of the Motodriver project.
//
// Copyright (c) 2022 Institute of Control Sciences RAS.
//
// Feel free to use, copy, modify, merge, and publish this software

#pragma once

/**
* @brief Supporting Drivers:    
* L298N 2X Motor Shield, 
* Other.
*/
typedef enum {
    L298N = 1, 
    OTHER = 0
} ShieldDriversNames;

/**
 * @brief Supporting directions: 
 * Forward, Backward, Shutdown
 */
typedef enum {
    FORWARD = 0, 
    BACKWARD = 1,
    SHUTDOWN = -1
} MoveDirection;