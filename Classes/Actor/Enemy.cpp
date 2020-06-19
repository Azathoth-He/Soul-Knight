#include"Enemy.h"

Enemy* Enemy::create(const std::string& fileName, const std::string& enemyName, BattleMap* combatScene)
{
	Enemy* sprite = new(std::nothrow) Enemy();
	if (sprite && sprite->init(fileName, enemyName, combatScene))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Enemy::init(const std::string& fileName, const std::string& enemyName, BattleMap* combatScene)
{
	if (!Sprite::initWithFile(fileName))
	{
		return false;
	}

	scheduleUpdate();

	_combatScene = combatScene;
	_enemyName = enemyName;
	_isAvailable = true;

	initEnemyData();

	return true;
}

void Enemy::initEnemyData()
{
	cocos2d::ValueMap value = cocos2d::FileUtils::getInstance()->getValueMapFromFile("hero_enemy\\EnemyData.plist");
	auto EnemyData = value.at(_enemyName).asValueMap();

	_attack = EnemyData["attack"].asValueVector().at(0).asInt();
	_attackRate = EnemyData["attackRate"].asValueVector().at(0).asFloat();
	_mode = EnemyData["mode"].asValueVector().at(0).asInt();
	_health = EnemyData["health"].asValueVector().at(0).asInt();
	_bulletNum = EnemyData["bulletNum"].asValueVector().at(0).asInt();
	_bulletV = EnemyData["bulletV"].asValueVector().at(0).asInt();
	_moveSpeed = EnemyData["moveSpeed"].asValueVector().at(0).asInt();
}

void Enemy::update(float dt)
{
	if (_isAvailable)
	{
		updatePosition();
		attack();
		if (_combatScene->getMyHero().getMyWeapon()->getMode() == 2)
			beAttackedByBullet();
	}
}

void Enemy::updatePosition()
{

	/*if (_mode == 1)
	{
		auto oldPosition = this->getPosition();
		auto direction = _combatScene->_armature->getPosition() - oldPosition;
		auto distance = pow(pow(direction.x, 2) + (pow(direction.y, 2)), 1 / 2);
		if (distance == 0)
			distance = 1;
		auto newPosition = oldPosition + Vec2(direction.x / distance * _moveSpeed / 3000,
			direction.y / distance * _moveSpeed / 3000);

		MapInformation mapInfo;
		bool isBorder = mapInfo.checkBorder((TMXTiledMap*)_combatScene->getMap(), newPosition);

		if (isBorder);
		else
		{
			if (direction.x < 0)
			{
				dir = 1;
				this->setFlipX(true);
			}
			else if (direction.x > 0)
			{
				dir = 0;
				this->setFlipX(false);
			}
			this->setPosition(newPosition);
		}
	}*/

	_nowTime = GetCurrentTime();
	auto oldPosition = this->getPosition();
	if (_nowTime - _lastMoveTime > 1000)
	{
		float random1 = 2 * CCRANDOM_0_1() - 1.0;
		float random2 = 2 * CCRANDOM_0_1() - 1.0;
		direction = Vec2(random1, random2);
		_lastMoveTime = GetCurrentTime();
	}
	auto newPosition = oldPosition + direction * _moveSpeed / 10;

	MapInformation mapInfo;
	bool isBorder = mapInfo.checkBorder((TMXTiledMap*)_combatScene->getMap(), newPosition);

	if (isBorder);
	else
	{
		if (direction.x < 0)
		{
			dir = 1;
			this->setFlipX(true);
		}
		else if (direction.x > 0)
		{
			dir = 0;
			this->setFlipX(false);
		}
			this->setPosition(newPosition);
	}
}

void Enemy::attack()
{
	if (_mode == 2)
	{
		_nowTime = GetCurrentTime();

		if ((_nowTime - _lastAttackTime) >= _attackRate * 1000)
		{
			std::string fileName = StringUtils::format("weapon/bullet%d.png", _bulletNum);
			Bullet* bullet = Bullet::create(fileName);
			bullet->setVelocity(Vec2(_bulletV, 0));
			bullet->setPosition(this->getPosition());
			bullet->setVisible(true);

			if (dir == 1)
				bullet->setFlipX(true);

			_combatScene->addChild(bullet);
			bullet->shootBullet(dir, 1, _attack, _combatScene->getMap());
			_combatScene->_bullets.pushBack((Bullet*)bullet);

			_lastAttackTime = GetCurrentTime();
		}
	}
	
}

void Enemy::beAttackedByBullet()
{
	for (int i = 0; i < _combatScene->_bullets.size(); i++)
	{
		Bullet* bullet = _combatScene->_bullets.at(i);
		if (bullet->_camp == 0 && bullet->isVisible())
		{
			Rect crEnemy = this->boundingBox();
			Rect crBullet = bullet->boundingBox();

			if (crEnemy.intersectsRect(crBullet))	//是否存在交集
			{
				int health = this->getHealth() - bullet->_attack;
				if (health <= 0)
						die();
				this->setHealth(health);
				bullet->setVisible(false);
			}
		}
	}
}

void Enemy::die()
{
	_combatScene->_killEnemy++;
	Vec2 position = this->getPosition();
	_combatScene->setMyMoney(_combatScene->getMyMoney() + 100);
	this->setVisible(false);
	this->removeFromParent();
	this->retain();
	float random = CCRANDOM_0_1();
	if (random < 0.5 && random >= 0)
	{
		Prop* prop = Prop::create("redBottle.png");
		prop->setAddHealth(2);
		prop->setAddMagic(0);
		prop->setAddShield(2);
		prop->setPosition(position);
		_combatScene->_props.pushBack(prop);
		_combatScene->addChild(prop);
	}
	else if (random >= 0.5 && random <= 1.0)
	{
		Prop* prop = Prop::create("buleBottle.png");
		prop->setAddHealth(0);
		prop->setAddMagic(50);
		prop->setAddShield(2);
		prop->setPosition(position);
		_combatScene->_props.pushBack(prop);
		_combatScene->addChild(prop);
	}

}

void Enemy::beAttackedByweapon()
{
	Rect crEnemy = this->boundingBox();
	Rect crWeapon = _combatScene->_armature->getBoundingBox();
	
	if (crEnemy.intersectsRect(crWeapon))	//是否存在交集
	{
		int health = this->getHealth() - _combatScene->getMyHero().getMyWeapon()->getAttack();
		if (health <= 0)
			die();
		this->setHealth(health);
	}
}