#ifndef __HEROMESSAGE_SCENE_H__
#define __HEROMESSAGE_SCENE_H__

#include"cocos2d.h"
#include"../Actor/Hero.h"
#include"SecurityMapScene.h"
#include"ChooseHeroScene.h"

USING_NS_CC;

class ChooseHero;

class HeroMessage :public cocos2d::Scene
{
	CC_SYNTHESIZE(Hero, myHero, MyHero);
	CC_SYNTHESIZE(int, myMoney, MyMoney);
	CC_SYNTHESIZE(std::string, heroName, HeroName);
	
	Hero _archer;
	Hero _paladin;
	Hero _berserker;
	
public:
	static cocos2d::Scene* createScene(const std::string hero,ChooseHero* scene);
	static HeroMessage* create(const std::string hero, ChooseHero* scene);
	virtual bool init(const std::string hero, ChooseHero* scene);
	virtual void update(float dt);
	void upLevelCallBack();
	void nextCallBack();

	
};

#endif
#pragma once
