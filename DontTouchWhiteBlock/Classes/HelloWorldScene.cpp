#include "HelloWorldScene.h"


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    srand(time(NULL));

    visiableSize = Director::getInstance()->getVisibleSize();
    
    timeLayer = Label::create();
    gameLayer = Node::create();
    addChild(gameLayer);

    timeLayer->setTextColor(Color4B::BLUE);
    
    timeLayer->setSystemFontSize(48);
    
    timeLayer->setPosition(visiableSize.width/2,visiableSize.height-100);
    timeLayer->setString("time");
    addChild(timeLayer);
    
    
    
    
    
    startGame();
    
    
    auto lisener = EventListenerTouchOneByOne::create();
    lisener->onTouchBegan = [this](Touch * t, Event * e){
        auto bs = Block::getBlocks();
        Block * b;
        for (auto it = bs->begin(); it!= bs->end(); it++) {
            b = *it;
            
            if(b->getLineIndex()==1&&b->getBoundingBox().containsPoint(t->getLocation())){
                if(b->getColor()==Color3B::BLACK)
                {
                    if(!timerRuning)
                    {
                        this->startTimer();
                    }
                    b->setColor(Color3B::GRAY);
                    this->moveDown();
                }
                else if(b->getColor()==Color3B::GREEN)
                {
                    this->moveDown();
                    this->stopTimer();
                }
                else
                {
                   // showEnd = true;
                    MessageBox("www", "game Over");
                }
                break;
            
            }
            
        }
        log("on touch");
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lisener, this);
 //   addStartLine();
  //  addEndLine();
   // addNormalLine(2);
    return true;
}

void HelloWorld::moveDown()
{
    
    if(lineCount<10)
    {
        addNormalLine(4);
    }
    else if(!showEnd){
        addEndLine();
        showEnd = true;
    }
    auto bs = Block::getBlocks();
    
    
    
    for (auto it = bs->begin(); it!=bs->end(); it++) {
        (*it)->moveDown();
    }
}

void HelloWorld::startGame()
{
    timerRuning = false;
    lineCount = 0;
    addStartLine();
    addNormalLine(1);
    addNormalLine(2);
    addNormalLine(3);
   // addEndLine();
}

void HelloWorld::addNormalLine(int index){

    Block * b;
    lineCount++;
    
    int blackIndex = rand()%4;
    
    for (int i = 0 ; i<4; i++) {
        b =   Block::createWithArgs(( blackIndex == i )?Color3B::BLACK:Color3B::WHITE, Size(visiableSize.width/4-1,visiableSize.height/4-1), "", 20, Color4B::BLACK);
        gameLayer -> addChild(b);
        //
       // b->setPosition(const cocos2d::Vec2 &pos)
        b->setPosition(Vec2(i*visiableSize.width/4,index*visiableSize.height/4));
        b->setLineIndex(index);
    }
}



void HelloWorld::update(float dt)
{
    long offset = clock() - startTime;
    
    timeLayer->setString( StringUtils::format("%g",(double)offset/1000000));
    
    
}
void HelloWorld::startTimer()
{
    if(!timerRuning)
    {
        startTime = clock();
        scheduleUpdate();
        timerRuning = true;
    }
}
void HelloWorld::stopTimer()
{
    if(timerRuning)
    {
        unscheduleUpdate();
        timerRuning = false;
    }
}

void HelloWorld::addStartLine(){
    auto b = Block::createWithArgs(Color3B::YELLOW, Size(visiableSize.width,visiableSize.height/4), "", 20, Color4B::BLACK);
    gameLayer -> addChild(b);
    b->setLineIndex(0);
}

void HelloWorld::addEndLine()
{
    auto b = Block::createWithArgs(Color3B::GREEN, visiableSize, "Game Over", 32, Color4B::BLACK);
    gameLayer -> addChild(b);
    b->setLineIndex(4);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

