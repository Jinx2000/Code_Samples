/**
 * @file e_decorator.cc
 * @author Jinwei Zhang (zhan7075@umn.edu)
 * @brief decorator EDrone adding on Drone .cc
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "e_decorator.h"

EDrone::EDrone(Drone* newDrone){
    drone = &newDrone;
}

EDrone::~EDrone(){}

int EDrone::getCurrentBattery(){
    return battery->getPercentage();
}

void EDrone::setBattery(const int percent) {
    battery->chargeTo(percent);
}

