#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"cocos2d.h"
#include"Scene/BattleMapScene.h"
#include"Auxiliary/MapInformation.h"
#include <cmath>
#include"Component/Prop.h"

USING_NS_CC;

//��ս
#define MELEE 1
//Զ��
#define REMOTE 2

class BattleMap;

class Enemy :public cocos2d::Sprite
{
	BattleMap* _combatScene;

	CC_SYNTHESIZE(std::string, _enemyName, EnemyName);
	//����ֵ
	CC_SYNTHESIZE(int, _health, Health);
	//�Ƿ���ƶ�
	CC_SYNTHESIZE(bool, _isAvailable, IsAvailable);
	//�ƶ��ٶ�
	CC_SYNTHESIZE(int, _moveSpeed, MoveSpeed);
	//������
	CC_SYNTHESIZE(int, _attack, Attack);
	//����(�������)
	CC_SYNTHESIZE(float, _attackRate, AttackRate);
	//������ʽ
	CC_SYNTHESIZE(int, _mode, Mode);
	//�ӵ��ٶ�
	CC_SYNTHESIZE(int, _bulletV, BulletV);
	//�ӵ����
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
