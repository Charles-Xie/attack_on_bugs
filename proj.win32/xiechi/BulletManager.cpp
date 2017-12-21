#include "BulletManager.h"
#include"SimpleAudioEngine.h"
#include <math.h>
using namespace CocosDenshion;


BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

bool BulletManager::init()
{
	bool isInit = false;
	do {
		createBullet();
//		scheduleUpdate();

		allocateBullet();

		isInit = true;
	} while (0);

	return isInit;
}

void BulletManager::createBullet()
{
	m_bulletArr = Array::create();
	m_bulletArr->retain();

	Bullet *bullet = NULL;
	Sprite *sprite = NULL;

	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bullet = Bullet::create();
		bullet->bindSprite(Sprite::create("bullet.png"));
		bullet->reset();

		addChild(bullet);

		//保存到子弹列表中方便管理
		m_bulletArr->addObject(bullet);
	}
}

void BulletManager::update(float delta)
{
}


void BulletManager::allocateBullet()
{
	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t, Event *e) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point start = Point(visibleSize.width / 2, visibleSize.height / 2);

		/*转动塔到敌人的方向*/
		

		Point shootDirection = t->getLocation() - start;
		Point normShootDirection = shootDirection.getNormalized();

		float radian = atan2(normShootDirection.y, -normShootDirection.x);
		float degree = CC_RADIANS_TO_DEGREES(radian);

		//设置旋转速度
		const float rotateSpeed = 6 * M_PI;
		//旋转时长
		float rotateDuration = fabs(radian / rotateSpeed);
		//使炮塔旋转
		TollgateScene::getTower()->runAction(RotateTo::create(rotateDuration, degree - 90));

		//开火特效
		auto explosion = CCParticleSun::create();
		explosion->setTexture(CCTextureCache::sharedTextureCache()->addImage("pow1.png"));
		explosion->setPosition(start+normShootDirection*100);
		explosion->setAutoRemoveOnFinish(true);
		explosion->setDuration(0.1f);
		addChild(explosion);
		
		//开火音效
		//SimpleAudioEngine::sharedEngine()->playEffect("throw.wav");
		
		//位移矢量
		Point shootVector = normShootDirection * 700;
		Point end = shootVector + start;
		float moveDistance = start.getDistance(end);
		float moveSpeed = 200;
		//炮弹发射时长
		float moveDuration = moveDistance / moveSpeed;

		Object* obj = NULL;
		Bullet *bullet = NULL;

		CCARRAY_FOREACH(m_bulletArr, obj) {
			bullet = (Bullet*)obj;

//			if (bullet->isInScreen())
//			{
//				Point start = bullet->getPosition(); //获取怪物位置
////				Point direction = bullet->getDirection();//获取怪物移动向量
////				bullet->setPosition(start + direction);//怪物移动
//			}
//			else {
//				bullet->reset();
//				bullet->show();
//			}
//			Tower* tower = TollgateScene::getTower();
//			if (bullet->isCollideWithOther(tower)) {
//				bullet->hide();
//				tower->hit();
//			}

			/*子弹不在界面内,则使其在中央出现并朝点击位置移动*/
			if (!bullet->isVisible())
			{
				bullet->reset();
				bullet->show();

				CallFunc *moveDone = CallFunc::create([bullet]{
					bullet->hide();
				});
				Sequence *moveAndDone = Sequence::create(MoveTo::create(moveDuration, end), moveDone, NULL);
				moveAndDone->setTag(1);
				bullet->runAction(moveAndDone);


				break;
			}
		}

		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
