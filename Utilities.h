#pragma once
#include <iostream>

float GetRandom() {
	return (rand() / (RAND_MAX + 1.0));
}