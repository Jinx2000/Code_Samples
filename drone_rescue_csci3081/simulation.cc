/**
 * @file simulation.cc
 * @author Jinwei Zhang (zhan7075@umn.edu)
 * @brief simulation facade .cc
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "simulation.h"

Simulation::Simulation(){};
Simulation::~Simulation(){
    delete drone;
};
Entity* Simulation::createEntity(const picojson::object& data){
    EntityFactory* factory = new EntityFactory();
    Entity* newEntity = factory->createEntity(data);
    delete factory;
    drone = &newEntity;
    return newEntity;
}
void Simulation::update(double dt) {
    // drone move, take picture:
    drone->updatePos(dt, destination);
    // analyze picture:
    Findbot* finder = new Findbot();
    if (finder->Find(coloredImage) { // if found
        drone->entityStatus = "found";
        // use Finder to find the pixel location on the pictur, pass it to the Locator:
        Locator* locator0 = new Locator(finder->PixelLocation());
        // use Locator to get the actual Vector3 location for the robot:
        Vector3* robotLocation = locator0->Locate(depthImage, drone->getPosition());
        destination->setVector(robotLocation->getX(), roboLocation->getY(), robotLocation->getZ());
    }
}
void Simulation::finishUpdate(picojson::object& returnValue) {
    // cite!!!!!
    picojson::object entity;
    entity["entityId"] = picojson::value((double)0);
    
    // Save the position as an array
    picojson::array pos;
    pos.push_back(picojson::value(drone->entityPos->getX());
    pos.push_back(picojson::value(drone->entityPos->getY());
    pos.push_back(picojson::value(drone->entityPos->getZ());
    entity["pos"] = picojson::value(pos);
    
    // Save the direction as an array
    picojson::array dir;
    dir.push_back(picojson::value(drone->droneDir->getX());
    dir.push_back(picojson::value(drone->droneDir->getY());
    dir.push_back(picojson::value(drone->droneDir->getZ());
    entity["dir"] = picojson::value(dir);
    // Send the compile picojson data to the UI in the returnValue variable
    returnValue["entity"+std::to_string(drone->entityID)] = picojson::value(entity);
}

#endif;