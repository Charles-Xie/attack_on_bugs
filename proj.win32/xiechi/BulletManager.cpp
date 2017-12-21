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

		//���浽�ӵ��б��з������
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

		/*ת���������˵ķ���*/
		

		Point shootDirection = t->getLocation() - start;
		Point normShootDirection = shootDirection.getNormalized();

		float radian = atan2(normShootDirection.y, -normShootDirection.x);
		float degree = CC_RADIANS_TO_DEGREES(radian);

		//������ת�ٶ�
		const float rotateSpeed = 6 * M_PI;
		//��תʱ��
		float rotateDuration = fabs(radian / rotateSpeed);
		//ʹ������ת
		TollgateScene::getTower()->runAction(RotateTo::create(rotateDuration, degree - 90));

		//������Ч
		auto explosion = CCParticleSun::create();
		explosion->setTexture(CCTextureCache::sharedTextureCache()->addImage("pow1.png"));
		explosion->setPosition(start+normShootDirection*100);
		explosion->setAutoRemoveOnFinish(true);
		explosion->setDuration(0.1f);
		addChild(explosion);
		
		//������Ч
		//SimpleAudioEngine::sharedEngine()->playEffect("throw.wav");
		
		//λ��ʸ��
		Point shootVector = normShootDirection * 700;
		Point end = shootVector + start;
		float moveDistance = start.getDistance(end);
		float moveSpeed = 200;
		//�ڵ�����ʱ��
		float moveDuration = moveDistance / moveSpeed;

		Object* obj = NULL;
		Bullet *bullet = NULL;

		CCARRAY_FOREACH(m_bulletArr, obj) {
			bullet = (Bullet*)obj;

//			if (bullet->isInScreen())
//			{
//				Point start = bullet->getPosition(); //��ȡ����λ��
////				Point direction = bullet->getDirection();//��ȡ�����ƶ�����
////				bullet->setPosition(start + direction);//�����ƶ�
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

			/*�ӵ����ڽ�����,��ʹ����������ֲ������λ���ƶ�*/
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
