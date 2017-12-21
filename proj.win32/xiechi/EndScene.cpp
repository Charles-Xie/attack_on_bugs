#include "EndScene.h"

int EndScene::score = 0;

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}

Scene* EndScene::scene()
{
	Scene *scene = Scene::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto layer = EndScene::create();
	scene->addChild(layer);
	return scene;
}

bool EndScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	score = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Label *gameName = Label::create("Attack on Bugs", "Times New Roman", 36);
	gameName->setPosition(Point(visibleSize.width / 2, visibleSize.height * 0.85f));
	addChild(gameName);

	Label *gameOver = Label::create("Game Over", "Arial", 54);
	gameOver->setPosition(Point(visibleSize.width / 2, visibleSize.height * 0.7f));
	addChild(gameOver, 1);

	setTouchEnabled(true);
	createStartButton();
	return true;
}

void EndScene::createStartButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	startButton = Button::create("restart.png");//Button::create添加按钮，后面可跟3个参数，对应不同状态按钮的图片
	startButton->setScale(0.3);
	startButton->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.1f));//设置按钮位置
	startButton->setTitleText("Play again");
	startButton->setTouchEnabled(true);
	startButton->addTouchEventListener(this, toucheventselector(StartScene::newStartEasy)); //添加监听器
	addChild(startButton, 1);//将按钮添加进去
}

void EndScene::onEnter()
{
	Layer::onEnter();
	showScore();
}

void EndScene::showScore()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (score <= 50)
	{
		Sprite *bugDead = Sprite::create("dead1.png");
		bugDead->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		addChild(bugDead, 0);
	}
	else {
		Sprite *bugDead = Sprite::create("dead2.png");
		bugDead->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		addChild(bugDead, 0);
	}
	if (score != 0)
	{
		Label *label = Label::create("YOUR SCORE", "Courier", 30);
		label->setPosition(visibleSize.width / 2, visibleSize.height * 0.38);
		addChild(label, 1);

		Label *scoreLabel = Label::create();
		std::string str;
		std::stringstream ss;
		ss << score;
		ss >> str;
		scoreLabel->setString(str);
		scoreLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.28);
		scoreLabel->setSystemFontSize(60);
		scoreLabel->setColor(Color3B::YELLOW);
		addChild(scoreLabel, 1);

		Label *talk1 = Label::create("Hehe......", "Courier", 25);
		talk1->setPosition(visibleSize.width / 2, visibleSize.height * 0.2);
		Label *talk2 = Label::create("You can't be serious.", "Courier", 25);
		talk2->setPosition(visibleSize.width / 2, visibleSize.height * 0.2);
		Label *talk3 = Label::create("Well done!", "Courier", 25);
		talk3->setPosition(visibleSize.width / 2, visibleSize.height * 0.2);
		Label *talk4 = Label::create("You are my hero!", "Courier", 25);
		talk4->setPosition(visibleSize.width / 2, visibleSize.height * 0.2);
		if (score <= 10)
		addChild(talk1, 1);
		else if (score <= 50)
			addChild(talk2, 3);
		else if (score <= 120)
			addChild(talk3, 3);
		else addChild(talk4, 3);
	}
}