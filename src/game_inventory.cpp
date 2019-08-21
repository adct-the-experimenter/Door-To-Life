#include "game_inventory.h"


std::array <Weapon*,1> weaponsArray;

void setupDefaultGunForPlayer(std::int16_t& x, std::int16_t& y)
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
    addObjectToCollisionSystem(def_gun->getCollisionObjectPtr());
    //put into weapons array as first item
    Weapon* def_weapon = def_gun;
    weaponsArray[0] = def_weapon;
}

void checkWeaponsOnGround_Collision()
{
    for(size_t i=0; i < weaponsArray.size(); ++i)
    {
        //if weapon collision box collides with hero collision box
        if(weaponsArray[i]->getBool_HeroTouchedWeaponOnGround() )
        {
            //equip weapon to player for now
            equipThisWeaponToPlayer(weaponsArray[i]);
        }
    }
}

void run_weapons_render(SDL_Renderer* gRenderer, SDL_Rect& camera)
{
    //for every weapon 
    for(size_t i=0; i < weaponsArray.size(); ++i)
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

void passWeaponToPlayerInventory(Weapon* thisWeapon)
{
    
}

void freeWeapons()
{
    delete weaponsArray[0];
}
