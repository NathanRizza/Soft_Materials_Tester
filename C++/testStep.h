#pragma once

#ifndef TESTSTEP_H
#define TESTSTEP_H

class testStep
{
public: 
	//positive is up negative is down;
	int distance;	//In pulses 
	int velocity;	// In pulse per second
	int acceleration; //In pulse per second^2
	
};
#endif

// 1600 pulses per Revolution
// 1 Revolution is 0.3cm
// 1 pulse is 0.000375cm