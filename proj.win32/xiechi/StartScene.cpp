#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

Scene* StartScene::scene()
{
	Scene *scene = Scene::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto layer = StartScene::create();
	scene->addChild(layer);

	return scene;
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*Better replaced by menu*/
	Label *gameName = Label::create("Attack on Bugs", "Times New Roman", 90);
	gameName->setPosition(Point(visibleSize.width / 2, visibleSize.height * 0.65));
	addChild(gameName,1);

	bgSprite = Sprite::create("startbg1.png");
	bgSprite->setScale(1.5);
	bgSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(bgSprite, 0);

	setTouchEnabled(true);
	createStartButton();
	return true;
}

void StartScene::createStartButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	startButtonEasy = Button::create("easy.png");//Button::create��Ӱ�ť
	startButtonEasy->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));//���ð�ťλ��
	startButtonEasy->setScale(0.2);
	startButtonEasy->setTouchEnabled(true);
	startButtonEasy->addTouchEventListener(this, toucheventselector(StartScene::newStartEasy)); //��Ӽ�����
	addChild(startButtonEasy, 1);//����ť��ӽ�ȥ

	startButtonHard = Button::create("hard.png");//Button::create��Ӱ�ť
	startButtonHard->setScale(0.2);
	startButtonHard->setPosition(Point(visibleSize.width / 2, visibleSize.height * 0.4));//���ð�ťλ��
																					   
	startButtonHard->setTouchEnabled(true);
	startButtonHard->addTouchEventListener(this, toucheventselector(StartScene::newStartHard)); //��Ӽ�����
	addChild(startButtonHard, 1);//����ť��ӽ�ȥ
}

void StartScene::newStartEasy(Object* object, TouchEventType type)
{
	//�����ť��ص���Ϸ����(���¿�ʼ)
	if (type == ui::TOUCH_EVENT_BEGAN)
	{
		TollgateScene::rank = 1;
		auto nextScene = TollgateScene::scene();
		Director::sharedDirector()->replaceScene(TransitionFade::create(2, nextScene));
	}
	if (type == ui::TOUCH_EVENT_MOVED)
	{
	}
	if (type == ui::TOUCH_EVENT_ENDED)
	{
	}
}

void StartScene::newStartHard(Object* object, TouchEventType type)
{
	//�����ť��ص���Ϸ����(���¿�ʼ)
	if (type == ui::TOUCH_EVENT_BEGAN)
	{
		TollgateScene::rank = 2;
		auto nextScene = TollgateScene::scene();
		Director::sharedDirector()->replaceScene(TransitionFade::create(2, nextScene));
	}
	if (type == ui::TOUCH_EVENT_MOVED)
	{
	}
	if (type == ui::TOUCH_EVENT_ENDED)
	{
	}
}

