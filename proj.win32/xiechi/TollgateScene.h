#ifndef _TollgateScene_H_
#define _TollgateScene_H_
#include "cocos2d.h"
#include "Tower.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "PauseScene.h"
#include "EndScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "string.h"
#include "Skill.h"
USING_NS_CC;
using namespace ui;

class Tower;         //important, cannot be deleted

class TollgateScene :public Layer
{
public:
	TollgateScene();
	~TollgateScene();

	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(TollgateScene);

	static Tower* getTower();
	virtual void update(float delta);

	virtual void onEnter();
	virtual void onExit();

	bool onContactBegin(const PhysicsContact &contact);

	void createPauseButton();
	//	Player* m_player = Player::create();//ʵ������
	void touchButtonPause(Object* object, ui::TouchEventType type);//�ص�������������ͣ����

	void createSkill1();
	void createSkill2();
	void createSkill3();
	void touchSkill1(Object* object, ui::TouchEventType type);
	void touchSkill2(Object* object, ui::TouchEventType type);
	void touchSkill3(Object* object, ui::TouchEventType type);

	static int rank;
private:
	void initBG();//�ؿ�������ʼ��
private:
	static Tower* m_tower;
	Sprite *m_bgSprite;
	MonsterManager* m_monsterManager;

	int score = 0;//����
	void createScore();//�����Ʒְ�
	void addScore(int addNum = 1) { score+=addNum; };
	void decreScore(int decreNum = 1) { score -= decreNum; };
	Label* scoreLabel;//�Ʒְ�
	void showScore();//������תΪ�ַ�������str��ͨ��Label��ʾ

	Slider *HPslider;
	void createSlider();
	int HPpercent;
	Label* HPlabel;    //��ʾѪ��ֵ
	void showHP();

	//���ܰ�ť
	Button *btn1;
	Button *btn2;
	Button *btn3;
	Sprite *btn1Shadow;
	Sprite *btn2Shadow;
	Sprite *btn3Shadow;

	//��������
	Skill* m_skill01;
	Skill* m_skill02;
	Skill* m_skill03;
};
#endif