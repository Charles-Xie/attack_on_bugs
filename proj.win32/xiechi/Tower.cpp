#include "Tower.h"

int Tower::max_iHP = 1000;
int Tower::heal_iHP = 300;
int Tower::hurt_iHP = 100;

Tower::Tower()
{
}


Tower::~Tower()
{
}

bool Tower::init()
{
	m_iHP = max_iHP;

	Sprite *picSize = Sprite::create("wei.png");    //用于设置刚体大小

	towerBody = PhysicsBody::createCircle(picSize->getContentSize().width / 2);
	towerBody->setGravityEnable(false);
	towerBody->setCollisionBitmask(0x00000000);
	towerBody->setContactTestBitmask(0x01);

	setPhysicsBody(towerBody);
	setTag(3);
	return true;
}

void Tower::isHurt()
{
	if (getSprite() != NULL&&m_iHP >= hurt_iHP)
	{
		m_iHP -= hurt_iHP;
	}
}

void Tower::isHealed()
{
	if (getSprite() != NULL&&m_iHP > 0)
	{
		if (m_iHP >= (max_iHP - heal_iHP))
			m_iHP = max_iHP;
		else m_iHP += heal_iHP;
	}
}

int Tower::getiHP()
{
	return m_iHP;
}


void Tower::show()
{
}

void Tower::hide()
{
}

void Tower::reset()
{
}

int Tower::getMaxHP()
{
	return max_iHP;
}