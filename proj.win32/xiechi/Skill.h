#ifndef SKILL_H_
#define SKILL_H_
#include"cocos2d.h"
#include"MonsterManager.h"
USING_NS_CC;
class Skill :public Node
{
public:
	Skill();
	~Skill();
	void SkillTo(Node* target) { m_target = target; }
	void skillCool();
	void coolDown();
	void effectExplosion();
	Sequence* skill01(Point position);
	void skill02(Point position);
	void skill03(Point position);
	void onEnter();
	void onExit();
	void timeReset();//wei
	virtual bool init();
	CREATE_FUNC(Skill);
	bool isCool();


private:
	//Size visibleSize;
	bool m_isCool;
	Node* m_target;
	CCParticleMeteor* m_meteor;
};
#endif
