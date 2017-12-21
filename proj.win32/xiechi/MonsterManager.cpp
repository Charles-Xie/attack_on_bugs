#include "MonsterManager.h"
#include "Monster.h"
#include "TollgateScene.h"
#include <stdlib.h>

MonsterManager::MonsterManager()
{
}


MonsterManager::~MonsterManager()
{
}

bool MonsterManager::init()
{
	bool bRet = false;
	do {
		maxMonsterNum = TollgateScene::rank*MAX_MONSTER_NUM;
		log("monster num %d", maxMonsterNum);
		deadNum = 0;
		createMonster();
		scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}

void MonsterManager::createMonster()
{
	m_monsterArr = Array::create();
	m_monsterArr->retain();

	Monster* monster = NULL;
	Sprite* sprite = NULL;
	srand(time(0));

	for (int i = 0; i < maxMonsterNum; i++) {
		monster = Monster::create();
		int randomMaxHP = (int)(5 * rand() / (RAND_MAX + 1.0)) + 1;   //产生一个1~4之间的随机数
		log("max hp,%d", randomMaxHP);
		if (randomMaxHP <= 2)
		{
			monster->bindSprite(Sprite::create("Bill.png"));
			monster->getSprite()->setScale(0.4);
		}
		else {
			monster->bindSprite(Sprite::create("John.png"));
			monster->getSprite()->setScale(0.4);
		}
		monster->reset();
		monster->setMaxHP(randomMaxHP);

		addChild(monster);

		//保存到怪物列表中方便管理
		m_monsterArr->addObject(monster);
		m_monsterArr->retain();

	}
}

void MonsterManager::update(float delta)
{
	Tower* tower = TollgateScene::getTower();
	Object* obj = NULL;
	Monster* monster = NULL;
	Size size = Director::getInstance()->getVisibleSize();
	Point center = Point(size.width / 2, size.height / 2);
	srand(time(0));
	CCARRAY_FOREACH(m_monsterArr, obj) {
		monster = (Monster*)obj;
		if (!monster->hasEffect())
		{
			if (!monster->isVisible())
			{
				monster->reset();
				int randomMaxHP = (int)(4 * rand() / (RAND_MAX + 1.0)) + 1;   //产生一个1~4之间的随机数
				log("max hp,%d", randomMaxHP);
				monster->setMaxHP(randomMaxHP);
				monster->show();
			}
		}
	}
}

void MonsterManager::killAll()
{
	deadNum = 0;
	Object* obj = NULL;
	Monster* monster = NULL;
	CCARRAY_FOREACH(m_monsterArr, obj) {
		monster = (Monster*)obj;
		if (monster->isVisible())
		{
			monster->hide();
			deadNum++;
		}
	}
}

int MonsterManager::getDeadNum()
{
	return deadNum;
}