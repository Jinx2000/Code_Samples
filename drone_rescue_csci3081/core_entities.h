/**
 * @file core_entities.h
 * @author Jinwei Zhang (zhan7075@umn.edu)
 * @brief entity class
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef CORE_ENTITIES_H_
#define CORE_ENTITIES_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "vector3.h"
#include <cmath>
#include "Beeline.h"
#include "Patrol.h"
#include "camera.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Entity{
public:
    /**
     * @brief Construct a new Entity object
     * 
     */
    Entity();
    /**
     * @brief Destroy the Entity object
     * 
     */
    ~Entity();
    /**
     * @brief Get the Position object
     * 
     * @return Vector3* 
     */
    Vector3* getPosition(){return entityPos;}
    /**
     * @brief Get the Name object
     * 
     * @return std::string 
     */
    std::string getName(){return entityName;}
    /**
     * @brief Set the Status object
     * 
     * @param newStatus 
     */
    void setStatus(std::string newStatus){
        entityStatus = newStatus;
    }
    /**
     * @brief Set the Position object
     * 
     * @param newPos 
     */
    void setPosition(Vector3* newPos) {
        entityPos->setVector(newPos->getX(), newPos->getY(), newPos->getZ());
    }
    
    int entityID = 0;
    std::string entityName = "null";
    std::string entityType = "null";
    Vector3* entityPos = new Vector3();
    
};
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Drone : public Entity {
public:
    /**
     * @brief Construct a new Drone object
     * 
     */
    Drone();
    /**
     * @brief Destroy the Drone object
     * 
     */
    ~Drone();
    /**
     * @brief Get the Direction object
     * 
     * @return Vector3* 
     */
    Vector3* getDirection(){return droneDir;}
    /**
     * @brief Get the Speed object
     * 
     * @return double 
     */
    double getSpeed() {return speed;}
    /**
     * @brief Get the Got To Move object
     * 
     * @return int 
     */
    int getGotToMove() {return gotToMove;}
    /**
     * @brief Set the Direction object
     * 
     * @param newDir 
     */
    void setDirection(Vector3* newDir){
        droneDir->setVector(newDir->getX(), newDir->getY(), newDir->getZ());
    }
    /**
     * @brief Set the Speed object
     * 
     * @param newSpeed 
     */
    void setSpeed(double newSpeed) {
        speed = newSpeed;
    }
    /**
     * @brief return 1 if robot is found, else 0.
     * 
     * @return int 
     */
    int isRobotFound();
    /**
     * @brief update the position of drone based on the movement pattern it is using.
     * 
     * @param dt 
     * @param destination 
     * @return int 
     */
    int updatePos(double dt, Vector3* destination);
    /**
     * @brief rotate the drone to a certain direction.
     * 
     * @param angle 
     */
    void Rotate(const double angle);
    /**
     * @brief Set the Joystick object (used in manual control(no implementation))
     * 
     * @param x 
     * @param y 
     * @param z 
     * @param a 
     */
    void SetJoystick(const double x, double y, double z, double a);

protected:
    Vector3* droneDir = new Vector3();
    double speed = 0;
    std::vector<camera*> cameras;
    float lastPictureTime = 0.0;
    float time = 0;
    std::string droneStatus = "null";
};
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Robot : public Entity {
public:
    /**
     * @brief Construct a new Robot object
     * 
     */
    Robot();
    /**
     * @brief Destroy the Robot object
     * 
     */
    ~Robot();
};
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class RechargeStation : public Entity {
public:
    /**
     * @brief Construct a new Recharge Station object
     * 
     */
    RechargeStation();
    /**
     * @brief Destroy the Recharge Station object
     * 
     */
    ~RechargeStation();
    /**
     * @brief charge the given EDrone
     * 
     * @param drone 
     */
    void charge(EDrone* drone);
};

#endif
