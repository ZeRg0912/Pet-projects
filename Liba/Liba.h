#pragma once
#include <iostream>

bool CinCheck(auto in, std::string type) {
	if (&typeid(in).name == type.c_str()) return true;
	else return false;
}