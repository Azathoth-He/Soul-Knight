#ifndef __HEROMESSAGE_SCENE_H__
#define __HEROMESSAGE_SCENE_H__

#include"cocos2d.h"
#include"../Actor/Hero.h"
#include"SecurityMapScene.h"

USING_NS_CC;

class HeroMessage :public cocos2d::Scene
{
	CC_SYNTHESIZE(Hero*, myHero, MyHero);
	CC_SYNTHESIZE(int, myMoney, MyMoney);
	CC_SYNTHESIZE(std::string, heroName, HeroName);
	
	
public:
	static cocos2d::Scene* createScene(const std::string hero);
	static HeroMessage* create(const std::string hero);
	virtual bool init(const std::string hero);
	virtual void update(float dt);
	void upLevelCallBack();
	void nextCallBack();

	
};

#endif
#pragma once
