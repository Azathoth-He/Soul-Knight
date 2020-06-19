#ifndef __CHOOSEHERO_SCENE_H__
#define __CHOOSEHERO_SCENE_H__

#include"cocos2d.h"
#include"HeroMessageScene.h"
#include"Actor/Hero.h"
#include"Scene/BattleMapScene.h"

USING_NS_CC;

class BattleMap;

class ChooseHero : public cocos2d::Scene
{
    CC_SYNTHESIZE(int, _money, Money);
    cocos2d::TMXTiledMap* seMap;
    Hero _archer;
    Hero _paladin;
    Hero _berserker;
public:
    static cocos2d::Scene* createScene(int money);
    static ChooseHero* createByBattleMap(BattleMap* combatScene);
    static ChooseHero* create(int money);
    virtual bool init(int money);
    bool initHero(BattleMap* combatScene);
    void chooseCallBack(const std::string hero);
    
};

#endif
