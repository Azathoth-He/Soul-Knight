#ifndef _GAMEPAUSE_SCENE_H
#define _GAMEPAUSE_SCENE_H

#include"cocos2d.h"

USING_NS_CC;

class GamePause :public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene(CCRenderTexture* sqr);
    CREATE_FUNC(GamePause);
    //¼ÌÐøÓÎÏ·
    void menuContinueCallback(cocos2d::Ref* pSender);
    void menuExitCallback(cocos2d::Ref* pSender);
    void menuMusicCallBack(cocos2d::Ref* pSender);
};

#endif // !_GAMEPAUSE_SCENE_H


#pragma once
