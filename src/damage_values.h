#ifndef DAMAGE_VALUES_H
#define DAMAGE_VALUES_H

#include <cstdint>

//player health
extern std::int16_t playerHealth;

//hole tile
extern std::int16_t holeTileDamage;

//cockroach
extern std::int16_t cockroachHealth;
extern std::int16_t cockroachDamage;
extern std::int16_t cockroach_PushBackHero;

extern std::int16_t cockroach_HitBySwordDamage;
extern std::int16_t cockroach_PushBackBySword;

extern std::int16_t cockroach_HitByBulletDamage;
extern std::int16_t cockroach_PushBackByBullet;

// one push back is 5 pixels
extern std::int16_t onePushBack; 

#endif
