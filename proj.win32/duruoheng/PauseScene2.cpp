#include "PauseScene2.h"
#include "Background2.h"
#include "TollgateScene2.h"
#include "Player2.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace ui;

PauseScene :: ~PauseScene()
{
}

Scene* PauseScene::scene()
{
	auto scenePause = Scene::createWithPhysics();
	Vect gravity(0, -0.5f);
	scenePause->getPhysicsWorld()->setGravity(gravity);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto node = Node::create();
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	scenePause->addChild(node);
	auto layer = PauseScene::create();
	scenePause->addChild(layer, 10);

	return scenePause;
}

bool PauseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	background->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.85f));
	this->addChild(background, 5);
	setTouchEnabled(true);
	createOprUi();

	return true;
}

void PauseScene::onExit()
{
	Layer::onExit();
}

void PauseScene::createOprUi()
{
	Size visibleSizeOpr = Director::getInstance()->getVisibleSize();
	Button* startbtn = Button::create("res/button.png");//Button::create添加按钮，后面可跟3个参数，对应不同状态按钮的图片
	startbtn->setPosition(Point(visibleSizeOpr.width * 0.5f, visibleSizeOpr.height * 0.85f));//设置按钮位置，防止找不到。。。。。
	startbtn->setTitleText("Ah,  you are back!");//setTitleText设置按钮图片上面的字
	startbtn->setTouchEnabled(true);//好像不加也没事？
	startbtn->addTouchEventListener(this, toucheventselector(PauseScene::touchButtonStart)); //添加监听器
	this->addChild(startbtn, 5);//将按钮添加进去
}

void PauseScene::touchButtonStart(Object* object, TouchEventType type)
{

	if (type == ui::TOUCH_EVENT_BEGAN)
	{
		auto scene = TollgateScene::scene();
		Director::sharedDirector()->replaceScene(scene);
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

