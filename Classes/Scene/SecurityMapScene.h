#ifndef _SECURITYMAP_SCENE_H
#define _SECURITYMAP_SCENE_H

#include "cocos2d.h"
#include"HeroMessageScene.h"
#include"../Auxiliary/HRocker.h"
#include"../Auxiliary/MapInformation.h"
#include"cocostudio/CocoStudio.h"
#include"BattleMapScene.h"
#include"dragonBones/Engine/CCDragonBonesHeaders.h"
#include"GamePauseScene.h"
#include"EnemyMessageScene.h"
#include"WeaponMessageScene.h"

USING_NS_CC;
using namespace cocostudio::timeline;

class HeroMessage;
class GamePause;

class SecurityMap :public cocos2d::Scene
{
	TMXTiledMap* _seMap;
	CC_SYNTHESIZE(Hero, _myHero, MyHero);
	CC_SYNTHESIZE(int, _myMoney, MyMoney);
	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);
	dragonBones::CCFactory* _factory;
	dragonBones::CCArmatureDisplay* _armature;
	Vector<Weapon*> _weapons;
	int _lastChangeTime = 0;
	int dir = 0;
	int _lastDrawTime = 0;
	int _oldTime = 0;
	int _nowTime = 0;

	Hero _archer;
	Hero _paladin;
	Hero _berserker;

public:
	static cocos2d::Scene* createScene(HeroMessage* combatScene);
	static SecurityMap* create(HeroMessage* combatScene);
	virtual bool init(HeroMessage* combatScene);
	void initHRocker();
	void initIcon();
	void initStateBox();
	void initArmature();
	void update(float dt);
	void updateHeroPosition();
	void updateHeroDirction();
	void updateHeroState();
	void updateScene();
	void generateWeapon();
	void heroAttack();
	void changeWeapon();
	//¹ö¶¯µØÍ¼
	void setViewpointCenter(Vec2 position);
	//³é½±
	void chooseToDraw(bool isDraw);
	void menuPauseCallBack(cocos2d::Ref* pSender);
	void menuWeaponCallBack(cocos2d::Ref* pSender);
	void menuEnemyCallBack(cocos2d::Ref* pSender);
};

#endif // !_SECURITYMAP_SCENE_H

