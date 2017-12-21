#pragma once
#include"cocos2d.h"
#include"Entity.h"
#define MAX_MONSTER_NUM 6
USING_NS_CC;
class MonsterManager : public Node
{
public:
	MonsterManager();
	~MonsterManager();
	virtual bool init();
	CREATE_FUNC(MonsterManager);

	virtual void update(float delta);
	void killAll();
	int getDeadNum();
private:
	void createMonster();
private:
	Array* m_monsterArr;
	int deadNum;
	int maxMonsterNum;
	//	Array* m_bulletArr;

};


