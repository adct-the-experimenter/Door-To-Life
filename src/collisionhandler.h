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
	void addPlayersToCollisionSystem(CollisionObject* p1,CollisionObject* p2,CollisionObject* p3,CollisionObject* p4);

	//function to add player's current weapon to collision system
	void addPlayerEquippedWeaponToCollisionSystem(Weapon* thisWeapon);
	void addPlayerEquippedWeaponsToCollisionSystem(Weapon* thisWeapon1,Weapon* thisWeapon2,Weapon* thisWeapon3,Weapon* thisWeapon4);
	
	//function to add pointer to collision objects vector
	void addObjectToCollisionSystem(CollisionObject* thisObject);


	//function to remove pointer from collision object vector
	void removeObjectFromCollisionSystem(CollisionObject* thisObject);

	//function to set camera for collision system so
	//only keep track of collisions happening inside player's view 
	void setCameraForCollisionSystem(SDL_Rect* camera);
	
	void SetCamerasForCollisionSystem(SDL_Rect* camera1,SDL_Rect* camera2,SDL_Rect* camera3,SDL_Rect* camera4);

	//function to do collision process
	void run_collision_handler(int& num_players);
	
	//function to empty the collision objects vector of all collision objects.
	//used for restarting the game safely.
	void EmptyCollisionObjectVector();
	
	//function to remove the collisoin object pointer to player equipped weapon.
	void EmptyPlayerEquippedWeapon();

	bool repeatPlay;
	
private:

	CollisionObject* m_player1CollisionObject_ptr;
	CollisionObject* m_player2CollisionObject_ptr;
	CollisionObject* m_player3CollisionObject_ptr;
	CollisionObject* m_player4CollisionObject_ptr;

	Weapon* m_playerEquippedWeaponPtr;
	std::vector <CollisionObject*> collisionObjectsVector;
	
	SDL_Rect* cameraCollisionHandler;
	SDL_Rect* cameraCollisionHandler2;
	SDL_Rect* cameraCollisionHandler3;
	SDL_Rect* cameraCollisionHandler4;
	
	void runPlayer1CollisionOperations(CollisionObject& thisObject);
	void runPlayer2CollisionOperations(CollisionObject& thisObject);
	void runPlayer3CollisionOperations(CollisionObject& thisObject);
	void runPlayer4CollisionOperations(CollisionObject& thisObject);
	
	void runPlayer1WeaponCollisionOperations(CollisionObject& thisObject);
	void runPlayer2WeaponCollisionOperations(CollisionObject& thisObject);
	void runPlayer3WeaponCollisionOperations(CollisionObject& thisObject);
	void runPlayer4WeaponCollisionOperations(CollisionObject& thisObject);
	
	Weapon* playerEquippedWeapon;
	Weapon* playerEquippedWeapon2;
	Weapon* playerEquippedWeapon3;
	Weapon* playerEquippedWeapon4;
};




#endif
