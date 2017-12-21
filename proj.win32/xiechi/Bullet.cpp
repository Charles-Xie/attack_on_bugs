#include "Bullet.h"



Bullet::Bullet()
{
	m_iHarm = 100;
}


Bullet::~Bullet()
{
}


bool Bullet::init()
{
	Sprite *s = Sprite::create("bullet.png");

	bulletBody = PhysicsBody::createCircle(s->getContentSize().width/2);
	bulletBody->setEnabled(false);
	bulletBody->setGravityEnable(false);
	bulletBody->setCollisionBitmask(0x00000000);
	bulletBody->setContactTestBitmask(0x01);

	setPhysicsBody(bulletBody);
	setTag(2);
	setVisible(false);

	return true;
}

void Bullet::show()
{
	if (getSprite() != NULL)
	{
		setVisible(true);
		bulletBody->setEnabled(true);
	}
}

void Bullet::hide()
{
	if (getSprite() != NULL)
	{
		stopActionByTag(1);
		setVisible(false);
		bulletBody->setEnabled(false);
		reset();
	}

}

void Bullet::reset()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (getSprite() != NULL)
	{
		setPosition(visibleSize.width / 2, visibleSize.height / 2);
	}
}