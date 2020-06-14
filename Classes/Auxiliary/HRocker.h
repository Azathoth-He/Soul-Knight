#ifndef __HROCKER_H__
#define __HROCKER_H__

#include "cocos2d.h" 

USING_NS_CC;

class HRocker : public Layer
{
private:
	//是否可操作
	CC_SYNTHESIZE(bool, _available, Available);
	//摇杆与触屏点角度
	CC_SYNTHESIZE(float, _angle, Angle);

	//背景坐标  
	CC_SYNTHESIZE(Point, bgPosition, BgPoistion);
	//背景半径  
	CC_SYNTHESIZE(float, bgRadius, BgRadius);
	//按键状态
	bool _wState, _aState, _sState, _dState, _jState, _oState;

	//键盘监听器
	EventListenerKeyboard* listenerKeyBoard;

	void rockerInit(Point position);
	//得到半径为r的圆周运动上一个角度应对应的x,y坐标  
	Point getAnglePosition(float r, float angle);

	float getRadius(Point pos1, Point pos2);

	//按键事件
	virtual bool onPressKey(EventKeyboard::KeyCode keyCode, Event* envet);
	virtual bool onReleaseKey(EventKeyboard::KeyCode keyCode, Event* envet);
	virtual bool updateState(EventKeyboard::KeyCode keyCode, bool type);

public:
	//创建摇杆
	static HRocker* createHRocker(Point position);
	//启动摇杆  
	void startRocker(bool _isStopOther);
	//停止摇杆  
	void stopRocker();


	void update(float dt);

	CREATE_FUNC(HRocker);
};

#endif