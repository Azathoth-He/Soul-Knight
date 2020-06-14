#ifndef _BULLET_H_
#define _BULLET_H_

#include"cocos2d.h"

USING_NS_CC;

class Bullet :public cocos2d::Sprite
{
	CC_SYNTHESIZE(Vec2, _velocity, Velocity);
	int shootDir;

public:
	void shootBullet(int dir);

	virtual void update(float dt);
	static Bullet* create(const std::string& filename);

};

#endif // !_BULLET_H_


#pragma once
