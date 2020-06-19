#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"cocos2d.h"
#include"Scene/BattleMapScene.h"
#include"Auxiliary/MapInformation.h"
#include <cmath>
#include"Component/Prop.h"

USING_NS_CC;

//近战
#define MELEE 1
//远程
#define REMOTE 2

class BattleMap;

class Enemy :public cocos2d::Sprite
{
	BattleMap* _combatScene;

	CC_SYNTHESIZE(std::string, _enemyName, EnemyName);
	//生命值
	CC_SYNTHESIZE(int, _health, Health);
	//是否可移动
	CC_SYNTHESIZE(bool, _isAvailable, IsAvailable);
	//移动速度
	CC_SYNTHESIZE(int, _moveSpeed, MoveSpeed);
	//攻击力
	CC_SYNTHESIZE(int, _attack, Attack);
	//攻速(攻击间隔)
	CC_SYNTHESIZE(float, _attackRate, AttackRate);
	//攻击方式
	CC_SYNTHESIZE(int, _mode, Mode);
	//子弹速度
	CC_SYNTHESIZE(int, _bulletV, BulletV);
	//子弹编号
	CC_SYNTHESIZE(int, _bulletNum, BulletNum);

	Vec2 direction;

	int dir = 0;
	int _lastMoveTime = 0;
	int _lastAttackTime = 0;
	int _nowTime = 0;

public:
	static Enemy* create(const std::string& fileName, const std::string& enemyName, BattleMap* combatScene);
	virtual bool init(const std::string& fileName, const std::string& enemyName, BattleMap* combatScene);
	void initEnemyData();
	void update(float dt);
	void updatePosition();
	void attack();
	void beAttackedByBullet();
	void beAttackedByweapon();
	void die();
};

#endif // !_ENEMY_H_


#pragma once
