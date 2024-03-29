#pragma once
#include "GROUND.h"

class CAMEL : public GROUND {
public:
	CAMEL();
	float raceTime(float _distance) override;
protected:
	CAMEL(int _speed, int _wayToRest, int _restTime, int _quantityOfRests);
};