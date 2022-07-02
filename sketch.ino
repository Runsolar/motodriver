// This file is part of the Motodriver project.
//
// Copyright (c) 2022 Institute of Control Sciences RAS.
//
// Feel free to use, copy, modify, merge, and publish this software

#include "Motodriver.h"

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	ShieldDriver.clockWise(255, 1);
    ShieldDriver.clockWise(255, 2);
}