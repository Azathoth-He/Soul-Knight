#ifndef _BATTLEMAP_SCENE_H_
#define _BATTLEMAP_SCENE_H_

#include"cocos2d.h"
#include"SecurityMapScene.h"
#include"../Auxiliary/HRocker.h"

USING_NS_CC;

class SecurityMap;

class BattleMap :public cocos2d::Scene
{
	TMXTiledMap* _map;
	CC_SYNTHESIZE(Hero*, _myHero, MyHero);
	CC_SYNTHESIZE(int, _myMoney, MyMoney);
	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);
	cocos2d::Sprite* _player;
	cocos2d::Sprite* _weapon;
	//µØÍ¼ÒÆ¶¯Æ«ÒÆÁ¿
	Vec2 _offset;
	int dir = 0;
	int _oldTime = 0;
	int _nowTime = 0;
public:
	static cocos2d::Scene* createScene(SecurityMap* combatScene);
	static BattleMap* create(SecurityMap* combatScene);
	virtual bool init(SecurityMap* combatScene);
	void initHRocker();
	void initIcon();
	void initStateBox();

	void update(float dt);
	void updateHeroState();
	void updateHeroPosition();
	void updateOthers();
	void setViewpointCenter(Vec2 position);
};


#endif // !_BATTLEMAP_SCENE_H_

#pragma once
