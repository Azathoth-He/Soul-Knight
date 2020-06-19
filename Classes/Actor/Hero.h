#ifndef _HERO_H_ 
#define _HERO_H_

#include"cocos2d.h"
#include"Component/Weapons.h"
#include"Component/Bullet.h"

USING_NS_CC;

class Hero
{
	CC_SYNTHESIZE(std::string, _heroName, HeroName);
	//当前状态
	CC_SYNTHESIZE(int, _currentHealth, CurrentHealth);
	CC_SYNTHESIZE(int, _currentMagic, CurrentMagic);
	CC_SYNTHESIZE(int, _currentShiled, CurrentShiled);

	CC_SYNTHESIZE(int, _moveSpeed, MoveSpeed);

	//上限
	CC_SYNTHESIZE(int, _maxHealth, MaxHealth);
	CC_SYNTHESIZE(int, _maxShield, MaxShield);
	CC_SYNTHESIZE(int, _maxMagic, MaxMagic);
	//等级
	CC_SYNTHESIZE(int, _level, Level);
	CC_SYNTHESIZE(int, _upLevelMoney, UpLevelMoney);
	CC_SYNTHESIZE(Weapon*, _myWeapon, MyWeapon);


	cocos2d::ValueMap _heroDataAtEachLevel;
	cocos2d::ValueMap _upLevel;

public:
	void levelUp();
	bool initHeroData(std::string heroName);
	void initWeapon();
	Bullet* remoteAttack();

};


#endif
#pragma once
