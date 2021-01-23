#pragma once
#include<iostream>
#include <string>
#include "testStep.h"

#ifndef TEST_H
#define TEST_H

class test
{
public:
	std::string name;
	int amountSteps;
	testStep steps[100];
};
#endif

// 800 pulses per Revolution
// 1 Revolution is 0.3cm
// 1 pulse is 0.000375cm