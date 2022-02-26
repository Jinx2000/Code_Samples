/**
 * @file battery_pack.cc
 * @author Jinwei Zhang (zhan7075@umn.edu)
 * @brief composite battery .cc
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "battery_pack.h"

BatteryPack::BatteryPack(){}

BatteryPack::~BatteryPack(){
    for (int i = 0; i < batteries.size(); i++){
        batteries.~Battery();
    }
}

void BatteryPack::addBattery(Battery* newBattery){
    batteries.push_back(newBattery);
}

void BatteryPack::chargeTo(const int percent) {
    for (int i = 0; i < batteries.size(); i++){
        batteries.at(i)->chargeTo(percent);
    }
}

