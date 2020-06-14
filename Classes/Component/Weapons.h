#ifndef _WEAPONS_H_
#define _WEAPONS_H_

#include"cocos2d.h"

USING_NS_CC;

//近战
#define MELEE 1
//远程
#define REMOTE 2

class Weapon
{
	//攻击力
	CC_SYNTHESIZE(int, _attack, Attack);
	//攻速(攻击间隔)
	CC_SYNTHESIZE(float, _attackRate, AttackRate);
	//攻击方式
	CC_SYNTHESIZE(int, _mode, Mode);
	//耗蓝
	CC_SYNTHESIZE(int, _magicUse, MagicUse);
	//子弹编号
	CC_SYNTHESIZE(int, _bulletNum, BulletNum);
	//子弹速度
	CC_SYNTHESIZE(int, _bulletV, BulletV);
	CC_SYNTHESIZE(std::string, _weaponName, WeaponName);

	cocos2d::ValueMap weaponData;

public:
	void initData();
};



#endif // !_WEAPONS_H_

#pragma once
