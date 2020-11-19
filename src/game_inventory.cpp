#include "game_inventory.h"


GameInventory::GameInventory()
{
	m_player_inventory_ptr = nullptr;
	weaponsArray[0] = nullptr;
}

GameInventory::~GameInventory()
{
	m_player_inventory_ptr = nullptr;
}

void GameInventory::SetPointerToPlayerInventory(PlayerInventory* thisInventory)
{
	m_player_inventory_ptr = thisInventory;
}

void GameInventory::SetPointerToCollisionHandler(CollisonHandler* thisHandler)
{
	m_collision_handler_ptr = thisHandler;
}

void GameInventory::setupDefaultGunForPlayer_grounditem(std::int16_t& x, std::int16_t& y)
{
	//setup bullet resources
	Bullet* thisBullet = new Bullet();
	thisBullet->setSpriteTexture(&bullet_sprite_sheet_tex);
	thisBullet->setBulletSpriteClips(&bullet_direction_clips);
	float defGun_BulletSpeed = 480;
	thisBullet->setBulletSpeed(defGun_BulletSpeed);
	
    //setup gun resources
    Gun* def_gun = new Gun();
    
    //make gun point to bullet 
    def_gun->setPointerToBullet(thisBullet);
    
    def_gun->setWeaponState(Weapon::WeaponState::ON_GROUND); //set to ground state
    
    std::int8_t animFrames = 4;
    def_gun->setNumberOfAnimationFrames(animFrames);
    def_gun->setSpriteSheetTexture(&gun_sprite_sheet_tex); //set sprite sheet of sword
    def_gun->setWalkClips(&gun_walk_clips); //set walk clips of sword
    
    
    std::int16_t groundWidth = 10;
    std::int16_t groundHeight = 20;
    //set width and height of sword
    def_gun->setWeaponGroundBoxWidth(groundWidth);
    def_gun->setWeaponGroundBoxHeight(groundHeight);
    
    std::int16_t attackWidth = 20;
    std::int16_t attackHeight = 40;
    def_gun->setWeaponAttackBoxWidth(attackWidth);
    def_gun->setWeaponAttackBoxHeight(attackHeight);
    
    def_gun->setGroundLocation(x,y); //set location of sword
    def_gun->faceWeaponGroundNorth(); //set direction weapon is facing on ground
    def_gun->setMoveClip();
    
    //add weapon to collision handler
    m_collision_handler_ptr->addObjectToCollisionSystem(def_gun->getCollisionObjectPtr());
    //put into weapons array as first item
    Weapon* def_weapon = def_gun;
    weaponsArray[0] = def_weapon;
}

void GameInventory::setupDefaultGunForPlayer_equippedweapon(Player* thisPlayer)
{
	//setup bullet resources
	Bullet* thisBullet1 = new Bullet();
	thisBullet1->setSpriteTexture(&bullet_sprite_sheet_tex);
	thisBullet1->setBulletSpriteClips(&bullet_direction_clips);
	
	float defGun_BulletSpeed = 480;
	thisBullet1->setBulletSpeed(defGun_BulletSpeed);
	
	
	//setup gun resources
	Gun* def_gun1 = new Gun();
	
	//make gun point to bullet 
	def_gun1->setPointerToBullet(thisBullet1);
	std::int8_t animFrames = 4;
	def_gun1->setNumberOfAnimationFrames(animFrames);
	def_gun1->setSpriteSheetTexture(&gun_sprite_sheet_tex); //set sprite sheet of sword
	def_gun1->setWalkClips(&gun_walk_clips); //set walk clips of sword
	
	
	std::int16_t groundWidth = 10;
	std::int16_t groundHeight = 20;
	//set width and height of sword
	def_gun1->setWeaponGroundBoxWidth(groundWidth);
	def_gun1->setWeaponGroundBoxHeight(groundHeight);
	
	
	std::int16_t attackWidth = 20;
	std::int16_t attackHeight = 40;
	def_gun1->setWeaponAttackBoxWidth(attackWidth);
	def_gun1->setWeaponAttackBoxHeight(attackHeight);
	def_gun1->faceWeaponGroundNorth(); //set direction weapon is facing on ground
	def_gun1->setMoveClip();
	m_player_inventory_ptr->equipThisWeaponToPlayer(thisPlayer,def_gun1);
}

void GameInventory::checkWeaponsOnGround_Collision(PlayerInventory* p_inventory)
{
    for(size_t i=0; i < weaponsArray.size(); ++i)
    {
        //if weapon collision box collides with hero collision box
        if(weaponsArray[i]->getBool_HeroTouchedWeaponOnGround() )
        {
            //equip weapon to player for now
            p_inventory->equipThisWeaponToPlayer(weaponsArray[i]);
            m_collision_handler_ptr->addPlayerEquippedWeaponToCollisionSystem(weaponsArray[i]);
        }
    }
}

void GameInventory::run_weapons_render(SDL_Renderer* gRenderer, SDL_Rect& camera)
{
    //for every weapon 
    for(size_t i=0; i < weaponsArray.size(); ++i)
    {
		if(weaponsArray[i])
		{
			//if weapon within camera
			if(checkCollision(camera,
								*( weaponsArray[i]->getCollisionObjectPtr()->ptrToCollisionBox) ) )
			{
				//if weapon is on ground
				if(weaponsArray[i]->getWeaponState() == Weapon::WeaponState::ON_GROUND)
				{
					weaponsArray[i]->render(camera,gRenderer,nullptr);
				}
				
			}
		}
        
    }
}

void GameInventory::passWeaponToPlayerInventory(Weapon* thisWeapon)
{
    
}

void GameInventory::freeWeapons()
{
    delete weaponsArray[0];
}
