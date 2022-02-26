/**
 * @file e_decorator.h
 * @author Jinwei Zhang (zhan7075@umn.edu)
 * @brief decorator EDrone adding on Drone .h
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef E_DECORATOR_H_
#define E_DECORATOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "core_entities.h"
#include "battery.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class EDrone : public Drone{ // only drone can be decorated in current version
public:
    /**
     * @brief Construct a new EDrone object
     * 
     * @param newDrone 
     */
    EDrone(Drone* newDrone);
    /**
     * @brief Destroy the EDrone object
     * 
     */
    ~EDrone();
    /**
     * @brief Get the Current Battery object
     * 
     * @return int 
     */
    int getCurrentBattery();
    /**
     * @brief Set the Battery object
     * 
     * @param newPercentage 
     */
    void setBattery(const int newPercentage);
    



protected:
    Drone* drone;
    Battery* battery;
};

#endif