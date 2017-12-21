#include "TollgateScene2.h"
#include "Player2.h"
#include "PauseScene2.h"
#include "Background2.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace ui;

TollgateScene :: ~TollgateScene()
{
}

Scene* TollgateScene::scene()
{
	auto scene = Scene::createWithPhysics();
	Vect gravity(0, -0.5f);
	scene->getPhysicsWorld()->setGravity(gravity);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto node = Node::create();
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	scene->addChild(node);
	auto layer = TollgateScene::create();
	scene->addChild(layer, 10);
	
	return scene;
}

bool TollgateScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	m_player->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.85f));
	this->addChild(m_player, 5);
	setTouchEnabled(true);
	createOprUi();
	//�����Ʒְ����ú���Label::create();
	//str = itoa(����, str, 10);
	//label->setString(str);
	//label->setVisible(true);
	//�û�ȡʱ�亯�����ƵĿ�����ʾʱ��
	return true;
}

void TollgateScene::onExit()
{
	Layer::onExit();
}

void TollgateScene::createOprUi()
{
	Size visibleSizeOpr = Director::getInstance()->getVisibleSize();
	Button* btn = Button::create("res/button.png");//Button::create��Ӱ�ť������ɸ�3����������Ӧ��ͬ״̬��ť��ͼƬ
	btn->setPosition(Point(visibleSizeOpr.width * 0.5f, visibleSizeOpr.height * 0.85f));//���ð�ťλ�ã���ֹ�Ҳ�������������
	btn->setTitleText("this is a button");//setTitleText���ð�ťͼƬ�������
	btn->setTouchEnabled(true);
	btn->addTouchEventListener(this, toucheventselector(TollgateScene::touchButton)); //��Ӽ�����
	this->addChild(btn);//����ť��ӽ�ȥ
}

void TollgateScene::touchButton(Object* object, TouchEventType type)
{
	
	log("112");
	if (type == ui::TOUCH_EVENT_BEGAN)
	{
		auto scenePause = PauseScene::scene();
		Director::sharedDirector()->replaceScene(scenePause);
		//do something;
	}
	if (type == ui::TOUCH_EVENT_MOVED)
	{
	
					 //do something;
	}
	if (type == ui::TOUCH_EVENT_ENDED)
	{
	
					 //do something;
	}

};

