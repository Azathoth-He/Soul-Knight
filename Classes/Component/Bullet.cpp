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

void Bullet::shootBullet(int dir)
{
	shootDir = dir;
	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void Bullet::update(float dt)
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	if (shootDir == 0)
		this->setPosition(Vec2(this->getPosition() + _velocity * dt));
	else if (shootDir == 1)
		this->setPosition(Vec2(this->getPosition() - _velocity * dt));
	
}