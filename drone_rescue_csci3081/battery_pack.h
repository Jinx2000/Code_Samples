/**
 * @file battery_pack.h
 * @author Jinwei Zhang (zhan7075@umn.edu)
 * @brief composite battery .h
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef BATTERY_PACK_H_
#define BATTERY_PACK_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "battery.h"
#include <iostream>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class BatteryPack : public Battery {
public:
    /**
     * @brief Construct a new Battery Pack object
     * 
     */
    BatteryPack();
    /**
     * @brief Destroy the Battery Pack object
     * 
     */
    ~BatteryPack();
    /**
     * @brief add a new battery to the batteries list (composite)
     * 
     * @param newBattery 
     */
    void addBattery(Battery* newBattery);
    /**
     * @brief charge every batteries in list to <percentage>
     * 
     * @param percentage 
     */
    void chargeTo(const int percentage);


protected:
    std::vector<Battery*> batteries;
};

#endif