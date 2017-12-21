#ifndef BULLET_H_
#define BULLET_H_
#include "cocos2d.h"
#include "Monster.h"
USING_NS_CC;
class Bullet :public Entity
{
public:
	Bullet();
	~Bullet();
	CREATE_FUNC(Bullet);
	virtual bool init();

	virtual void show();
	virtual void hide();
	virtual void reset();

private:
	int m_iHarm;
	PhysicsBody *bulletBody;
};
#endif

