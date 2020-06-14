#ifndef _ACTOR_H
#define _ACTOR_H

#include "cocos2d.h"

USING_NS_CC;

//��ս
#define MELEE 1
//Զ��
#define REMOTE 2

class Actor :public cocos2d::Sprite
{
	//��ǰ״̬
	CC_SYNTHESIZE(int, _currentHealth, health);
	CC_SYNTHESIZE(int, _currentMagic, magic);

	CC_SYNTHESIZE(int, _attackMode, AttackMode);
	CC_SYNTHESIZE(float, _moveAngle, MoveAngle);
	CC_SYNTHESIZE(float, _moveSpeed, MoveSpeed);

	virtual void die();
	virtual void move(Vec2 destination);

public:
	virtual bool init();
	virtual void initState();
	static Actor* create();
};
#endif 

#pragma once
