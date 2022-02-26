/**
 * @file core_entities.cc
 * @author Jinwei Zhang (zhan7075@umn.edu)
 * @brief entity class .cc
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "core_entities.h"

// Entity:

Entity::Entity(){}

Entity::~Entity(){
    delete entityPos;
}

Vector3* Entity::getPosition(){return entityPos;}





// Drone:

Drone::Drone(){}

Drone::~Drone(){
    delete entityPos;
    delete droneDir;
}
// getters:
Vector3* Drone::getDirection(){return droneDir;}
double Drone::getSpeed() {return speed;}
int Drone::getGotToMove() {return gotToMove;}

// setters:
void Drone::setStatus(std::string newStatus){
    droneStatus = newStatus;
}
void Drone::setDirection(Vector3* const newDir){
    droneDir->setVector(newDir->getX(), newDir->getY(), newDir->getZ());
}
void Drone::setSpeed(double newSpeed) {
    speed = newSpeed;
}


int Drone::isRobotFound(){
    std::string temp = "found";
    return (entityStatus.compare(temp));
}


int Drone::updatePos(double dt, Vector3* destination){
    if (entityStatus.compare("found")) {
        Beeline *beeline = new Beeline(this);
        beeline->move(destination);
        entityPos += droneDir * (float)(dt * speed);
        time += dt;
        delete beeline;
    } else {
        Patrol *patrol = new Patrol(this);
        patrol->move();
        entityPos += droneDir * (float)(dt * speed); // overrided "*"
        time += dt;
        if (time-lastPictureTime > 5.0) {
            cameras[0]->TakePicture();
            lastPictureTime = time;
        }
        return 0;
    }
}

}

void Drone::Rotate(double angle) {
    // Rotates the drone by changing the velocity by a
    // specified angle.
    double x = droneDir->getX();
    double y = droneDir->getY();
    droneDir->setX(x*std::cos(angle) - y*std::sin(angle));
    droneDir->setY(x*std::sin(angle) + y*std::cos(angle));
}


// Robot:

Robot::Robot(){}

Robot::~Robot(){}


// RechargeStation:

RechargeStation::RechargeStation(){}

RechargeStation::~RechargeStation(){}

void RechargeStation::charge(EDrone* drone) {
    drone->setBattery(100);
}
