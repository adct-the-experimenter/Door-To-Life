#include "player_inventory.h"

PlayerInventory::PlayerInventory()
{
	m_player_ptr = nullptr;
}

PlayerInventory::~PlayerInventory()
{
	m_player_ptr = nullptr;
}

void PlayerInventory::equipThisWeaponToPlayer(Weapon* thisWeapon)
{
    //assign equipped player weapon pointer to point to weapon pointer input
    m_player_ptr->equippedPlayerWeapon = thisWeapon;    
    //put weapon in default state of standing with handler no action
    thisWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION);
    //attach player collision box to weapon
    thisWeapon->attachWeaponToHandlerBox(m_player_ptr->getCollisionObjectPtr()->ptrToCollisionBox);
    
    thisWeapon->SetHeightFromGround(10);
}

void PlayerInventory::equipThisWeaponToPlayer(Player* thisPlayer, Weapon* thisWeapon)
{
	//assign equipped player weapon pointer to point to weapon pointer input
    thisPlayer->equippedPlayerWeapon = thisWeapon;    
    //put weapon in default state of standing with handler no action
    thisWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION);
    //attach player collision box to weapon
    thisWeapon->attachWeaponToHandlerBox(thisPlayer->getCollisionObjectPtr()->ptrToCollisionBox);
    
    thisWeapon->SetHeightFromGround(10);
}

void PlayerInventory::unequipWeaponFromPlayer(){m_player_ptr->equippedPlayerWeapon = nullptr;}

void PlayerInventory::unequipWeaponFromPlayer(Player* thisPlayer){thisPlayer->equippedPlayerWeapon = nullptr;}

void PlayerInventory::SetPointerToPlayer(Player* thisPlayer){m_player_ptr = thisPlayer;}
