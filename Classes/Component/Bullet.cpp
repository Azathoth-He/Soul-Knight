#include"Bullet.h"

Bullet* Bullet::create(const std::string& filename)
{
	Bullet* bullet = new (std::nothrow) Bullet();
	if (bullet && bullet->initWithFile(filename))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void Bullet::shootBullet(int dir, int camp, int attack, TMXTiledMap* map)
{
	shootDir = dir;
	_camp = camp;
	_attack = attack;
	_map = map;
	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void Bullet::update(float dt)
{
	MapInformation mapInfo;
	bool isBorder = mapInfo.checkBorder((TMXTiledMap*)_map, this->getPosition());
	if (!isBorder)
	{
		Size screenSize = Director::getInstance()->getVisibleSize();
		if (shootDir == 0)
			this->setPosition(Vec2(this->getPosition() + _velocity * dt));
		else if (shootDir == 1)
			this->setPosition(Vec2(this->getPosition() - _velocity * dt));
	}
	else
		this->setVisible(false);
}