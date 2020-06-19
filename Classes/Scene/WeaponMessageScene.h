#ifndef _WEAPONSSAGE_SCENE_H
#define _WEAPONSSAGE_SCENE_H

#include"cocos2d.h"

USING_NS_CC;

class WeaponMessage :public cocos2d::Layer
{
    int page;
    cocos2d::ValueMap weaponData;
public:
    virtual bool init();
    static cocos2d::Scene* scene(CCRenderTexture* sqr);
    void initData();
    CREATE_FUNC(WeaponMessage);
    void menuNextPageCallback(cocos2d::Ref* pSender);
    void menuPreviousPageCallback(cocos2d::Ref* pSender);
    void menuExitCallback(cocos2d::Ref* pSender);
    void updateData();
};
#endif
#pragma once
