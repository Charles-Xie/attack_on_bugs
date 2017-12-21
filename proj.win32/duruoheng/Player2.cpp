#include "Player2.h"
Player::Player()
{
	m_iHP = 100;
}

Player::~Player()
{

}

bool Player::init()
{
	auto playersp = Sprite::create("Player.png");
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

void Player::moveToRight()
{
	this->getPhysicsBody()->applyImpulse(Vect(50000, 0));
}

void Player::moveToLeft()
{
	this->getPhysicsBody()->applyImpulse(Vect(-500000, 0));
}

void Player::quickMove()
{
	this->getPhysicsBody()->applyImpulse(Vect(0, 200000));
}

void Player::logic(float dt)
{

}