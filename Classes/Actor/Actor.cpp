#include"Actor.h"

Actor* Actor::create()
{
	Actor* sprite = new (std::nothrow)Actor;
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Actor::init()
{
	return true;
}

void Actor::initState()
{

}

void Actor::die()
{

}

void Actor::move(Vec2 destination)
{

}