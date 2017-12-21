#include "Background2.h"
Background::Background()
{
	m_iHP = 100;
}

Background::~Background()
{

}

bool Background::init()
{
	auto playersp = Sprite::create("HelloWorld.png");
	this->addChild(playersp);
	auto body = PhysicsBody::createCircle(playersp->getContentSize().width * 0.4f);
	body->getShape(0)->setFriction(0);
	body->getShape(0)->setRestitution(1.0f);
	body->setCategoryBitmask(1);
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);
	this->setPhysicsBody(body);
	this->getPhysicsBody()->applyImpulse(Vect(0, 0));

	return true;
}

void Background::BackToGame()
{

}

void Background::logic(float dt)
{

}