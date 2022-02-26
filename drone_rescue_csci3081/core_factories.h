/**
 * @file core_factories.h
 * @author Jinwei Zhang zhan7075@umn.edu
 * @brief 
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CORE_FACTORIES_H_
#define CORE_FACTORIES_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "web_app.h"
#include "core_entities.h"
#include "vector3.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class EntityFactory {
public:
    /**
     * @brief Construct a new Entity Factory object
     * 
     */
    EntityFactory();
    /**
     * @brief Destroy the Entity Factory object
     * 
     */
    ~EntityFactory();
    /**
     * @brief Create a Entity object
     * 
     * @param entityData 
     * @return Entity* 
     */
    Entity* createEntity(picojson::object& entityData);

    //
};
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class DroneFactory : public EntityFactory {
public:
    /**
     * @brief Construct a new Drone Factory object
     * 
     */
    DroneFactory();
    /**
     * @brief Destroy the Drone Factory object
     * 
     */
    ~DroneFactory();
    /**
     * @brief Create a Entity object
     * 
     * @param entityData 
     * @return Entity* 
     */
    Entity* createEntity(picojson::object& entityData);

};
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class RobotFactory : public EntityFactory {
public:
    /**
     * @brief Construct a new Robot Factory object
     * 
     */
    RobotFactory();
    /**
     * @brief Destroy the Robot Factory object
     * 
     */
    ~RobotFactory();
    /**
     * @brief Create a Entity object
     * 
     * @param entityData 
     * @return Entity* 
     */
    Entity* createEntity(picojson::object& entityData);
};
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class RechargeStationFactory : public EntityFactory {
public:
    /**
     * @brief Construct a new Recharge Station Factory object
     * 
     */
    RechargeStationFactory();
    /**
     * @brief Destroy the Recharge Station Factory object
     * 
     */
    ~RechargeStationFactory();
    /**
     * @brief Create a Entity object
     * 
     * @param entityData 
     * @return Entity* 
     */
    Entity* createEntity(picojson::object& entityData);
};
#endif
