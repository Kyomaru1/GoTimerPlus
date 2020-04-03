#include <nds.h>
#include <stdio.h>
#include "TimerSystem.h"

Time::Time(int hours, int minutes, int seconds)
{
    setTime(hours, minutes, seconds);
}

Time::~Time()
{
    delete &this -> hours;
    delete &this -> minutes;
    delete &this -> seconds;
    delete &this -> vblankConsumed;
}
