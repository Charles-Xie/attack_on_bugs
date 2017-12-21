#include "TollgateScene.h"
#include "ui/CocosGUI.h"
#include"cocos2d.h"
USING_NS_CC;
#include"SimpleAudioEngine.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
using namespace CocosDenshion;
using namespace ui;

int TollgateScene::rank = 1;
Tower *TollgateScene::m_tower = NULL;

TollgateScene::TollgateScene()
{
}


TollgateScene::~TollgateScene()
{
}

Scene* TollgateScene::scene()
{
	//the scene contains one layer
	Scene *scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//create and initialize the layer
	TollgateScene *layer = TollgateScene::create();
	scene->addChild(layer);
	//Ԥ�����Դ
	SimpleAudioEngine::sharedEngine()->preloadEffect("hit2.mp3");
	//SimpleAudioEngine::sharedEngine()->preloadEffect("hit.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("dead.wav");
	return scene;
}

bool TollgateScene::init()
{
	bool isInit = false;
	do
	{
		/*��ӱ���*/
		initBG();

		Size visibleSize = Director::getInstance()->getVisibleSize();

		//�����Ʒְ�
		createScore();

		//�������������
		Point center = Point(visibleSize.width / 2, visibleSize.height / 2);
		m_tower = Tower::create();
		m_tower->bindSprite(Sprite::create("bug.png"));
		m_tower->bindEffect(Sprite::create("pow1.png"));
		m_tower->setPosition(center);
		m_tower->setScale(0.5);
		addChild(m_tower);
		m_tower->getEffect()->setVisible(false);
		//m_tower->fire();

		//�����������������
		MonsterManager *monsterMgr = MonsterManager::create();
		m_monsterManager = monsterMgr;
		addChild(monsterMgr, 1);

		//�ӵ������������ӵ�
		BulletManager *bulletMgr = BulletManager::create();
		addChild(bulletMgr, 2);

		//��������,��Ϊ�߽�
		Sprite *edge = Sprite::create();
		PhysicsBody *edgeBody = PhysicsBody::createEdgeBox(visibleSize*1.5, PHYSICSBODY_MATERIAL_DEFAULT, 3);
		edgeBody->getShape(0)->setFriction(0.0f);
		edgeBody->getShape(0)->setRestitution(1.0f);
		edgeBody->setCollisionBitmask(0x00000000);
		edgeBody->setContactTestBitmask(0x01);
		edgeBody->setEnabled(true);

		edge->setPhysicsBody(edgeBody);
		edge->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		edge->setTag(0);
		addChild(edge, 0);

		setTouchEnabled(true);

		//������ͣ��ť
		createPauseButton();

		//�������⼼�ܰ�ť
		createSkill1();
		createSkill2();
		createSkill3();

		//������������
		Skill* decelerate = Skill::create();
		m_skill03 = decelerate;
		addChild(m_skill03, 15);
		Skill* recover = Skill::create();
		m_skill02 = recover;
		addChild(m_skill02, 14);
		Skill *meteroSkill = Skill::create();
		m_skill01 = meteroSkill;
		addChild(m_skill01, 13);                //Skill������ЧͼƬ����

		//����Ѫ����
		createSlider();

		scheduleUpdate();

		isInit = true;
	} while (0);

	return isInit;
}


void TollgateScene::initBG()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite *background = Sprite::create("background2.jpg");
	m_bgSprite = background;
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);
}

Tower* TollgateScene::getTower()
{
	return m_tower;
}

void TollgateScene::onEnter()
{
	Layer::onEnter();
	EventListenerPhysicsContact *listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(TollgateScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void TollgateScene::onExit()
{
	Layer::onExit();
}


bool TollgateScene::onContactBegin(const PhysicsContact &contact)
{
	Node *contactBodyA = contact.getShapeA()->getBody()->getNode();
	Node *contactBodyB = contact.getShapeB()->getBody()->getNode();
	int tagA = contactBodyA->getTag();
	int tagB = contactBodyB->getTag();
	if (contactBodyA->getTag() != 0 && contactBodyB->getTag() != 0)
	{
		if ((tagA == 1 && tagB == 2) || (tagA == 2 && tagB == 1)) //��ײ����ֱ��ǹ��޺��ӵ�
		{
			//���������Ч
			auto explosion = CCParticleFire::create();
			explosion->setTexture(CCTextureCache::sharedTextureCache()->addImage("pow1.png"));
			explosion->setPosition(contactBodyA->getPosition());
			explosion->setAutoRemoveOnFinish(true);
			explosion->setDuration(0.1f);
			addChild(explosion);
			if (tagA == 1 && tagB == 2)
			{
				Monster *contactMonster = (Monster*)contactBodyA;
				Bullet *contactBullet = (Bullet*)contactBodyB;
				contactMonster->isHurt();
				contactBullet->hide();
				if (contactMonster->isDead())
				{
					addScore(contactMonster->getMaxHP());//�ӷ�
					showScore();
				}
			}
			else {
				Bullet *contactBullet = (Bullet*)contactBodyA;
				Monster *contactMonster = (Monster*)contactBodyB;
				contactBullet->hide();
				contactMonster->isHurt();  
				if (contactMonster->isDead())
				{
					//��ɱmonster��Ч
					//SimpleAudioEngine::sharedEngine()->playEffect("hit2.mp3");
					addScore(contactMonster->getMaxHP());//�ӷ�
					showScore();
				}
			}
		}
		//����������ײ,����Ѫ,������ʧ
		if (tagA == 1 && tagB == 3 || tagA == 3 && tagB == 1)
		{
			if (tagA == 1 && tagB == 3)
			{
				Monster *contactMonster = (Monster*)contactBodyA;
				Tower *contactTower = (Tower*)contactBodyB;
				contactMonster->getIntoTower();
				contactTower->isHurt();
			}
			else {
				Tower *contactTower = (Tower*)contactBodyA;
				Monster *contactMonster = (Monster*)contactBodyB;
				contactTower->isHurt();
				contactMonster->getIntoTower();
			}
			showHP();
			if (m_tower->getiHP() == 0)
			{
				//����bug������Ч
				SimpleAudioEngine::sharedEngine()->playEffect("shoot.mp3");
				Scene *endScene = EndScene::scene();
				EndScene::score = score;
				Director::getInstance()->replaceScene(TransitionMoveInT::create(1, endScene));
			}
		}
	}
	else {
		//�ӵ���ǽ�����
		if (tagA == 0 && tagB == 2)
		{
			Entity *bulletB = (Entity*)contactBodyB;
			bulletB->hide();
			//decreScore();      /*�ӵ���� �۷� �Ѷȱ��*/
			//showScore();
		}
		if (tagA == 2 && tagB == 0)
		{
			Entity *bulletA = (Entity*)contactBodyA;
			bulletA->hide();
			/*decreScore();
			showScore();*/
		}
	}
	return false;
}

void TollgateScene::update(float delta)
{
	if (m_skill01->isCool())
		btn1->setVisible(true);
	if (m_skill02->isCool())
		btn2->setVisible(true);
	if (m_skill03->isCool())
		btn3->setVisible(true);
}

void TollgateScene::createPauseButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Button* btn = Button::create("pause2.png");//Button::create��Ӱ�ť������ɸ�3����������Ӧ��ͬ״̬��ť��ͼƬ
	btn->setScale(0.3);
	btn->setPosition(Point(visibleSize.width * 0.9f, visibleSize.height * 0.9f));//������ͣ��ťλ��
	btn->setTitleText("Pause");//setTitleText���ð�ťͼƬ�������
	btn->setTouchEnabled(true);
	btn->addTouchEventListener(this, toucheventselector(TollgateScene::touchButtonPause)); //�����ͣ��ť������
	addChild(btn, 3);//����ť��ӽ�ȥ
	log("there is button");
}

void TollgateScene::touchButtonPause(Object* object, TouchEventType type)
{
	if (type == ui::TOUCH_EVENT_BEGAN)
	{
		Scene *pauseScene = PauseScene::scene();
		Director::sharedDirector()->pushScene(pauseScene);
	}
	if (type == ui::TOUCH_EVENT_MOVED)
	{
	}
	if (type == ui::TOUCH_EVENT_ENDED)
	{
	}
}

void TollgateScene::createSkill1()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	btn1 = Button::create("missile.png");//Button::create��Ӱ�ť
	btn1->setScale(0.2);
	btn1Shadow = Sprite::create("missile2.png");
	btn1Shadow->setScale(0.2);
	btn1->setPosition(Point(visibleSize.width * 0.65f, visibleSize.height * 0.15f));//���ð�ťλ��
	btn1Shadow->setPosition(Point(visibleSize.width * 0.65f, visibleSize.height * 0.15f));
	btn1->setTitleText("Deadly Missle");//setTitleText���ð�ťͼƬ�������
	btn1->setTitleFontSize(60);
	btn1->setTouchEnabled(true);
	btn1->addTouchEventListener(this, toucheventselector(TollgateScene::touchSkill1));//��Ӱ�ť������
	addChild(btn1, 5);//����ť��ӽ�ȥ
	addChild(btn1Shadow, 4);
}

void TollgateScene::createSkill2()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	btn2 = Button::create("recover1.png");//Button::create��Ӱ�ť������ɸ�3����������Ӧ��ͬ״̬��ť��ͼƬ
	btn2->setScale(0.14);
	btn2Shadow = Sprite::create("recover2.png");
	btn2Shadow->setScale(0.14);
	btn2->setPosition(Point(visibleSize.width * 0.7f, visibleSize.height * 0.15f));//���ð�ťλ��
	btn2Shadow->setPosition(Point(visibleSize.width * 0.7f, visibleSize.height * 0.15f));
	btn2->setTitleText("God's Bless");//setTitleText���ð�ťͼƬ�������
	btn2->setTitleFontSize(100);
	btn2->setTouchEnabled(true);
	btn2->addTouchEventListener(this, toucheventselector(TollgateScene::touchSkill2));//��Ӱ�ť������
	addChild(btn2, 7);//����ť��ӽ�ȥ
	addChild(btn2Shadow, 6);
}

void TollgateScene::createSkill3()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	btn3 = Button::create("time.png");//Button::create��Ӱ�ť������ɸ�3����������Ӧ��ͬ״̬��ť��ͼƬ
	btn3->setScale(0.14);
	btn3Shadow = Sprite::create("time2.png");
	btn3Shadow->setScale(0.14);
	btn3->setPosition(Point(visibleSize.width * 0.75f, visibleSize.height * 0.15f));//���ð�ťλ��
	btn3Shadow->setPosition(Point(visibleSize.width * 0.75f, visibleSize.height * 0.15f));
	btn3->setTitleText("Freeze");//setTitleText���ð�ťͼƬ�������
	btn3->setTitleFontSize(120);
	btn3->setTouchEnabled(true);
	btn3->addTouchEventListener(this, toucheventselector(TollgateScene::touchSkill3));//��Ӱ�ť������
	addChild(btn3, 9);//����ť��ӽ�ȥ
	addChild(btn3Shadow, 8);
}

void TollgateScene::touchSkill1(Object* object, TouchEventType type)
{
	if (type == ui::TOUCH_EVENT_BEGAN)
	{
	}	
	if (type == ui::TOUCH_EVENT_MOVED)
	{
	}
	if (type == ui::TOUCH_EVENT_ENDED)
	{
		m_skill01->SkillTo(m_monsterManager);//��Ҫ���õĶ���ɱ�����й��
		Sequence* killAllMonster = m_skill01->skill01(Point(-200 - CCRANDOM_0_1() * 300, 1000 + CCRANDOM_0_1() * 300));//������Ч
		auto changeScore = CCCallFunc::create([this] {
			addScore(m_monsterManager->getDeadNum());
			showScore();
			btn1->setVisible(false);
		});
		runAction(Sequence::create(killAllMonster, changeScore, NULL));
	}
}

void TollgateScene::touchSkill2(Object* object, TouchEventType type)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("touch skill2");
	if (type == ui::TOUCH_EVENT_BEGAN)
	{
	}
	if (type == ui::TOUCH_EVENT_MOVED)
	{
	}
	if (type == ui::TOUCH_EVENT_ENDED)
	{
		m_skill02->skill02(Point(visibleSize.width / 2, visibleSize.height / 2));
		btn2->setVisible(false);
		//����Ч��,������Ѫ
		m_tower->isHealed();
		showHP();
	}
}

void TollgateScene::touchSkill3(Object* object, TouchEventType type)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("touch skill3");
	if (type == ui::TOUCH_EVENT_BEGAN)
	{
	}
	if (type == ui::TOUCH_EVENT_MOVED)
	{
	}
	if (type == ui::TOUCH_EVENT_ENDED)
	{
		m_skill03->skill03(Point(visibleSize.width / 2, visibleSize.height / 2));
		btn3->setVisible(false);
	}
}

void TollgateScene::createScore()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	scoreLabel = Label::create();//��ʼ���Ʒְ�
	scoreLabel->setPosition(visibleSize.width*0.5f, visibleSize.height*0.9f);//��ʼλ��
	scoreLabel->setString("ZERO");//��ʼ����
	scoreLabel->setSystemFontSize(50);
	scoreLabel->setColor(Color3B::BLACK);
	addChild(scoreLabel, 10);//���Ʒְ���볡��
}

void TollgateScene::showScore()
{
	std::string str;//ת�����ַ���
	std::stringstream ss;
	ss << score;
	ss >> str;//����ת�ַ���
	scoreLabel->setString(str);//�������ַ�������label
}

void TollgateScene::createSlider()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	HPslider = Slider::create();
	HPslider->setTouchEnabled(false);
	HPslider->setMaxPercent(100);
	HPslider->setPercent(100);
	HPslider->loadBarTexture("Bar4.png");//Ѫ�����ײ�
	HPslider->loadSlidBallTexturePressed("button.png");//Ѫ������ť
	HPslider->loadProgressBarTexture("ProgressBar4.png");//Ѫ��������(�ڲ�)
	HPslider->setPosition(Point(visibleSize.width * 0.2f, visibleSize.height * 0.9f));
	HPslider->setScale(0.05);
	addChild(HPslider, 11);
	Sprite *Bar = Sprite::create("Bar.png");
	Bar->setScale(0.05);
	Bar->setPosition(Point(visibleSize.width * 0.215f, visibleSize.height * 0.9f));
	addChild(Bar, 10);

	HPlabel = Label::create();//��ʼ���Ʒְ�
	HPlabel->setPosition(visibleSize.width*0.2f, visibleSize.height*0.9f);//��ʼλ��
	HPlabel->setString("100");//��ʼ����
	HPlabel->setSystemFontSize(20);
	HPlabel->setColor(Color3B::WHITE);
	addChild(HPlabel, 12);//���Ʒְ���볡��
}

void TollgateScene::showHP()
{
	HPpercent = m_tower->getiHP() * 100 / m_tower->getMaxHP();
	//�ı�Ѫ����
	HPslider->setPercent(HPpercent);

	std::string str;//ת�����ַ���
	std::stringstream ss;
	ss << HPpercent;
	ss >> str;//����ת�ַ���
	HPlabel->setString(str);//�������ַ�������label
}