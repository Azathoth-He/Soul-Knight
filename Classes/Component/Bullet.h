#ifndef _BULLET_H_
#define _BULLET_H_

#include"cocos2d.h"
#include"Auxiliary/MapInformation.h"

USING_NS_CC;

class Bullet :public cocos2d::Sprite
{
	CC_SYNTHESIZE(Vec2, _velocity, Velocity);
	int shootDir;
	int _camp;
	int _attack;
	TMXTiledMap* _map;
public:
	void shootBullet(int dir, int camp, int attack, TMXTiledMap* map);

	virtual void update(float dt);
	static Bullet* create(const std::string& filename);

};

#endif // !_BULLET_H_


#pragma once
