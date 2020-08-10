#include <algorithm>
#include <iostream>
#include <chrono>
#include "TrafficObject.h"

// init static variable
int TrafficObject::_idCnt = 0;

std::mutex TrafficObject::mtx_;

void TrafficObject::setPosition(double x, double y)
{
    _posX = x;
    _posY = y;
}

void TrafficObject::getPosition(double &x, double &y)
{
    x = _posX;
    y = _posY;
}

TrafficObject::TrafficObject()
{
    type_ = ObjectType::noObject;
    id_ = _idCnt++;
}

TrafficObject::~TrafficObject()
{
    // set up thread barrier before this object is destroyed
    std::for_each(threads_.begin(), threads_.end(), [](std::thread &t) {
        t.join();
    });
}
