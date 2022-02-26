/**
 * @file core_factories.cc
 * @author Jinwei Zhang (zhan7075@umn.edu)
 * @brief entity factory .cc
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

// EntityFactory:

EntityFactory::EntityFactory() {}

EntityFactory::~EntityFactory() {}

Entity* EntityFactory::createEntity(picojson::object& entityData) {
    if (entityData["name"].get<std::string>() == "drone") {
        DroneFactory* droneInc = new DroneFactory();
        Drone* drone = droneInc.createEntity(entityData);
        delete droneInc;
        return drone;
    } else if (entityData["name"].get<std::string>() == "robot") {
        RobotFactory* robotInc = new RobotFactory();
        Robot* robot = robotInc.createEntity(entityData);
        delete robotInc;
        return robot;
    } else if (entityData["name"].get<std::string>() == "recharge_station") {
        RechargeStationFactory* stationInc = new RechargestationFactory();
        RechargeStation* station = stationInc.createEntity(entityData);
        delete stationInc;
        return station;
    } else {
        std::cout<<"Entity type is not supported in current version."<<std::endl;
        return NULL;
    }
}




// DroneFactory:

DroneFactory::DroneFactory(){}

DroneFactory::~DroneFactory(){}

Entity* DroneFactory::createEntity(picojson::object& entityData){
    // Simply change this part to use the decorator pattern for batteries:
    Entity* drone = new Drone();
    // set ID:
    drone->entityID = static_cast<int> (entityData["entityId"].get<double>());
    // set name (type)
    drone->entityName = "drone";
    // set type
    drone->entityType = entityData["type"].get<std::string>();
    // update the position to vector
    picojson::array position = entityData["position"].get<picojson::array>();
    drone->entityPos->setVector(position[0].get<double>(), position[1].get<double>(), position[2].get<double>());
    // update the direction to vector
    picojson::array dir = entityData["direction"].get<picojson::array>();
    drone->droneDir->setVector(dir[0].get<double>(), dir[1].get<double>(), dir[2].get<double>());
    // set the status of the drone:
    drone->droneStatus.replace("searching");
    return drone;
}




// RobotFactory:

RobotFactory::RobotFactory(){}

RobotFactory::~RobotFactory(){}

Entity* RobotFactory::createEntity(picojson::object& entityData){
    Entity* robot = new Robot();
    robot->entityID = static_cast<int> (entityData["entityId"].get<double>());
    robot->entityName = "robot";
    robot->entityType = entityData["type"].get<std::string>();
    picojson::array position = entityData["position"].get<picojson::array>();
    robot->entityPos.setVector(position[0].get<double>(), position[1].get<double>(), position[2].get<double>());
    return robot;
}



// RechargeStationFactory:

RechargeStationFactory::RechargeStationFactory(){}

RechargeStationFactory::~RechargeStationFactory(){}

Entity* RechargeStationFactory::createEntity(picojson::object& entityData) {
    Entity* station = new RechargeStation();
    station->entityID = static_cast<int> (entityData["entityId"].get<double>());
    station->entityName = "recharge_station";
    station->entityType = entityData["type"].get<std::string>();
    picojson::array position = entityData["position"].get<picojson::array>();
    station->entityPos.setVector(position[0].get<double>(), position[1].get<double>(), position[2].get<double>());
    return station;
}

