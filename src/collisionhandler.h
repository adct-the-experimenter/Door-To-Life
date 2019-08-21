#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "globalvariables.h" //for SDL Rect
#include "collisionobject.h" //for collision object and checkCollision
#include "weapon.h" //for weapon class pointer

#include <cstdint> //for integer types with specific size
#include <vector>



//pointer to player's collision object
extern CollisionObject* playerCollisionObject;
//function to add player to collision system
void addPlayerToCollisionSystem(CollisionObject* thisObject);

//pointer to collision object of player's equipped weapon
extern Weapon* playerEquippedWeapon;

//function to add player's current weapon to collision system
void addPlayerEquippedWeaponToCollisionSystem(Weapon* thisWeapon);



//vector of collision objects
extern std::vector <CollisionObject*> collisionObjectsVector;
//function to add pointer to collision objects vector
void addObjectToCollisionSystem(CollisionObject* thisObject);


//function to remove pointer from collision object vector
void removeObjectFromCollisionSystem(CollisionObject* thisObject);

//pointer to camera 
extern SDL_Rect* cameraCollisionHandler;

//function to set camera for collision system so
//only keep track of collisions happening inside player's view 
void setCameraForCollisionSystem(SDL_Rect* camera);

//function to do collision process
void run_collision_handler();



#endif
