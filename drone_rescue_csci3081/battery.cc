/**
 * @file battery.cc
 * @author Jinwei Zhang (zhan7075@umn.edu)
 * @brief battery for decorator EDrone .cc
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "battery.h"

Battery::Battery(){}

Battery::~Battery(){}

int Battery::getPercentage(){
    return currentPercentage;
}

void Battery::chargeTo(const int percentage) {
    currentPercentage = percentage;
}