#ifndef __HROCKER_H__
#define __HROCKER_H__

#include "cocos2d.h" 

USING_NS_CC;

class HRocker : public Layer
{
private:
	//�Ƿ�ɲ���
	CC_SYNTHESIZE(bool, _available, Available);
	//ҡ���봥����Ƕ�
	CC_SYNTHESIZE(float, _angle, Angle);

	//��������  
	CC_SYNTHESIZE(Point, bgPosition, BgPoistion);
	//�����뾶  
	CC_SYNTHESIZE(float, bgRadius, BgRadius);
	//����״̬
	bool _wState, _aState, _sState, _dState, _jState, _oState;

	//���̼�����
	EventListenerKeyboard* listenerKeyBoard;

	void rockerInit(Point position);
	//�õ��뾶Ϊr��Բ���˶���һ���Ƕ�Ӧ��Ӧ��x,y����  
	Point getAnglePosition(float r, float angle);

	float getRadius(Point pos1, Point pos2);

	//�����¼�
	virtual bool onPressKey(EventKeyboard::KeyCode keyCode, Event* envet);
	virtual bool onReleaseKey(EventKeyboard::KeyCode keyCode, Event* envet);
	virtual bool updateState(EventKeyboard::KeyCode keyCode, bool type);

public:
	//����ҡ��
	static HRocker* createHRocker(Point position);
	//����ҡ��  
	void startRocker(bool _isStopOther);
	//ֹͣҡ��  
	void stopRocker();


	void update(float dt);

	CREATE_FUNC(HRocker);
};

#endif