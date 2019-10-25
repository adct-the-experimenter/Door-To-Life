# How to Make An Enemy And Add it to the Game

## Overview

There are 4 parts to making an enemy character for the game.

- Enemy Media
- Enemy Attributes
- Enemy Logic
- Enemy Generation In Game

There are 10 files that need to be edited to add an enemy to the game.

- `enemy_inventory.cpp`
- `enemy_media_loader.h` and `enemy_media_loader.cpp`
- `player.cpp`
- `damage_values.h` and `damage_values.cpp`
- `collisionobject.h` and `collisionhandler.cpp`
- `my_enemy.h` and `my_enemy.cpp`

Use `my_enemy.h` and `my_enemy.cpp` as templates.
Copy the files, change the file names, change MyEnemy to desired enemy name.

## Setting Enemy Media

![Image of Enemy](https://raw.githubusercontent.com/adct-the-experimenter/Door-To-Life/master/data/Graphics/greedy-zombie.png)


### In `enemy_media_loader.h`

Include the my_enemy.h header file and declare the functions for loading media and the extern variables to be defined for my enemy.
function loadMyEnemyMedia is a friend function declared in my_enemy.h and defined in my_enemy.cpp

    #include "my_enemy.h"
    //My Enemy media
    bool setupLoad_MyEnemy(SDL_Renderer* gRenderer);
    extern LTexture my_enemy_texture;
    extern std::vector <SDL_Rect> my_enemy_walk_clips;
    bool loadMyEnemyMedia(LTexture* cTexture,
                            std::vector <SDL_Rect> &clips,
                            SDL_Renderer* gRenderer );`
    
    void freeMyEnemyMedia(LTexture* cTexture);


### In `enemy_media_loader.cpp`

Define the how to load media.

    include "enemy_media_loader.h"
    //Setup my enemy media
    
    LTexture my_enemy_texture;
    std::vector <SDL_Rect> my_enemy_walk_clips;
    bool setupLoad_MyEnemy(SDL_Renderer* gRenderer)
    {
        //load my enemy media
        if(!loadMyEnemyMedia(&my_enemy_texture,
                            my_enemy_walk_clips,
                            gRenderer )
        )
        {
            printf("Failed to load my enemy media! \n");```
            return false;
        }
        return true;
    }

### In `my_enemy.h`

Declare friend functions for loading media.

    //function to load media outside class

    friend bool loadMyEnemyMedia(LTexture* cTexture,
                                        std::vector <SDL_Rect> &clips,
                                        SDL_Renderer* gRenderer );
    
    friend void freeMyEnemyMedia(LTexture* cTexture); 


### In `my_enemy.cpp`

Define the friend functions for loading media.
The walk clips are the frames in the sprite sheet that get cut for animation.

Also define how the media is freed.

    bool loadMyEnemyMedia(LTexture* cTexture,
                        std::vector <SDL_Rect> &walk_clips,
                        SDL_Renderer* gRenderer )
    {
        bool success = true;
    
        std::string cTexFilePath = DATADIR_STR + std::string("/Graphics/my-enemy.png");
        //initialize greedy zombie image
        if(!cTexture->loadFromFile(cTexFilePath.c_str(),gRenderer) )
        {
            success = false;
            std::cout << "my enemy image loading failed! \n";
        }
        else
        {
            walk_clips.resize(32);
        
            std::int8_t width = 51;
            std::int8_t height = 65;
            
            walk_clips[Sprite::UP_1] = {6,192,51,65};
            walk_clips[Sprite::UP_2] = {70,192,51,65}; 
            walk_clips[Sprite::UP_3] = {136,192,51,65}; 
            walk_clips[Sprite::UP_4] = {199,192,51,65};
            
            walk_clips[Sprite::UP_LEFT_1] = {0,82,64,54};
            walk_clips[Sprite::UP_LEFT_2] = {63,82,64,54};
            walk_clips[Sprite::UP_LEFT_3] = {126,82,64,54};
            walk_clips[Sprite::UP_LEFT_4] = {190,82,64,54};
            
            walk_clips[Sprite::LEFT_1] = {0,82,64,54};
            walk_clips[Sprite::LEFT_2] = {63,82,64,54};
            walk_clips[Sprite::LEFT_3] = {126,82,64,54};
            walk_clips[Sprite::LEFT_4] = {190,82,64,54};
            
            walk_clips[Sprite::DOWN_LEFT_1] = {0,82,64,54};
            walk_clips[Sprite::DOWN_LEFT_2] = {63,82,64,54};
            walk_clips[Sprite::DOWN_LEFT_3] = {126,82,64,54};
            walk_clips[Sprite::DOWN_LEFT_4] = {190,82,64,54};
            
            walk_clips[Sprite::DOWN_1] = {5,3,51,65};
            walk_clips[Sprite::DOWN_2] = {68,3,51,65};
            walk_clips[Sprite::DOWN_3] = {134,3,51,65};
            walk_clips[Sprite::DOWN_4] = {198,3,51,65};
            
            walk_clips[Sprite::RIGHT_1] = {0,138,64,54};
            walk_clips[Sprite::RIGHT_2] = {65,138,64,54};
            walk_clips[Sprite::RIGHT_3] = {127,138,64,54};
            walk_clips[Sprite::RIGHT_4] = {191,138,64,54};
            
            walk_clips[Sprite::DOWN_RIGHT_1] = {0,138,64,54};
            walk_clips[Sprite::DOWN_RIGHT_2] = {65,138,64,54};
            walk_clips[Sprite::DOWN_RIGHT_3] = {127,138,64,54};
            walk_clips[Sprite::DOWN_RIGHT_4] = {191,138,64,54};
            
            walk_clips[Sprite::UP_RIGHT_1] = {0,138,64,54};
            walk_clips[Sprite::UP_RIGHT_2] = {65,138,64,54};
            walk_clips[Sprite::UP_RIGHT_3] = {127,138,64,54};
            walk_clips[Sprite::UP_RIGHT_4] = {191,138,64,54};
        }
        
        return success;
    }

    void freeMyEnemyMedia(LTexture* cTexture)
    {
        if(cTexture != nullptr)
        {
            //delete cTexture;
            cTexture = nullptr;
        }
    }

## Setting Enemy Attributes

### In `damage_values.h`

Declare these variables for health of the enemy, damage done by enemy to player, pushback that enemy causes to player, and pushback that weapons do to enemy.

    //My Enemy

    extern std::int16_t myEnemyHealth;
    extern std::int16_t myEnemyDamage;
    extern std::int16_t myEnemy_PushBackHero;
    
    extern std::int16_t myEnemy_HitBySwordDamage;
    extern std::int16_t myEnemy_PushBackBySword;
    
    extern std::int16_t myEnemy_HitByBulletDamage;
    extern std::int16_t meEnemy_PushBackByBullet;

### In `damage_values.cpp`

Define the variables for health of the enemy, damage done by enemy to player, pushback that enemy causes to player, and pushback that weapons do to enemy.

    //My enemy
    
    std::int16_t myEnemyHealth = 50;
    std::int16_t myEnemyDamage = playerHealth / 5; // 1/5 of total hero health 
    
    std::int16_t myEnemy_PushBackHero = 30; // 30 pixel push back distance
    
    std::int16_t myEnemy_HitBySwordDamage = 20; // damage to greedZombie when hit by sword`
    std::int16_t myEnemy_PushBackBySword = 40; // 40 pixel push back distance
    
    std::int16_t myEnemy_HitByBulletDamage = 20;
    std::int16_t myEnemy_PushBackByBullet = 40;

### In `collisionobject.h`

Add an enum for my enemy in enum class CollisionBoxOwnerType and
an enum for my enemy in enum class CollisionType.

    //Info on who owns collision box
    
    enum class CollisionBoxOwnerType : std::int8_t {
    NONE = 0, PLAYER ,    
    //Enemy 
    COCKROACH, LINE_OF_SIGHT,
    MY_ENEMY,
                                                    
    //Obstacle
    HOLE,
    //Weapons
    SWORD, BULLET,
    //Items                                               `  
    };

    //enum for what kind of collision it is
    
    enum class CollisionType : std::int8_t { 
    NONE = 0,
    //for enemy
    HIT_PLAYER, HIT_BY_SWORD, HIT_BY_BULLET,
    
    //for player
    HIT_BY_COCKROACH, HIT_BY_MY_ENEMY,COLLIDING_WITH_HOLE};

### In `collisionhandler.cpp`

In function `void CollisonHandler::runPlayerCollisionOperations(CollisionObject& thisObject)`

Add a case for collision box owner type being my enemy and assigning type of collision as a hit by my enemy.

    switch(thisObject.ownerType )
    {
        case CollisionBoxOwnerType::COCKROACH :{ typeCollisionToPlayer = CollisionType::HIT_BY_COCKROACH; break;}
        case CollisionBoxOwnerType::MY_ENEMY :{ typeCollisionToPlayer = CollisionType::HIT_BY_MY_ENEMY; break;}
        case CollisionBoxOwnerType::HOLE:{ typeCollisionToPlayer = CollisionType::COLLIDING_WITH_HOLE; break;}
        default:{typeCollisionToPlayer = CollisionType::NONE; break;}
    }

## Setting Enemy Generation

In function `void EnemyInventory::setupEnemyVector()`
, based on how many enemies to add in game,
can use size of enemy vector and decide how many of MyEnemy to put in the game using iterators.

    enemies_vector.resize(150);
    //for all enemies
    for(size_t i=0; i < enemies_vector.size(); ++i)
    {
		if(i < 70)
		{
			//make it a cockroach
			OtherCockroach* thisCockroach = new OtherCockroach(4,2,55,65);
			thisCockroach->setPointersToMedia(&cockroach_texture,cockroach_walk_clips);
			
			enemies_vector[i] = thisCockroach;
		}
		else if(i >= 70 && i <= 80)
		{
			//make it my enemy
			MyEnemy* thisEnemy = new MyEnemy(4,2,55,65);
			thisEnemy->setPointersToMedia(&my_enemy_texture,my_enemy_walk_clips);
			
			enemies_vector[i] = thisEnemy;
		}
		else
		{
			//make it a cockroach
			OtherCockroach* thisCockroach = new OtherCockroach(4,2,55,65);
			thisCockroach->setPointersToMedia(&cockroach_texture,cockroach_walk_clips);
			
			enemies_vector[i] = thisCockroach;
		}
        
    }

