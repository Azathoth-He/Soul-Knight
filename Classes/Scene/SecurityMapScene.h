#ifndef _SECURITYMAP_SCENE_H
#define _SECURITYMAP_SCENE_H

#include "cocos2d.h"
#include"HeroMessageScene.h"
#include"../Auxiliary/HRocker.h"
#include"../Auxiliary/MapInformation.h"
#include"cocostudio/CocoStudio.h"
#include"BattleMapScene.h"

USING_NS_CC;
using namespace cocostudio::timeline;

class HeroMessage;

class SecurityMap :public cocos2d::Scene
{
	TMXTiledMap* _seMap;
	CC_SYNTHESIZE(Hero*, _myHero, MyHero);
	CC_SYNTHESIZE(int, _myMoney, MyMoney);
	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);
	cocos2d::Sprite* _player;
	cocos2d::Sprite* _weapon;
	int dir = 0;
	int _oldTime = 0;
	int _nowTime = 0;

public:
	static cocos2d::Scene* createScene(HeroMessage* combatScene);
	static SecurityMap* create(HeroMessage* combatScene);
	virtual bool init(HeroMessage* combatScene);
	void initHRocker();
	void initIcon();
	void initStateBox();
	void update(float dt);
	void updateHeroPosition();
	void updateHeroDirction();
	void updateHeroState();
	void updateScene();
	void heroAttack();
	//¹ö¶¯µØÍ¼
	void setViewpointCenter(Vec2 position);

	//³é½±
	void chooseToDraw(bool isDraw);
};

#endif // !_SECURITYMAP_SCENE_H

