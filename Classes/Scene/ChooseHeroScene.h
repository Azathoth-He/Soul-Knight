#ifndef __CHOOSEHERO_SCENE_H__
#define __CHOOSEHERO_SCENE_H__

#include"cocos2d.h"
#include"HeroMessageScene.h"

USING_NS_CC;

class ChooseHero : public cocos2d::Scene
{
    cocos2d::TMXTiledMap* seMap;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void chooseCallBack(const std::string hero);
    CREATE_FUNC(ChooseHero);
};

#endif
