#ifndef PLAYER_INVENTORY_H
#define PLAYER_INVENTORY_H

#include <array>

#include "collisionhandler.h" //for registering player weapon to collision handler
#include "weapon.h"
#include "sword.h"

#include "player.h"

//structure to hold a weapon or game item
struct InventorySlot 
{
    //pointer to weapon
    Weapon* weaponPtr;
    //pointer to game_item
    
    //bool to tell if slot is filled with something(e.g game item or weapon)
    bool slotFilled;
};

class PlayerInventory
{
public:
	
	PlayerInventory();
	~PlayerInventory();
	
	void SetPointerToPlayer(Player* thisPlayer);
	
	//Prompt

	//function to prompt player if want to throw away item
	void promptPlayerThrowAway();
	//function to prompt player to put item in inventory
	void promptPlayer_PutItemInInventory();
	//function to prompt player to put weapon in inventory
	void promptPlayer_PutWeaponInInventory(Weapon* thisWeapon);


	//Adding to Inventory 
	//function to place weapon in next available inventory slot
	void putWeaponInInventory(Weapon* thisWeapon);
	
	//function to place item in next available inventory slot
	//void putGameItemInInventory();
	//Removing from Inventory


	//Using Stuff in Inventory

	//function to use item from inventory
	//void useItem();

	

	//function to equip weapon to player
	void equipThisWeaponToPlayer(Weapon* thisWeapon);
	//function to unequip weapon from player
	void unequipWeaponFromPlayer();

private:
	//array of slots in inventory which are used to contain weapon or item
	std::array <InventorySlot,8> inventory_slots;

	//variable for which slot selector is currently on
	std::int8_t currentInventorySlotSelected;
	
	Player* m_player_ptr;
	
};





#endif
