#include "player_inventory.h"



std::array <InventorySlot,8> inventory_slots;
std::int8_t currentInventorySlotSelected;

//Pointer to Weapon equipped by player
Weapon* equippedPlayerWeapon = nullptr;

void equipThisWeaponToPlayer(Weapon* thisWeapon)
{
    //assign equipped player weapon pointer to point to weapon pointer input
    equippedPlayerWeapon = thisWeapon;    
    //put weapon in default state of standing with handler no action
    thisWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION);
    //attach player collision box to weapon
    thisWeapon->attachWeaponToHandlerBox(playerCollisionObject->ptrToCollisionBox);
    //pass collision object pointer to weapon to collision system 
    addPlayerEquippedWeaponToCollisionSystem(thisWeapon);
}

void unequipWeaponFromPlayer(){equippedPlayerWeapon = nullptr;}

