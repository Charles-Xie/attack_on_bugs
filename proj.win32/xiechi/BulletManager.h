#ifndef BULLETMANAGER_H_
#define BULLETMANAGER_H_
#include "cocos2d.h"
#include "Bullet.h"
#include "Tower.h"
#include "TollgateScene.h"
#define MAX_BULLET_NUM 20
USING_NS_CC;
class BulletManager :public Node
{
public:
	BulletManager();
	~BulletManager();
	CREATE_FUNC(BulletManager);
	bool init();
	void createBullet();
	void allocateBullet();
	virtual void update(float delta);
private:
	Array *m_bulletArr;
};
#endif
