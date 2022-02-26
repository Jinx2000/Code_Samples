/**
 * @file battery.h
 * @author Jinwei Zhang (zhan7075@umn.edu)
 * @brief battery for decorator EDrone .h
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef BATTERY_H_
#define BATTERY_H_
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Battery {
public:
    /**
     * @brief Construct a new Battery object
     * 
     */
    Battery();
    /**
     * @brief Destroy the Battery object
     * 
     */
    ~Battery();
    /**
     * @brief charge the battery to <percentage>
     * 
     * @param percentage 
     */
    void chargeTo(const int percentage);
    /**
     * @brief Get the Percentage object
     * 
     * @return int 
     */
    int getPercentage();

protected:
    int currentPercentage = 100;
};
#endif