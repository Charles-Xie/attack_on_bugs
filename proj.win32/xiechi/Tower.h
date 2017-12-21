#ifndef TOWER_H_
#define TOWER_H_
#include "Entity.h"
#include "TollgateScene.h"
#include "EndScene.h"
class Tower :public Entity
{
public:
	Tower();
	~Tower();
	virtual bool init();
	CREATE_FUNC(Tower);
public:
	void isHurt();
	int getiHP();
	int getMaxHP();
	void isHealed();

	virtual void show();
	virtual void hide();
	virtual void reset();
private:
	int m_iHP;//ÑªÁ¿
	static int max_iHP;
	static int heal_iHP;
	static int hurt_iHP;

	PhysicsBody *towerBody;
};
#endif
