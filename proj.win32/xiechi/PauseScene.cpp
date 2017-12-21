#include "PauseScene.h"

using namespace ui;

PauseScene::PauseScene()
{
}

PauseScene::~PauseScene()
{
}

Scene* PauseScene::scene()
{
	auto scene = Scene::createWithPhysics();
	Vect gravity(0, -10.0f);
	scene->getPhysicsWorld()->setGravity(gravity);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto edgeBody = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->getShape(0)->setRestitution(1.0f);
	auto node = Node::create();
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(edgeBody);
	scene->addChild(node);

	auto layer = PauseScene::create();
	scene->addChild(layer);

	return scene;
}

bool PauseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Label *mainTitle = Label::create("pause", "Arial", 50);
	mainTitle->setPosition(Point(visibleSize.width / 2, visibleSize.height * 0.9f));
	//���"��ͣ"����
	addChild(mainTitle);
	
	Sprite *bg = Sprite::create("pausebg.jpg");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(bg, 0);

	littleDevil = Sprite::create("littleDevil.png");

	PhysicsBody *littleDevilBody = PhysicsBody::createCircle(littleDevil->getContentSize().width * 0.4f);
	littleDevilBody->setGravityEnable(true);
	littleDevilBody->getShape(0)->setFriction(0);
	littleDevilBody->getShape(0)->setRestitution(1.0f);

	littleDevil->setPhysicsBody(littleDevilBody);
	littleDevil->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.85f));
	
	addChild(littleDevil, 2);
	setTouchEnabled(true);
	createOprUi();
	return true;
}

void PauseScene::onEnter()
{
	Layer::onEnter();
	log("pause onenter");
}

void PauseScene::onExit()
{
	Layer::onExit();
	log("pause onexit");
}

void PauseScene::createOprUi()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	restartButton = Button::create("restart.png");//Button::create��Ӱ�ť������ɸ�3����������Ӧ��ͬ״̬��ť��ͼƬ
	restartButton->setScale(0.3);
	restartButton->setPosition(Point(visibleSize.width * 0.4f, visibleSize.height * 0.75f));//���ð�ťλ��
	restartButton->setTitleText("Retry");//setTitleText���ð�ťͼƬ�������
	restartButton->setTouchEnabled(true);
	restartButton->addTouchEventListener(this, toucheventselector(StartScene::newStartEasy)); //��Ӽ�����
	addChild(restartButton, 1);//����ť��ӽ�ȥ

	resumeButton = Button::create("start.png");
	resumeButton->setScale(0.3);
	resumeButton->setPosition(Point(visibleSize.width * 0.6f, visibleSize.height * 0.75f));
	resumeButton->setTitleText("Resume");
	resumeButton->setTouchEnabled(true);
	resumeButton->addTouchEventListener(this, toucheventselector(PauseScene::touchButtonResume));
	addChild(resumeButton, 2);
}

void PauseScene::touchButtonResume(Object* object, TouchEventType type)
{
	//�����ť��ص���Ϸ����(������Ϸ)
	if (type == ui::TOUCH_EVENT_BEGAN)
	{
		Director::sharedDirector()->popScene();
	}
	if (type == ui::TOUCH_EVENT_MOVED)
	{
	}
	if (type == ui::TOUCH_EVENT_ENDED)
	{
	}
}