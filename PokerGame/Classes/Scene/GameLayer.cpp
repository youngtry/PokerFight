//
//  GameLayer.cpp
//  FightWithCard
//
//  Created by tianrunyan on 16/3/16.
//
//

#include "GameLayer.h"
#include "../Data/MakeCard.h"
#include "../Tools/tools.h"
#include "../Data/GameData.h"

GameLayer::GameLayer()
:m_BackgroundLayer(NULL)
,m_Background(NULL)
,m_BackgroundName("")
,m_MenuLayer(NULL)
,m_CallScoreMenu(NULL)
,m_DoubleMenu(NULL)
,m_PlayMenu(NULL)
,m_AutoPlayMenu(NULL)
,m_HandCardLayer(NULL)
,m_OutCardLayer(NULL)
,m_AnimLayer(NULL)
,m_InfoLayer(NULL)
,m_PlayerLayer(NULL)
,m_Time(NULL)
,m_MyPlayer(NULL)
,m_RightPlayer(NULL)
,m_LeftPlayer(NULL)
,m_Story(NULL)
,m_StoryLayer(NULL)
,m_RoundIndex(0)
,m_TopInfoPanel(NULL)
,m_LordIndex(-1)
,m_DealIndex(0)
,m_Nickname(NULL)
,m_Gold(NULL)
,m_Beishu(NULL)
,m_DiFen(NULL)
,m_TableLayer(NULL)
,m_Clock(NULL)
,m_ClockNum(NULL)
,m_GameState(GameNull)
,m_CurrPlayer(-1)
{
    m_LeftCard.clear();
    m_MyCard.clear();
    m_RightCard.clear();
    m_LordCard.clear();
    m_StoryInfo.clear();
    m_TopLordCard.clear();
    for(int i=0;i<3;i++){
        m_LeftCardNumber[i] = 0;
        m_LeftCardNumberLabel[i] = NULL;
        m_PlayerSpeak[i] = NULL;
    }
}

GameLayer::~GameLayer(){
    
}

void GameLayer::onEnter(){
    Layer::onEnter();
}

void GameLayer::onExit(){
    Layer::onExit();
}

Scene* GameLayer::createGameScene(){
    GameLayer* layer = GameLayer::create();
    Scene* scene = Scene::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init(){
    if(!Layer::init()){
        return false;
    }
    m_RoundIndex = UserDefault::getInstance()->getIntegerForKey("RoundIndex", 1);
    
    MakeCard::getInstance()->initData(__String::createWithFormat("LevelInfo/level%03d.xml",m_RoundIndex)->getCString());
    
    //初始化数据
    m_winSize = Director::getInstance()->getWinSize();
    
    m_LordIndex = MakeCard::getInstance()->m_LordIndex;
    m_LeftCard = MakeCard::getInstance()->m_LeftCard;
    m_MyCard = MakeCard::getInstance()->m_MyCard;
    m_RightCard = MakeCard::getInstance()->m_RightCard;
    m_LordCard = MakeCard::getInstance()->m_LordCard;
    
    string a = getString("ShowText");
    log("showText = %s",a.c_str());
    
    
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    changeToGameState(GameReady);
    return true;
}
#pragma mark ***********流程控制***********
void GameLayer::changeToGameState(GameState state){
    m_GameState = state;
    if(state == GameReady){
        //准备状态，铺设基本UI
        createBackground();
        createPlayersLayer();
        createStoryLayer();
        showStory();
        return;
    }
    
    if(state == GameDealCard){
        createHanderLayer();
        createInfoLayer();
        createTableLayer();
        DealCards();
        createMenuLayer();
        hideMenuLayer();
        return;
    }
    if(state == GameCallScore){
        CallScore(0);
        return;
    }
 
    if(state == GameGetLord){
        GetLord();
        return;
    }
    
    if(state == GameDouble){
        for(int i=0;i<3;i++){
            if(m_PlayerSpeak[i])
                m_PlayerSpeak[i]->setVisible(false);
        }
        CallDouble();
        return;
    }
    
    if(state == GamePlay){
        for(int i=0;i<3;i++){
            if(m_PlayerSpeak[i])
                m_PlayerSpeak[i]->setVisible(false);
        }
        return;
    }
}

void GameLayer::DealCards(){
    
    schedule([=](float df){
        GameLayer::adjustCards();
        for(int i=0;i<3;i++){
            m_LeftCardNumber[i] = m_DealIndex;
            m_LeftCardNumberLabel[i]->setString(__String::createWithFormat("%d",m_LeftCardNumber[i])->getCString());
        }
        m_DealIndex++;
        log("m_DealIndex = %d",m_DealIndex);
        if(m_DealIndex == 17){
            GameLayer::showBaseInfo();
        }
    },0.1f, CC_REPEAT_FOREVER, 0.0f, "DealCard");
    
    
}

void GameLayer::CallScore(int score){
    if(m_CurrPlayer == -1){
        m_CurrPlayer = 0;
        showClock(CloclkTime, 0);
    }else if(m_CurrPlayer == 0){
        m_CurrPlayer = 1;
        showClock(CloclkTime, 1);
        showCallScoreMenu(true);
    }
}

void GameLayer::GetLord(){
    Sprite* spr1 = (Sprite*)m_InfoLayer->getChildByName("Lord1");
    Sprite* spr2 = (Sprite*)m_InfoLayer->getChildByName("Lord2");
    Sprite* spr3 = (Sprite*)m_InfoLayer->getChildByName("Lord3");
    
    __String* str1;
    Animation* animation1 = Animation::create();
    for(int i=1;i<7;i++){
        str1 = __String::createWithFormat("Card/lordcard/lordlz_lzbottom_frame_%d.png",i);
        animation1->addSpriteFrameWithFile(str1->getCString());
    }
    
    animation1->setDelayPerUnit(0.1f);
    Animate* animate1 = Animate::create(animation1);
    CallFunc* func1 = CallFunc::create([=]{
        spr1->setVisible(false);
        if(m_LordCard[0]){
            m_LordCard[0]->setPosition(Vec2(m_winSize.width/2-m_LordCard[0]->getCardSize().width*1.5-5, m_winSize.height*0.6));
            MoveTo* move1 = MoveTo::create(0.5, Vec2(m_winSize.width/2, m_winSize.height*0.9));
            ScaleTo* scale1 = ScaleTo::create(0.5, 0.3);
            
            CallFunc* func = CallFunc::create([=]{
                m_LordCard[0]->setVisible(false);
                if(m_TopLordCard[0])
                {
                    m_TopLordCard[0]->setVisible(true);
                }
            });
            
            m_LordCard[0]->runAction(Sequence::create(Spawn::create(move1,scale1, NULL),func, NULL));
        }
    });
    spr1->runAction(Sequence::create(animate1,func1, NULL));
    
    __String* str2;
    Animation* animation2 = Animation::create();
    for(int i=1;i<7;i++){
        str2 = __String::createWithFormat("Card/lordcard/lordlz_lzbottom_frame_%d.png",i);
        animation2->addSpriteFrameWithFile(str2->getCString());
    }
    
    animation2->setDelayPerUnit(0.1f);
    Animate* animate2 = Animate::create(animation2);
    CallFunc* func2 = CallFunc::create([=]{
        spr2->setVisible(false);
        if(m_LordCard[1]){
            m_LordCard[1]->setPosition(Vec2(m_winSize.width/2-m_LordCard[1]->getCardSize().width/2, m_winSize.height*0.6));
            MoveTo* move1 = MoveTo::create(0.5, Vec2(m_winSize.width/2, m_winSize.height*0.9));
            ScaleTo* scale1 = ScaleTo::create(0.5, 0.3);
            
            CallFunc* func = CallFunc::create([=]{
                m_LordCard[1]->setVisible(false);
                if(m_TopLordCard[1])
                {
                    m_TopLordCard[1]->setVisible(true);
                }
            });
            
            m_LordCard[1]->runAction(Sequence::create(Spawn::create(move1,scale1, NULL),func, NULL));
            
        }
    });
    spr2->runAction(Sequence::create(animate2,func2, NULL));
    
    __String* str3;
    Animation* animation3 = Animation::create();
    for(int i=1;i<7;i++){
        str3 = __String::createWithFormat("Card/lordcard/lordlz_lzbottom_frame_%d.png",i);
        animation3->addSpriteFrameWithFile(str3->getCString());
    }
    
    animation3->setDelayPerUnit(0.1f);
    Animate* animate3 = Animate::create(animation3);
    CallFunc* func3 = CallFunc::create([=]{
        spr3->setVisible(false);
        if(m_LordCard[2]){
            m_LordCard[2]->setPosition(Vec2(m_winSize.width/2+m_LordCard[2]->getCardSize().width/2+5, m_winSize.height*0.6));
            MoveTo* move1 = MoveTo::create(0.5, Vec2(m_winSize.width/2, m_winSize.height*0.9));
            ScaleTo* scale1 = ScaleTo::create(0.5, 0.3);
            
            CallFunc* func = CallFunc::create([=]{
                m_LordCard[2]->setVisible(false);
                if(m_TopLordCard[2])
                {
                    m_TopLordCard[2]->setVisible(true);
                }
            });
            
            m_LordCard[2]->runAction(Sequence::create(Spawn::create(move1,scale1, NULL),func, NULL));
        }
    });
    spr3->runAction(Sequence::create(animate3,func3, NULL));
    
    switch (m_LordIndex) {
        case 0:
        {
            for(int i=0;i<m_LordCard.size();i++){
                PokerCard* card = PokerCard::createPokerCard(m_LordCard[i]->getNumber(), m_LordCard[i]->getColor());
                card->setPosition(Vec2(-10000, -10000));
                m_HandCardLayer->addChild(card);
                m_LeftCard.push_back(card);
                
            }
            MakeCard::getInstance()->sequenceCards(m_LeftCard);
        }
            break;
        case 1:
        {
            for(int i=0;i<m_LordCard.size();i++){
                PokerCard* card = PokerCard::createPokerCard(m_LordCard[i]->getNumber(), m_LordCard[i]->getColor());
                card->setPosition(Vec2(-10000, -10000));
                m_HandCardLayer->addChild(card);
                m_MyCard.push_back(card);
            }
            MakeCard::getInstance()->sequenceCards(m_MyCard);
            GameLayer::setOrder(m_MyCard);
        }
            break;
        case 2:
        {
            for(int i=0;i<m_LordCard.size();i++){
                PokerCard* card = PokerCard::createPokerCard(m_LordCard[i]->getNumber(), m_LordCard[i]->getColor());
                card->setPosition(Vec2(-10000, -10000));
                m_HandCardLayer->addChild(card);
                m_RightCard.push_back(card);
            }
            MakeCard::getInstance()->sequenceCards(m_RightCard);
        }
            break;
        default:
            break;
    }
    
    CallFunc* act1 = CallFunc::create([=]{
        m_DealIndex = (int)m_MyCard.size()-1;
        GameLayer::adjustCards();
        GameLayer::showLeftCardNumber();
        if(m_LeftCardNumberLabel[m_LordIndex]){
            ScaleTo* scale1 = ScaleTo::create(0.5, 2);
            ScaleTo* scale2 = ScaleTo::create(0.5, 1);
            m_LeftCardNumberLabel[m_LordIndex]->runAction(Sequence::create(scale1,scale2, NULL));
        }
        
        changeToGameState(GameDouble);
    });
    
    this->runAction(Sequence::create(DelayTime::create(0.7),act1, NULL));
    
}

void GameLayer::CallDouble(){
    if(m_LordIndex == 0 ){
        if(m_CurrPlayer == -1){
            //I first
            m_CurrPlayer = 1;
            showClock(CloclkTime, 1);
            showDoubleMenu(true);
        }else if(m_CurrPlayer == 1){
            m_CurrPlayer = 2;
            showClock(CloclkTime, 2);
        }else{
            m_CurrPlayer = -1;
            CallFunc* func = CallFunc::create([=]{
                GameLayer::changeToGameState(GamePlay);
                changeToGameState(GamePlay);
                CCLOG("changeToGameState(GamePlay)");
            });
            
            this->runAction(Sequence::create(DelayTime::create(1),func, NULL));
            
        }
    }else if (m_LordIndex == 1){
        if(m_CurrPlayer == -1){
            m_CurrPlayer = 2;
            showClock(CloclkTime, 2);
        }else if (m_CurrPlayer ==2){
            m_CurrPlayer = 0;
            showClock(CloclkTime, 0);
        }else{
            m_CurrPlayer = -1;
            CallFunc* func = CallFunc::create([=]{
                GameLayer::changeToGameState(GamePlay);
                changeToGameState(GamePlay);
                CCLOG("changeToGameState(GamePlay)");
            });
            
            this->runAction(Sequence::create(DelayTime::create(1),func, NULL));
        }
    }else if (m_LordIndex == 2){
        if(m_CurrPlayer == -1){
            m_CurrPlayer = 0;
            showClock(CloclkTime, 0);
        }else if (m_CurrPlayer ==0){
            m_CurrPlayer = 1;
            showClock(CloclkTime, 1);
            showDoubleMenu(true);
        }else{
            m_CurrPlayer = -1;
            CallFunc* func = CallFunc::create([=]{
                GameLayer::changeToGameState(GamePlay);
                changeToGameState(GamePlay);
                CCLOG("changeToGameState(GamePlay)");
            });
            
            this->runAction(Sequence::create(DelayTime::create(1),func, NULL));
        }
    }
}

void GameLayer::OutTimehandle()
{
    if(m_GameState == GameCallScore){
        ScroeCallBack(0);
    }else if (m_GameState == GameDouble){
        DoubleCallBack(0);
        CallDouble();
    }else if (m_GameState == GamePlay){
        //自动出牌
    }
}

void GameLayer::ComputerOperation(){

    if(m_GameState == GameCallScore){
        if(m_CurrPlayer == 0){
            int score = AutoCallScore();
            m_PlayerSpeak[0]->setTexture(__String::createWithFormat("speak/lord_speak_%d_call_left.png",score)->getCString());
            m_PlayerSpeak[0]->setVisible(true);
            CallScore(score);
        }else if (m_CurrPlayer == 2){
            
        }
    }else if (m_GameState == GameDouble){
        bool isdouble = isDouble();
        if(m_CurrPlayer == 0){
            if(isdouble){
                Sprite* doubleicon = Sprite::create("speak/jiabei.png");
                doubleicon->setPosition(Vec2(m_winSize.width*0.02, m_winSize.height*0.7));
                m_PlayerLayer->addChild(doubleicon);
                m_PlayerSpeak[0]->setVisible(true);
                m_PlayerSpeak[0]->setTexture("speak/lordhl_play_speak_double_left.png");
            }else{
                m_PlayerSpeak[0]->setVisible(true);
                m_PlayerSpeak[0]->setTexture("speak/lordhl_play_speak_no_double_left.png");
            }
        }else if (m_CurrPlayer == 2){
            if(isdouble){
                Sprite* doubleicon = Sprite::create("speak/jiabei.png");
                doubleicon->setPosition(Vec2(m_winSize.width*0.96, m_winSize.height*0.7));
                m_PlayerLayer->addChild(doubleicon);
                m_PlayerSpeak[2]->setVisible(true);
                m_PlayerSpeak[2]->setTexture("speak/lordhl_play_speak_double_right.png");
            }else{
                m_PlayerSpeak[2]->setVisible(true);
                m_PlayerSpeak[2]->setTexture("speak/lordhl_play_speak_no_double_right.png");
            }
            
        }
        
        CallDouble();
    }else if (m_GameState == GamePlay){
        //自动出牌
        if(m_CurrPlayer == 0){
            
        }else if (m_CurrPlayer == 2){
            
        }
    }
}
#pragma mark ***********AI相关***********
bool GameLayer::isDouble(){
    return true;
}

int GameLayer::AutoCallScore(){
    return 1;
}

void GameLayer::AutoComputerPlay(){
    
}
#pragma mark ***********牌桌相关***********
void GameLayer::createTableLayer(){
    m_TableLayer = Layer::create();
    m_TableLayer->setPosition(Vec2(0, 0));
    m_TableLayer->setContentSize(Size(m_winSize.width, m_winSize.height));
    m_TableLayer->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_TableLayer,TableLayerTag);
    
    m_Clock = Sprite::create("Clock/lord_clock_bg.png");
    m_Clock->setPosition(-10000, -10000);
    m_TableLayer->addChild(m_Clock);
    
    m_ClockNum = Label::createWithCharMap("Clock/normal_clock_num.png", 23, 32, '0');
    m_ClockNum->setString("0");
    m_ClockNum->setPosition(Vec2(m_Clock->getContentSize().width/2, m_Clock->getContentSize().height/2));
    m_Clock->addChild(m_ClockNum);
    
}

void GameLayer::showClock(int time,int seat){
    Point pos = Vec2(-10000, -10000);
    switch (seat) {
        case 0:
        {
            pos = Vec2(m_winSize.width*0.2, m_winSize.height*0.82);
        }
            break;
        case 1:
        {
            pos = Vec2(m_winSize.width*0.5, m_winSize.height*0.55);
        }
            break;
        case 2:
        {
            pos = Vec2(m_winSize.width*0.8, m_winSize.height*0.82);
        }
            break;
            
        default:
            break;
    }
    
    m_Clock->setPosition(pos);
    
    m_ClockNum->setString(__String::createWithFormat("%d",time)->getCString());
    
    schedule([=](float dt){
        int num = std::atoi(m_ClockNum->getString().c_str());
        CCLOG("num = %d",num);
        
        if(CloclkTime - num == 2){
            GameLayer::hideClock();
            GameLayer::ComputerOperation();
            return;
        }
        
        if(num == 6){
            m_Clock->setTexture("Clock/lord_clock_red_bg.png");
            m_ClockNum->setCharMap("Clock/left_clock_num.png",23,32,'0');
        }
        if(num == 0){
            GameLayer::hideClock();
            if(m_CurrPlayer == 1){
                GameLayer::OutTimehandle();
            }
        }
        
        num--;
        m_ClockNum->setString(__String::createWithFormat("%d",num)->getCString());
        
    }, 1.0f, time, 1.0f,"ClockDown");
    
}

void GameLayer::hideClock(){
    m_Clock->setTexture("Clock/lord_clock_bg.png");
    m_ClockNum->setCharMap("Clock/normal_clock_num.png",23,32,'0');
    m_Clock->setPosition(-10000, -10000);
    m_ClockNum->setString("0");
    unschedule("ClockDown");
}

#pragma mark ***********调整相关***********
void GameLayer::setOrder(std::vector<PokerCard *> &card){
    for(int i=0;i<card.size();i++){
        if(card[i]->getParent() != NULL){
            card[i]->setLocalZOrder(i+1);
        }
    }
}
#pragma mark ***********理牌调整相关***********
void GameLayer::adjustCards(){
    if(m_DealIndex == m_MyCard.size()){
        unschedule("DealCard");
        return;
    }
    Point center = Vec2(0, 0);
    int centerIndex = 0;
    float delta = 0;
    
    if(m_MyCard.size() == 17){
        delta =  m_winSize.width*0.052;
    }else{
        delta =  m_winSize.width*0.044;
    }
    
    for(int i=0;i<m_DealIndex;i++){
        if(m_DealIndex%2==0){
            centerIndex = m_DealIndex/2;
            center.x = m_winSize.width/2-delta/2;
            center.y = m_winSize.height*0.048;
        }else{
            centerIndex = (m_DealIndex+1)/2;
            center.x = m_winSize.width/2;
            center.y = m_winSize.height*0.048;
        }
        
        m_MyCard[i]->setPosition(Vec2(center.x+(i-centerIndex)*delta-m_winSize.width*0.02, center.y));
    }
    
}

void GameLayer::showLeftCardNumber(){
    m_LeftCardNumber[0] = (int)m_LeftCard.size();
    m_LeftCardNumber[1] = (int)m_MyCard.size();
    m_LeftCardNumber[2] = (int)m_RightCard.size();
    
    for(int i=0;i<3;i++){
        m_LeftCardNumberLabel[i]->setString(__String::createWithFormat("%d",m_LeftCardNumber[i])->getCString());
    }
}

#pragma mark ***********背景层相关***********

void GameLayer::createBackground(){
    
    m_BackgroundLayer = Layer::create();
    m_BackgroundLayer->setPosition(Vec2(0, 0));
    m_BackgroundLayer->setContentSize(Size(m_winSize.width, m_winSize.height));
    m_BackgroundLayer->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_BackgroundLayer,BackeGroundTag);
    
    
    srand((unsigned int)time(0));
    int index = rand()%10+1;
    log("随机到第%d张背景图",index);
    if(index<1 || index>10){
        log("序号错误");
        assert(0);
        return;
    }
    
    m_BackgroundName = __String::createWithFormat("background/bg_%d.png",index)->getCString();
    m_Background = Sprite::create(m_BackgroundName.c_str());
    m_Background->setPosition(Vec2(m_winSize.width/2, m_winSize.height/2));
    m_BackgroundLayer->addChild(m_Background);
    
}

void GameLayer::changeBackground(){
    srand((unsigned int)time(0));
    int index = rand()%10+1;
    log("随机到第%d张背景图",index);
    if(index<1 || index>10){
        log("序号错误");
        assert(0);
        return;
    }
    if(strcmp(m_BackgroundName.c_str(), __String::createWithFormat("background/bg_%d.png",index)->getCString()) == 0){
        log("更换背景失败,重新更换");
        changeBackground();
    }else{
       m_BackgroundName = __String::createWithFormat("background/bg_%d.png",index)->getCString(); 
    }
}
#pragma mark ***********人物层相关***********
void GameLayer::createPlayersLayer(){
    m_PlayerLayer = Layer::create();
    m_PlayerLayer->setPosition(Vec2(0, 0));
    m_PlayerLayer->setContentSize(Size(m_winSize.width, m_winSize.height));
    m_PlayerLayer->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_PlayerLayer,PlayerLayerTag);
    
    srand((unsigned int)time(0));
    
    //左家头像
    int leftindex = rand()%HeadNumber+1;
    m_LeftPlayer = Sprite::create(__String::createWithFormat("head/head%d.png",leftindex)->getCString());
    m_LeftPlayer->setPosition(Vec2(m_winSize.width*0.1, m_winSize.height*0.8));
    m_PlayerLayer->addChild(m_LeftPlayer);
    
    m_LeftCardNumberLabel[0] = Label::createWithCharMap("playercardnumber.png", 20, 28, '0');
    m_LeftCardNumberLabel[0]->setPosition(Vec2(m_winSize.width*0.17, m_winSize.height*0.9));
    m_PlayerLayer->addChild(m_LeftCardNumberLabel[0]);
    
    m_PlayerSpeak[0] = Sprite::create("speak/lordhl_play_speak_double_left.png");
    m_PlayerSpeak[0]->setPosition(Vec2(m_winSize.width*0.17, m_winSize.height*0.87));
    m_PlayerLayer->addChild(m_PlayerSpeak[0]);
    m_PlayerSpeak[0]->setAnchorPoint(Vec2(0, 0.5));
    m_PlayerSpeak[0]->setVisible(false);
    
    //本家头像
    int myindex = rand()%HeadNumber+1;
    while (myindex == leftindex) {
        myindex = rand()%HeadNumber+1;
    }
    m_MyPlayer = Sprite::create(__String::createWithFormat("head/head%d.png",myindex)->getCString());
    m_MyPlayer->setPosition(Vec2(m_winSize.width*0.1, m_winSize.height*0.4));
    m_PlayerLayer->addChild(m_MyPlayer);
    m_LeftCardNumberLabel[1] = Label::createWithCharMap("playercardnumber.png", 20, 28, '0');
    m_LeftCardNumberLabel[1]->setPosition(Vec2(m_winSize.width*0.17, m_winSize.height*0.45));
    m_PlayerLayer->addChild(m_LeftCardNumberLabel[1]);
    
    m_PlayerSpeak[1] = Sprite::create("speak/lordhl_play_speak_double_left.png");
    m_PlayerSpeak[1]->setPosition(Vec2(m_winSize.width*0.17, m_winSize.height*0.42));
    m_PlayerLayer->addChild(m_PlayerSpeak[1]);
    m_PlayerSpeak[1]->setAnchorPoint(Vec2(0, 0.5));
    m_PlayerSpeak[1]->setVisible(false);
    
    //右家头像
    int rightindex = rand()%HeadNumber+1;
    while (rightindex == leftindex || rightindex == myindex) {
        rightindex = rand()%HeadNumber+1;
    }
    m_RightPlayer = Sprite::create(__String::createWithFormat("head/head%d.png",rightindex)->getCString());
    m_RightPlayer->setPosition(Vec2(m_winSize.width*0.9, m_winSize.height*0.8));
    m_PlayerLayer->addChild(m_RightPlayer);
    m_LeftCardNumberLabel[2] = Label::createWithCharMap("playercardnumber.png", 20, 28, '0');
    m_LeftCardNumberLabel[2]->setPosition(Vec2(m_winSize.width*0.83, m_winSize.height*0.9));
    m_PlayerLayer->addChild(m_LeftCardNumberLabel[2]);
    
    m_PlayerSpeak[2] = Sprite::create("speak/lordhl_play_speak_double_right.png");
    m_PlayerSpeak[2]->setPosition(Vec2(m_winSize.width*0.83, m_winSize.height*0.87));
    m_PlayerLayer->addChild(m_PlayerSpeak[2]);
    m_PlayerSpeak[2]->setAnchorPoint(Vec2(1, 0.5));
    m_PlayerSpeak[2]->setVisible(false);
}

#pragma mark ***********故事层相关***********
void GameLayer::createStoryLayer(){
    m_StoryLayer = LayerColor::create(Color4B(0, 0, 0, 200));
    m_StoryLayer->setPosition(Vec2(0, 0));
    m_StoryLayer->setContentSize(Size(m_winSize.width, m_winSize.height));
    m_StoryLayer->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_StoryLayer,StoryLayerTag);
    
    m_StoryInfo = GameData::getInstance()->StoryInfo;
}

void GameLayer::showStory(){
    int size = (int)GameData::getInstance()->StoryInfo.size();
    if(m_StoryInfo.size() == 0){
        //进入下一阶段
        m_StoryLayer->stopAllActions();
        MoveTo* move = MoveTo::create(0.5, Vec2(0, m_winSize.height));
        CallFunc* func = CallFunc::create([=]{
            m_StoryLayer->removeAllChildren();
            GameLayer::changeToGameState(GameDealCard);
        });

        m_StoryLayer->runAction(Sequence::create(move,func, NULL));

    }else{
        Point pos  = Vec2(m_winSize.width*0.1, m_winSize.height*((float)(0.8/(float)size)*m_StoryInfo.size()));
        
        string story = getString( m_StoryInfo[0]);
        m_StoryInfo.erase(m_StoryInfo.begin());
        
        string fontpath = "font/Arial.ttf";
        if(strcmp(getCurrentLanguage().c_str(), "zh-Hans-US") == 0){
            fontpath = "font/songti.TTF";
        }
        
        Label* storytext = Label::createWithSystemFont(story.c_str(), "Arial", 30);
        storytext->setColor(Color3B::WHITE);
        storytext->setPosition(pos);
        storytext->setAnchorPoint(Vec2(0, 0.5));
        m_StoryLayer->addChild(storytext);
        
        DelayTime* time = DelayTime::create(1.0f);
        CallFunc* func = CallFunc::create(CC_CALLBACK_0(GameLayer::showStory, this));
        m_StoryLayer->runAction(Sequence::create(time,func,NULL));
        
    }
    
    
}
#pragma mark ***********信息层相关***********
void GameLayer::createInfoLayer(){
    m_InfoLayer = Layer::create();
    m_InfoLayer->setPosition(Vec2(0, 0));
    m_InfoLayer->setContentSize(Size(m_winSize.width, m_winSize.height));
    m_InfoLayer->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_InfoLayer,InfoLayerTag);
    
    m_TopInfoPanel = Sprite::create("infolayer/gameUpPanel.png");
    m_TopInfoPanel->setPosition(Vec2(0, m_winSize.height+m_TopInfoPanel->getContentSize().height));
    m_TopInfoPanel->setAnchorPoint(Vec2(0, 1));
    m_InfoLayer->addChild(m_TopInfoPanel);
    
    Sprite* lordbg = Sprite::create("infolayer/gameLordPanel.png");
    lordbg->setPosition(Vec2(m_TopInfoPanel->getContentSize().width/2, m_TopInfoPanel->getContentSize().height));
    lordbg->setAnchorPoint(Vec2(0.5, 1));
    m_TopInfoPanel->addChild(lordbg);
    
    if(m_LordCard.size() == 3){
        for(int i=0;i<m_LordCard.size();i++){
            PokerCard* card = PokerCard::createPokerCard(m_LordCard[i]->getNumber(), m_LordCard[i]->getColor(),2);
            m_TopLordCard.push_back(card);
            card->setPosition(Vec2(m_TopInfoPanel->getContentSize().width/2+(i-1)*card->getCardSize().width*1.0f+(i-1)*5-card->getCardSize().width/2, m_TopInfoPanel->getContentSize().height*0.6));
            m_TopInfoPanel->addChild(card);
            card->setVisible(false);
        } 
    }
    
    
    
    
    Sprite* buttominfo = Sprite::create("infolayer/bottom_infobar_bg.png");
    buttominfo->setPosition(Vec2(0, 0));
    buttominfo->setAnchorPoint(Vec2(0,0));
    m_InfoLayer->addChild(buttominfo);
    buttominfo->setName("BottomInfoBar");
    
    Label* namelabel = Label::createWithSystemFont(getString("Name"), "Arial", 20);
    namelabel->setPosition(Vec2(buttominfo->getContentSize().width*0.1, buttominfo->getContentSize().height/2));
    buttominfo->addChild(namelabel);
    
    m_Nickname = Label::createWithSystemFont(GameData::getInstance()->getPlayerName().c_str(), "Arial",20);
    m_Nickname->setPosition(Vec2(buttominfo->getContentSize().width*0.14, buttominfo->getContentSize().height/2));
    m_Nickname->setAnchorPoint(Vec2(0, 0.5));
    buttominfo->addChild(m_Nickname);
    
    Sprite* goldicon = Sprite::create("infolayer/bottom_infobar_jj_gold_big.png");
    goldicon->setPosition(Vec2(buttominfo->getContentSize().width*0.4, buttominfo->getContentSize().height/2));
    buttominfo->addChild(goldicon);
    
    m_Gold = Label::createWithSystemFont(__String::createWithFormat("%d",GameData::getInstance()->getPlayerGold())->getCString(), "Arial",20);
    m_Gold->setPosition(Vec2(buttominfo->getContentSize().width*0.42, buttominfo->getContentSize().height/2));
    m_Gold->setAnchorPoint(Vec2(0, 0.5));
    buttominfo->addChild(m_Gold);

}

void GameLayer::showBaseInfo(){
    MoveTo* move = MoveTo::create(0.5, Vec2(0, m_winSize.height));
    CallFunc* func = CallFunc::create([=]{
        GameLayer::showLordCard();
    });
    m_TopInfoPanel->runAction(Sequence::create(move,func, NULL));
}

void GameLayer::showLordCard(){
    
    for(int i=0;i<m_LordCard.size();i++){
        m_LordCard[i]->setPosition(Vec2(-10000, -10000));
        m_InfoLayer->addChild(m_LordCard[i]);
        m_LordCard[i]->setScale(0.8);
    }
    
    
    Sprite* lord1 = Sprite::create("Card/lordcard/lordlz_lzbottom_frame_1.png");
    lord1->setPosition(Vec2(m_winSize.width*0.5-lord1->getContentSize().width-5, m_winSize.height*0.7));
    m_InfoLayer->addChild(lord1);
    lord1->setName("Lord1");
    
    Sprite* lord2 = Sprite::create("Card/lordcard/lordlz_lzbottom_frame_1.png");
    lord2->setPosition(Vec2(m_winSize.width*0.5, m_winSize.height*0.7));
    m_InfoLayer->addChild(lord2);
    lord2->setName("Lord2");
    
    Sprite* lord3 = Sprite::create("Card/lordcard/lordlz_lzbottom_frame_1.png");
    lord3->setPosition(Vec2(m_winSize.width*0.5+lord3->getContentSize().width+5, m_winSize.height*0.7));
    m_InfoLayer->addChild(lord3);
    lord3->setName("Lord3");
    
    if(m_LordIndex != -1){
        //选定了地主
        changeToGameState(GameGetLord);
    }else{
        //叫分
        changeToGameState(GameCallScore);
    }
}

#pragma mark ***********手牌层相关***********
void GameLayer::createHanderLayer(){
    
    m_HandCardLayer = Layer::create();
    m_HandCardLayer->setPosition(Vec2(0, 0));
    m_HandCardLayer->setContentSize(Size(m_winSize.width, m_winSize.height));
    m_HandCardLayer->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_HandCardLayer,HandCardLayerTag);
    
    for(int i=0;i<m_MyCard.size();i++){
        m_MyCard[i]->setPosition(Vec2(-10000, -10000));
        m_HandCardLayer->addChild(m_MyCard[i]);
        
    }
}



#pragma mark ***********菜单层相关***********

void GameLayer::createMenuLayer(){
    m_MenuLayer = Layer::create();
    m_MenuLayer->setPosition(Vec2(0, 0));
    m_MenuLayer->setContentSize(Size(m_winSize.width, m_winSize.height));
    m_MenuLayer->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_MenuLayer,MenuLayerTag);
    
    /**********创建打牌菜单**********/
    //要不起
    MenuItem* no_card = MenuItemSprite::create(Sprite::create("Button/playbtn/no_card_n.png"), Sprite::create("Button/playbtn/no_card_p.png"), CC_CALLBACK_0(GameLayer::PlayCallBack, this,-1));
    no_card->setPosition(Vec2(m_winSize.width/2, m_winSize.height*0.45));
    no_card->setTag(-1);
    
    //不要
    MenuItem* pass = MenuItemSprite::create(Sprite::create("Button/playbtn/pass_n.png"), Sprite::create("Button/playbtn/pass_p.png"),Sprite::create("Button/playbtn/pass_d.png"), CC_CALLBACK_0(GameLayer::PlayCallBack, this,0));
    //提示
    MenuItem* tips = MenuItemSprite::create(Sprite::create("Button/playbtn/tips_n.png"), Sprite::create("Button/playbtn/tips_p.png"), Sprite::create("Button/playbtn/tips_d.png"), CC_CALLBACK_0(GameLayer::PlayCallBack, this,1));
    //出牌
    MenuItem* play = MenuItemSprite::create(Sprite::create("Button/playbtn/play_n.png"), Sprite::create("Button/playbtn/play_p.png"), Sprite::create("Button/playbtn/play_d.png"), CC_CALLBACK_0(GameLayer::PlayCallBack, this,2));
    
    pass->setPosition(Vec2(m_winSize.width/2-tips->getContentSize().width/2-pass->getContentSize().width/2-5, m_winSize.height*0.43));
    tips->setPosition(Vec2(m_winSize.width/2, m_winSize.height*0.43));
    play->setPosition(Vec2(m_winSize.width/2+tips->getContentSize().width/2+play->getContentSize().width/2+5, m_winSize.height*0.43));
    
    
    m_PlayMenu = Menu::create(no_card,pass,tips,play, NULL);
    m_PlayMenu->setPosition(Vec2(0, 0));
    m_MenuLayer->addChild(m_PlayMenu);
    
    /**********创建叫分菜单**********/
    //不叫
    MenuItem* call0 = MenuItemSprite::create(Sprite::create("Button/scorebtn/callscore_0_n.png"), Sprite::create("Button/scorebtn/callscore_0_p.png"), Sprite::create("Button/scorebtn/callscore_0_d.png"), CC_CALLBACK_0(GameLayer::ScroeCallBack,this, 0));
    //1分
    MenuItem* call1 = MenuItemSprite::create(Sprite::create("Button/scorebtn/callscore_1_n.png"), Sprite::create("Button/scorebtn/callscore_1_p.png"), Sprite::create("Button/scorebtn/callscore_1_d.png"), CC_CALLBACK_0(GameLayer::ScroeCallBack, this,1));
    //2分
    MenuItem* call2 = MenuItemSprite::create(Sprite::create("Button/scorebtn/callscore_2_n.png"), Sprite::create("Button/scorebtn/callscore_2_p.png"), Sprite::create("Button/scorebtn/callscore_2_d.png"), CC_CALLBACK_0(GameLayer::ScroeCallBack, this,2));
    //3分
    MenuItem* call3 = MenuItemSprite::create(Sprite::create("Button/scorebtn/callscore_3_n.png"), Sprite::create("Button/scorebtn/callscore_3_p.png"), CC_CALLBACK_0(GameLayer::ScroeCallBack, this,3));
    call1->setPosition(Vec2(m_winSize.width/2-2.5-call1->getContentSize().width/2, m_winSize.height*0.43));
    call0->setPosition(Vec2(call1->getPosition().x-call1->getContentSize().width/2-call0->getContentSize().width/2-5, m_winSize.height*0.43));
    call2->setPosition(Vec2(m_winSize.width/2+2.5+call2->getContentSize().width/2, m_winSize.height*0.43));
    call3->setPosition(Vec2(call2->getPosition().x+call2->getContentSize().width/2+call3->getContentSize().width/2+5, m_winSize.height*0.43));
    
    m_CallScoreMenu = Menu::create(call0,call1,call2,call3, NULL);
    m_CallScoreMenu->setPosition(Vec2(0, 0));
    m_MenuLayer->addChild(m_CallScoreMenu);
    
    /**********创建加倍菜单**********/
    //不加倍
    MenuItem* nodouble = MenuItemSprite::create(Sprite::create("Button/doublebtn/nodouble_n.png"), Sprite::create("Button/doublebtn/nodouble_p.png"), CC_CALLBACK_0(GameLayer::DoubleCallBack, this,0));
    
    //不加倍
    MenuItem* _double = MenuItemSprite::create(Sprite::create("Button/doublebtn/double_n.png"), Sprite::create("Button/doublebtn/double_p.png"), CC_CALLBACK_0(GameLayer::DoubleCallBack, this,1));
    nodouble->setPosition(Vec2(m_winSize.width/2-2.5-nodouble->getContentSize().width/2, m_winSize.height*0.43));
    _double->setPosition(Vec2(m_winSize.width/2+2.5+_double->getContentSize().width/2, m_winSize.height*0.43));
    
    m_DoubleMenu = Menu::create(nodouble,_double, NULL);
    m_DoubleMenu->setPosition(Vec2(0, 0));
    m_MenuLayer->addChild(m_DoubleMenu);
    
}

void GameLayer::removeMenuLayer(){
    if(m_PlayMenu != NULL){
        m_PlayMenu->removeAllChildren();
        m_PlayMenu->removeFromParent();
        m_PlayMenu = NULL;
    }
    if(m_CallScoreMenu != NULL){
        m_CallScoreMenu->removeAllChildren();
        m_CallScoreMenu->removeFromParent();
        m_CallScoreMenu = NULL;
    }
    if(m_DoubleMenu != NULL){
        m_DoubleMenu->removeAllChildren();
        m_DoubleMenu->removeFromParent();
        m_DoubleMenu = NULL;
    }
    if(m_AutoPlayMenu != NULL){
        m_AutoPlayMenu->removeAllChildren();
        m_AutoPlayMenu->removeFromParent();
        m_AutoPlayMenu = NULL;
    }
    
    m_MenuLayer->removeAllChildren();
    m_MenuLayer->removeFromParent();
    m_MenuLayer = NULL;
}

void GameLayer::showMenuLayer(){
    if(m_PlayMenu != NULL){
        m_PlayMenu->setEnabled(true);
        m_PlayMenu->setVisible(true);
    }
    if(m_CallScoreMenu != NULL){
        m_CallScoreMenu->setEnabled(true);
        m_CallScoreMenu->setVisible(true);
    }
    if(m_DoubleMenu != NULL){
        m_DoubleMenu->setEnabled(true);
        m_DoubleMenu->setVisible(true);
    }
    if(m_AutoPlayMenu != NULL){
        m_AutoPlayMenu->setEnabled(true);
        m_AutoPlayMenu->setVisible(false);
    }
    
    m_MenuLayer->setVisible(true);
}

void GameLayer::hideMenuLayer(){
    if(m_PlayMenu != NULL){
        m_PlayMenu->setEnabled(false);
        m_PlayMenu->setVisible(false);
    }
    if(m_CallScoreMenu != NULL){
        m_CallScoreMenu->setEnabled(false);
        m_CallScoreMenu->setVisible(false);
    }
    if(m_DoubleMenu != NULL){
        m_DoubleMenu->setEnabled(false);
        m_DoubleMenu->setVisible(false);
    }
    if(m_AutoPlayMenu != NULL){
        m_AutoPlayMenu->setEnabled(false);
        m_AutoPlayMenu->setVisible(false);
    }
    
    m_MenuLayer->setVisible(false);
}

void GameLayer::showPlayMenu(bool show){
}

void GameLayer::showCallScoreMenu(bool show){
    hideMenuLayer();
    m_MenuLayer->setVisible(show);
    if(m_CallScoreMenu != NULL){
        m_CallScoreMenu->setEnabled(show);
        m_CallScoreMenu->setVisible(show);
    }
}

void GameLayer::showDoubleMenu(bool show){
    hideMenuLayer();
    m_MenuLayer->setVisible(show);
    if(m_DoubleMenu != NULL){
        m_DoubleMenu->setEnabled(show);
        m_DoubleMenu->setVisible(show);
    }
}

void GameLayer::showAutoPlayMenu(bool show){
}

void GameLayer::PlayCallBack(int tag){
    log("PlayCallBack ----- tag = %d",tag);
}

void GameLayer::ScroeCallBack(int tag){
    log("ScroeCallBack ----- tag = %d",tag);
}

void GameLayer::DoubleCallBack(int tag){
    log("DoubleCallBack ----- tag = %d",tag);
    hideClock();
    CallDouble();
    hideMenuLayer();
    if(tag == 1){
        Sprite* doubleicon = Sprite::create("speak/jiabei.png");
        doubleicon->setPosition(Vec2(m_winSize.width*0.02, m_winSize.height*0.5));
        m_PlayerLayer->addChild(doubleicon);
        
        m_PlayerSpeak[1]->setVisible(true);
        m_PlayerSpeak[1]->setTexture("speak/lordhl_play_speak_double_left.png");
    }else{
        m_PlayerSpeak[1]->setVisible(true);
        m_PlayerSpeak[1]->setTexture("speak/lordhl_play_speak_no_double_left.png");
    }
}

void GameLayer::AutoPlayCallBack(){
    
}

#pragma mark ***********触摸相关***********
bool GameLayer:: onTouchBegan(Touch *touch, Event *unused_event){
    if(m_StoryLayer->getPosition().y < m_winSize.height){
        m_StoryLayer->stopAllActions();
        m_StoryLayer->removeAllChildren();
        m_StoryLayer->setPositionY(m_winSize.height);
        changeToGameState(GameDealCard);
        return false;
    }
    for(int i=0;i<m_MyCard.size();i++){
        PokerCard* card = *(m_MyCard.begin()+i);
        Point pos =card->convertTouchToNodeSpace(touch);
        Rect rect;
        if(i<m_MyCard.size()-1){
            rect = Rect(0, 0, (*(m_MyCard.begin()+i+1))->getPosition().x-card->getPosition().x, card->getCardSize().height);
        }else{
            rect = Rect(0, 0, card->getCardSize().width, card->getCardSize().height);
        }
        
        if(rect.containsPoint(pos)){
            CCLOG("pos.x = %f,pos.y = %f",pos.x,pos.y);
            return true;
        }
    }
    return true;
}
void GameLayer::onTouchMoved(Touch *touch, Event *unused_event){}
void GameLayer::onTouchEnded(Touch *touch, Event *unused_event){}
void GameLayer::onTouchCancelled(Touch *touch, Event *unused_event){}






