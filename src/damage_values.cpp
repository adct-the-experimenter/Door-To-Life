#include "damage_values.h"

std::int16_t playerHealth = 100;

//one push back is 5 pixels
std::int16_t onePushBack = 5;

//Hole
std::int16_t holeTileDamage = playerHealth / 20;

//Cockroach
std::int16_t cockroachHealth = 50;
std::int16_t cockroachDamage = playerHealth / 10; // 1/10 of total hero health 

std::int16_t cockroach_PushBackHero = 30; // 30 pixel push back distance

std::int16_t cockroach_HitBySwordDamage = 20; // damage to cockroach when hit by sword
std::int16_t cockroach_PushBackBySword = 40; // 40 pixel push back distance

std::int16_t cockroach_HitByBulletDamage = 20;
std::int16_t cockroach_PushBackByBullet = 40;

//Greedy zombie
std::int16_t greedZombieHealth = 50;
std::int16_t greedZombieDamage = playerHealth / 5; // 1/5 of total hero health 

std::int16_t greedZombie_PushBackHero = 30; // 30 pixel push back distance

std::int16_t greedZombie_HitBySwordDamage = 20; // damage to greedZombie when hit by sword
std::int16_t greedZombie_PushBackBySword = 40; // 40 pixel push back distance

std::int16_t greedZombie_HitByBulletDamage = 20;
std::int16_t greedZombie_PushBackByBullet = 40;
