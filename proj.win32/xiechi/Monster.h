#pragma once
#ifndef MONSTER_H_
#define MONSTER_H_
#include "Entity.h"
#include "ui\CocosGUI.h"
USING_NS_CC;
using namespace ui;

class Monster :public Entity
{
private:
	PhysicsBody *monsterBody;
	bool m_hasEffect;
	int monsterHP;
	int monsterMaxHP;
	Slider *HPslider;
	void createSlider();
	//void setSlider();               //ÐÞ¸ÄÑªÁ¿Ìõ
public:
	Monster();
	~Monster();
	virtual bool init();
	CREATE_FUNC(Monster);
	Point& getDirection();
	virtual void show();
	virtual void hide();
	virtual void reset();
	void getIntoTower();
	bool hasEffect();
	void setHasEffect(bool effect);
	void setMaxHP(int maxHP = 1);
	bool isDead();
	void isHurt();
	int getMaxHP();
};
#endif

