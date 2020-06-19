#ifndef _ENEMYMESSAGE_SCENE_H
#define _ENEMYMESSAGE_SCENE_H

#include"cocos2d.h"

USING_NS_CC;

class EnemyMessage :public cocos2d::Layer
{
    int page;
    cocos2d::ValueMap enemyData;
public:
    virtual bool init();
    static cocos2d::Scene* scene(CCRenderTexture* sqr);
    void initData();
    CREATE_FUNC(EnemyMessage);
    void menuNextPageCallback(cocos2d::Ref* pSender);
    void menuPreviousPageCallback(cocos2d::Ref* pSender);
    void menuExitCallback(cocos2d::Ref* pSender);
    void updateData();
};

#endif // !_ENEMYMESSAGE_SCENE_H

#pragma once
