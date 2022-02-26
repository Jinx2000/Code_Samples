#ifndef SIMULATION_H_
#define SIMULATION_H_
/**
 * @file simulation.h
 * @author Jinwei Zhang (zhan7075@umn.edu)
 * @brief simulation facade .h
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "core_factories.h"
#include "core_entities.h"
#include "web_app.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Simulation {
public:
    /**
     * @brief Construct a new Simulation object
     * 
     */
    Simulation();
    /**
     * @brief Destroy the Simulation object
     * 
     */
    ~Simulation();
    /**
     * @brief Create a Entity object
     * 
     * @param data 
     * @return Entity* 
     */
    Entity* createEntity(const picojson::object& data);
    /**
     * @brief call the drone's update function with dt passed down
     * 
     * @param dt 
     */
    void update(double dt);
    /**
     * @brief communicate with front end using returnValue
     * 
     * @param returnValue 
     */
    void finishUpdate(picojson::object& returnValue);

    Drone* drone;
    Vector3* destination;

};

#endif