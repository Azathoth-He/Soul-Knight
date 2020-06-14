#include "HRocker.h"

USING_NS_CC;

HRocker* HRocker::createHRocker(Point position)
{
	HRocker* rocker = HRocker::create();
	if (rocker)
	{
		rocker->rockerInit(position);
		return rocker;
	}
	CC_SAFE_DELETE(rocker);
	return NULL;
}

void HRocker::rockerInit(Point position)
{
	scheduleUpdate();

	Sprite* bg = Sprite::create("rockerBg.png");
	bg->setVisible(false);
	bg->setPosition(position);
	bg->setOpacity(70);
	addChild(bg, 0, 30);

	Sprite* rocker = Sprite::create("rocker.png");
	rocker->setVisible(false);
	rocker->setPosition(position);
	rocker->setOpacity(180);
	addChild(rocker, 1, 40); 
	
	bgPosition = bg->getPosition();
	bgRadius = bg->getContentSize().width / 2;
	listenerKeyBoard = EventListenerKeyboard::create();

	// 绑定监听事件
	listenerKeyBoard->onKeyPressed = CC_CALLBACK_2(HRocker::onPressKey, this);
	listenerKeyBoard->onKeyReleased = CC_CALLBACK_2(HRocker::onReleaseKey, this);
}
 
void HRocker::startRocker(bool _isStopOther)
{ 
	Sprite* bg = (Sprite*)getChildByTag(30);
	bg->setVisible(true);

	Sprite* rocker = (Sprite*)getChildByTag(40);
	rocker->setVisible(true);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listenerKeyBoard, 2);

}

void HRocker::stopRocker()
{ 
	Sprite* bg = (Sprite*)getChildByTag(30);
	bg->setVisible(false);

	Sprite* rocker = (Sprite*)getChildByTag(40);
	rocker->setVisible(false);
}

bool HRocker::updateState(EventKeyboard::KeyCode keyCode, bool type)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	{
		if (type)
		{
			_wState = true;
			_sState = false;
		}
		else if (!type)
		{
			_wState = false;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_A:
	{
		if (type)
		{
			_aState = true;
			_dState = false;
		}
		else if (!type)
		{
			_aState = false;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_S:
	{
		if (type)
		{
			_sState = true;
			_wState = false;
		}
		else if (!type)
		{
			_sState = false;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		if (type)
		{
			_dState = true;
			_aState = false;
		}
		else if (!type)
		{
			_dState = false;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_J:
	{
		if (type)
		{
			_jState = true;
		}
		else if (!type)
		{
			_jState = false;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_O:
	{
		if (type)
		{
			_oState = true;
		}
		else if (!type)
		{
			_oState = false;
		}
		break;
	}
	default:
		break;
	}
	return true;
}

bool HRocker::onPressKey(EventKeyboard::KeyCode keyCode, Event* envet)
{
	updateState(keyCode, 1);
	Sprite* rocker = (Sprite*)getChildByTag(40);
	Sprite* bg = (Sprite*)getChildByTag(30);

	rocker->stopAllActions();
	_available= true;
	Point point;

	if ((!_wState)&&(!_aState)&&(!_sState)&&(!_dState))
	{
		_available = false;
		return false;
	}

	if (_sState)
	{
		if (_aState)
			point = Point(bgPosition.x - bgRadius, bgPosition.y - bgRadius);
		else if (_dState)
			point = Point(bgPosition.x + bgRadius, bgPosition.y - bgRadius);
		else
			point = Point(bgPosition.x, bgPosition.y - bgRadius);
	}
	else if (_wState)
	{
		if (_aState)
			point = Point(bgPosition.x - bgRadius, bgPosition.y + bgRadius);
		else if (_dState)
			point = Point(bgPosition.x + bgRadius, bgPosition.y + bgRadius);
		else
			point = Point(bgPosition.x, bgPosition.y + bgRadius);
	}
	else if (_aState)
		point = Point(bgPosition.x - bgRadius, bgPosition.y);
	else if (_dState)
		point = Point(bgPosition.x + bgRadius, bgPosition.y);

	_angle = getRadius(bgPosition, point);
	

	return true;
}

bool HRocker::onReleaseKey(EventKeyboard::KeyCode keyCode, Event* envet)
{
	updateState(keyCode, 0);
	if (!_available)
	{
		return true;
	}

	Sprite* bg = (Sprite*)getChildByTag(30);
	Sprite* rocker = (Sprite*)getChildByTag(40);

	if ((!_wState) && (!_aState) && (!_sState) && (!_dState))
	{
		rocker->stopAllActions();
		rocker->runAction(MoveTo::create(0.08, bg->getPosition()));
		_available = false;
	}
	else
	{
		rocker->stopAllActions();
		_available = true;
		Point point;
		if (_sState)
		{
			if (_aState)
				point = Point(bgPosition.x - bgRadius, bgPosition.y - bgRadius);
			else if (_dState)
				point = Point(bgPosition.x + bgRadius, bgPosition.y - bgRadius);
			else
				point = Point(bgPosition.x, bgPosition.y - bgRadius);
		}
		else if (_wState)
		{
			if (_aState)
				point = Point(bgPosition.x - bgRadius, bgPosition.y + bgRadius);
			else if (_dState)
				point = Point(bgPosition.x + bgRadius, bgPosition.y + bgRadius);
			else
				point = Point(bgPosition.x, bgPosition.y + bgRadius);
		}
		else if (_aState)
			point = Point(bgPosition.x - bgRadius, bgPosition.y);
		else if (_dState)
			point = Point(bgPosition.x + bgRadius, bgPosition.y);
		
		_angle = getRadius(bgPosition, point);
	}
	return true;
}

Point HRocker::getAnglePosition(float r, float angle)
{
	return ccp(r * cos(angle), r * sin(angle));
}

float HRocker::getRadius(Point pos1, Point pos2)
{
	//得到两点的坐标x,y坐标值
	float x1 = pos1.x;
	float y1 = pos1.y;
	float x2 = pos2.x;
	float y2 = pos2.y;

	//求出两边长度
	float x = x2 - x1;
	float y = y1 - y2;

	//距离
	float distance = sqrt(pow(x, 2) + pow(y, 2));
	float cos = x / distance;

	//反三角
	float rad = acos(cos);

	if (y1 > y2)
	{
		rad = -rad;
	}

	return rad;
}

void HRocker::update(float dt)
{
	Sprite* bg = (Sprite*)getChildByTag(30);

	Sprite* rocker = (Sprite*)getChildByTag(40);

	bgPosition = bg->getPosition();

	rocker->setPosition(ccpAdd(getAnglePosition(bgRadius, _angle),
		ccp(bgPosition.x, bgPosition.y)));
}