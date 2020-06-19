#ifndef _PROP_H
#define _PROP_H

#include"cocos2d.h"
#include"Scene/BattleMapScene.h"

USING_NS_CC;

class BattleMap;

class Prop :public cocos2d::Sprite
{
	BattleMap* _combatScene;
	CC_SYNTHESIZE(int, _addHealth, AddHealth);
	CC_SYNTHESIZE(int, _addMagic, AddMagic);
	CC_SYNTHESIZE(int, _addShield, AddShield);
public:
	static Prop* create(const std::string& filename);
};
#endif // !_PROP_H


#pragma once
