#include "MapInformation.h"

bool MapInformation::checkBorder(TMXTiledMap* map, Vec2 position)
{
	auto _collidable = map->getLayer("collision");

	//像素点坐标转化为瓦片坐标
	Vec2 tileCoord = this->tileCoordFromPosition(map, position);
	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);
	
	//判断瓦片是否存在
	if (tileGid > 0)
	{
		Value prop = map->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		
		std::string collision = propValueMap["collision"].asString();

		if (collision == "true")
		{
			return true;
		}
		else
			return false;
	}
	return false;
}

bool MapInformation::checkDraw(TMXTiledMap* map, Vec2 position)
{
	auto _draw = map->getLayer("collision");
	Vec2 tileCoord = this->tileCoordFromPosition(map, position);
	int tileGid = _draw->getTileGIDAt(tileCoord);
	if (tileGid > 0)
	{
		Value prop = map->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string draw = propValueMap["draw"].asString();

		if (draw == "true")
		{
			return true;
		}
		else
			return false;
	}
	return false;
}

bool MapInformation::checkNewScene(TMXTiledMap* map, Vec2 position)
{
	auto _new = map->getLayer("collision");
	Vec2 tileCoord = this->tileCoordFromPosition(map, position);
	int tileGid = _new->getTileGIDAt(tileCoord);
	if (tileGid > 0)
	{
		Value prop = map->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string newScene = propValueMap["new"].asString();

		if (newScene == "true")
		{
			return true;
		}
		else
			return false;
	}
	return false;
}


Vec2 MapInformation::tileCoordFromPosition(TMXTiledMap* map, Vec2 position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) /
		map->getTileSize().height;

	return Vec2(x, y);
}