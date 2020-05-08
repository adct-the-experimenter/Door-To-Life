#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include "globalvariables.h"//for SDL_Rect

//Info on who owns collision box
enum class CollisionBoxOwnerType : std::int8_t { NONE = 0, 
                                                PLAYER ,
                                                //Enemy 
                                                COCKROACH, LINE_OF_SIGHT,
                                                GREEDY_ZOMBIE,
                                                //Obstacle
                                                HOLE,
                                                //Weapons
                                                SWORD, BULLET,
                                                //Items
                                                
                                                };

//enum for what kind of collision it is
enum class CollisionType : std::int8_t { 
										NONE = 0, 
                                        //for enemy
                                        HIT_PLAYER, HIT_BY_SWORD, HIT_BY_BULLET,
                                        //for player
                                        HIT_BY_COCKROACH, HIT_BY_ZOMBIE,
                                        COLLIDING_WITH_HOLE
                                        };


//enum for direction of collision based on direction weapon is facing
enum class CollisionDirection : std::int8_t {
												NONE = 0, NORTH, NORTHEAST,EAST,SOUTHEAST,SOUTH,SOUTHWEST,WEST,NORTHWEST, WALL
											};

//structure to hold pointer to collision box and info of its owner
struct CollisionObject
{
    //pointer to SDL_Rect
    SDL_Rect* ptrToCollisionBox = nullptr;
    //Info on who owns collision object
    CollisionBoxOwnerType ownerType = CollisionBoxOwnerType::NONE;
    //Info on what is colliding with owner of collision object
    CollisionType typeOfCollision = CollisionType::NONE;
    //Info on direction of collision
    CollisionDirection directionOfCollision = CollisionDirection::NONE;
};

//function to check collision between SDL_Rect
extern bool checkCollision(SDL_Rect& a, SDL_Rect& b);

#endif
