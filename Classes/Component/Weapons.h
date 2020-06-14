#ifndef _WEAPONS_H_
#define _WEAPONS_H_

#include"cocos2d.h"

USING_NS_CC;

//��ս
#define MELEE 1
//Զ��
#define REMOTE 2

class Weapon
{
	//������
	CC_SYNTHESIZE(int, _attack, Attack);
	//����(�������)
	CC_SYNTHESIZE(float, _attackRate, AttackRate);
	//������ʽ
	CC_SYNTHESIZE(int, _mode, Mode);
	//����
	CC_SYNTHESIZE(int, _magicUse, MagicUse);
	//�ӵ����
	CC_SYNTHESIZE(int, _bulletNum, BulletNum);
	//�ӵ��ٶ�
	CC_SYNTHESIZE(int, _bulletV, BulletV);
	CC_SYNTHESIZE(std::string, _weaponName, WeaponName);

	cocos2d::ValueMap weaponData;

public:
	void initData();
};



#endif // !_WEAPONS_H_

#pragma once
