#ifndef _BATTLEMAP_SCENE_H_
#define _BATTLEMAP_SCENE_H_

#include"cocos2d.h"
#include"SecurityMapScene.h"
#include"../Auxiliary/HRocker.h"
#include"Actor/Enemy.h"
#include"Component/Bullet.h"
#include"Actor/Enemy.h"
#include"dragonBones/Engine/CCDragonBonesHeaders.h"
#include"ChooseHeroScene.h"
#include"Component/Prop.h"

USING_NS_CC;

class SecurityMap;
class Bullet;
class Enemy;
class Prop;
class dragonBones::CCArmatureDisplay;


class BattleMap :public cocos2d::Scene
{
	CC_SYNTHESIZE(TMXTiledMap*, _map, Map);
	CC_SYNTHESIZE(Hero, _myHero, MyHero);
	CC_SYNTHESIZE(int, _myMoney, MyMoney);
	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);
	dragonBones::CCArmatureDisplay* _armature;
	dragonBones::CCFactory* _factory;
	//µØÍ¼ÒÆ¶¯Æ«ÒÆÁ¿
	Vec2 _offset;
	int _killEnemy = 0;
	int dir = 0;
	int _oldTime = 0;
	int _nowTime = 0;
	int _lastChangeTime = 0;

	Hero _archer;
	Hero _paladin;
	Hero _berserker;

public:
	Vector<Bullet*> _bullets;
	Vector<Enemy*> _enemies;
	Vector<Weapon*> _weapons;
	Vector<Prop*> _props;
	Vector<Sprite*> _boxes;

	static cocos2d::Scene* createScene(SecurityMap* combatScene);
	static BattleMap* create(SecurityMap* combatScene);
	static BattleMap* createByBattleMap(BattleMap* combatScene);
	virtual bool init(SecurityMap* combatScene);
	bool initLevel2(BattleMap* combatScene);
	void initHRocker();
	void initIcon();
	void initStateBox();
	void initEnemy(int n);
	void initBox(int n);
	void update(float dt);
	void updateHeroState();
	void updateHeroPosition();
	void updateHeroDirction();
	void updateOthers();
	void updateEnemy();
	void generateWeapon();
	void getProp();
	void heroAttack();
	void heroDie();
	void attackHero();
	void setViewpointCenter(Vec2 position);
	void menuPauseCallBack(cocos2d::Ref* pSender);
	void turnNextStep();
	void changeWeapon();
	void over();
};


#endif // !_BATTLEMAP_SCENE_H_

#pragma once
