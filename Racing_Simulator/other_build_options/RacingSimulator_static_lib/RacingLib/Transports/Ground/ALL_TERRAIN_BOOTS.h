#pragma once
#include "GROUND.h"

class BOOTS : public GROUND {
public:
	BOOTS();
	int raceTime(float _distance) override;
protected:
	BOOTS(int _speed, int _wayToRest, int _restTime, int _quantityOfRests);
};