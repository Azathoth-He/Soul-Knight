#pragma once
#ifndef _MAPINFORMATION_H_
#define _MAPINFORMATION_H

#include"cocos2d.h"

USING_NS_CC;

class MapInformation
{
	Vec2 tileCoordFromPosition(TMXTiledMap* map, Vec2 position);
public:
	bool checkBorder(TMXTiledMap* map, Vec2 position);
	bool checkDraw(TMXTiledMap* map, Vec2 position);
	bool checkNewScene(TMXTiledMap* map, Vec2 position);
};

#endif // !_MAPINFORMATION_H_
