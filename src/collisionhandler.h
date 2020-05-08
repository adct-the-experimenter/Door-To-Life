#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "globalvariables.h" //for SDL Rect
#include "collisionobject.h" //for collision object and checkCollision
#include "weapon.h" //for weapon class pointer

#include <cstdint> //for integer types with specific size
#include <vector>


class CollisonHandler
{
	
public:
	CollisonHandler();
	~CollisonHandler();
	
	//function to add player to collision system
	void addPlayerToCollisionSystem(CollisionObject* thisObject);

	//function to add player's current weapon to collision system
	void addPlayerEquippedWeaponToCollisionSystem(Weapon* thisWeapon);

	//function to add pointer to collision objects vector
	void addObjectToCollisionSystem(CollisionObject* thisObject);


	//function to remove pointer from collision object vector
	void removeObjectFromCollisionSystem(CollisionObject* thisObject);

	//function to set camera for collision system so
	//only keep track of collisions happening inside player's view 
	void setCameraForCollisionSystem(SDL_Rect* camera);

	//function to do collision process
	void run_collision_handler();
	
	//function to empty the collision objects vector of all collision objects.
	//used for restarting the game safely.
	void EmptyCollisionObjectVector();
	
	//function to remove the collisoin object pointer to player equipped weapon.
	void EmptyPlayerEquippedWeapon();

	bool repeatPlay;
	
private:
	CollisionObject* m_playerCollisionObject_ptr;

	Weapon* m_playerEquippedWeaponPtr;
	std::vector <CollisionObject*> collisionObjectsVector;
	SDL_Rect* cameraCollisionHandler;
	
	void runPlayerCollisionOperations(CollisionObject& thisObject);
	void runPlayerWeaponCollisionOperations(CollisionObject& thisObject);
	
	Weapon* playerEquippedWeapon;
};




#endif
