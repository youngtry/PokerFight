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
{
    m_LeftCard.clear();
    m_MyCard.clear();
    m_RightCard.clear();
    m_LordCard.clear();
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
    
    //初始化数据
    m_winSize = Director::getInstance()->getWinSize();
    
    m_LordIndex = MakeCard::getInstance()->m_LordIndex;
    m_LeftCard = MakeCard::getInstance()->m_LeftCard;
    m_MyCard = MakeCard::getInstance()->m_MyCard;
    m_RightCard = MakeCard::getInstance()->m_RightCard;
    m_LordCard = MakeCard::getInstance()->m_LordCard;
    
    string a = getString("ShowText");
    log("showText = %s",a.c_str());
    
    changeToGameState(GameReady);
    return true;
}
#pragma mark ***********流程控制***********
void GameLayer::changeToGameState(GameState state){
    if(state == GameReady){
        //准备状态，铺设基本UI
        createBackground();
        createPlayersLayer();
        return;
    }
    
    if(state == GameDealCard){
        
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
    
    
    //左家头像
    int leftindex = rand()%HeadNumber+1;
    m_LeftPlayer = Sprite::create(__String::createWithFormat("head/head%d.png",leftindex)->getCString());
    m_LeftPlayer->setPosition(Vec2(m_winSize.width*0.1, m_winSize.height*0.8));
    m_PlayerLayer->addChild(m_LeftPlayer);
    
    //本家头像
    int myindex = rand()%HeadNumber+1;
    while (myindex == leftindex) {
        myindex = rand()%HeadNumber+1;
    }
    m_MyPlayer = Sprite::create(__String::createWithFormat("head/head%d.png",myindex)->getCString());
    m_MyPlayer->setPosition(Vec2(m_winSize.width*0.1, m_winSize.height*0.4));
    m_PlayerLayer->addChild(m_MyPlayer);
    
    //右家头像
    int rightindex = rand()%HeadNumber+1;
    while (rightindex == leftindex || rightindex == myindex) {
        rightindex = rand()%HeadNumber+1;
    }
    m_RightPlayer = Sprite::create(__String::createWithFormat("head/head%d.png",rightindex)->getCString());
    m_RightPlayer->setPosition(Vec2(m_winSize.width*0.9, m_winSize.height*0.8));
    m_PlayerLayer->addChild(m_RightPlayer);
}

#pragma mark ***********故事层相关***********
void GameLayer::createStoryLayer(){
    m_StoryLayer = Layer::create();
    m_StoryLayer->setPosition(Vec2(0, 0));
    m_StoryLayer->setContentSize(Size(m_winSize.width, m_winSize.height));
    m_StoryLayer->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_StoryLayer,StoryLayerTag); 
    
    m_RoundIndex = UserDefault::getInstance()->getIntegerForKey("RoundIndex", 1);
    
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
    no_card->setPosition(Vec2(m_winSize.width/2, m_winSize.height*0.4));
    no_card->setTag(-1);
    
    //不要
    MenuItem* pass = MenuItemSprite::create(Sprite::create("Button/playbtn/pass_n.png"), Sprite::create("Button/playbtn/pass_p.png"),Sprite::create("Button/playbtn/pass_d.png"), CC_CALLBACK_0(GameLayer::PlayCallBack, this,0));
    //提示
    MenuItem* tips = MenuItemSprite::create(Sprite::create("Button/playbtn/tips_n.png"), Sprite::create("Button/playbtn/tips_p.png"), Sprite::create("Button/playbtn/tips_d.png"), CC_CALLBACK_0(GameLayer::PlayCallBack, this,1));
    //出牌
    MenuItem* play = MenuItemSprite::create(Sprite::create("Button/playbtn/play_n.png"), Sprite::create("Button/playbtn/play_p.png"), Sprite::create("Button/playbtn/play_d.png"), CC_CALLBACK_0(GameLayer::PlayCallBack, this,2));
    
    pass->setPosition(Vec2(m_winSize.width/2-tips->getContentSize().width/2-pass->getContentSize().width/2-5, m_winSize.height*0.4));
    tips->setPosition(Vec2(m_winSize.width/2, m_winSize.height*0.4));
    play->setPosition(Vec2(m_winSize.width/2+tips->getContentSize().width/2+play->getContentSize().width/2+5, m_winSize.height*0.4));
    
    
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
    call1->setPosition(Vec2(m_winSize.width/2-2.5-call1->getContentSize().width/2, m_winSize.height*0.4));
    call0->setPosition(Vec2(call1->getPosition().x-call1->getContentSize().width/2-call0->getContentSize().width/2-5, m_winSize.height*0.4));
    call2->setPosition(Vec2(m_winSize.width/2+2.5+call2->getContentSize().width/2, m_winSize.height*0.4));
    call3->setPosition(Vec2(call2->getPosition().x+call2->getContentSize().width/2+call3->getContentSize().width/2+5, m_winSize.height*0.4));
    
    m_CallScoreMenu = Menu::create(call0,call1,call2,call3, NULL);
    m_CallScoreMenu->setPosition(Vec2(0, 0));
    m_MenuLayer->addChild(m_CallScoreMenu);
    
    /**********创建加倍菜单**********/
    //不加倍
    MenuItem* nodouble = MenuItemSprite::create(Sprite::create("Button/doublebtn/nodouble_n.png"), Sprite::create("Button/doublebtn/nodouble_p.png"), CC_CALLBACK_0(GameLayer::DoubleCallBack, this,0));
    
    //不加倍
    MenuItem* _double = MenuItemSprite::create(Sprite::create("Button/doublebtn/double_n.png"), Sprite::create("Button/doublebtn/double_p.png"), CC_CALLBACK_0(GameLayer::DoubleCallBack, this,1));
    nodouble->setPosition(Vec2(m_winSize.width/2-2.5-nodouble->getContentSize().width/2, m_winSize.height*0.4));
    _double->setPosition(Vec2(m_winSize.width/2+2.5+_double->getContentSize().width/2, m_winSize.height*0.4));
    
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
    }
    if(m_CallScoreMenu != NULL){
        m_CallScoreMenu->setEnabled(true);
    }
    if(m_DoubleMenu != NULL){
        m_DoubleMenu->setEnabled(true);
    }
    if(m_AutoPlayMenu != NULL){
        m_AutoPlayMenu->setEnabled(true);
    }
    
    m_MenuLayer->setVisible(true);
}

void GameLayer::hideMenuLayer(){
    if(m_PlayMenu != NULL){
        m_PlayMenu->setEnabled(false);
    }
    if(m_CallScoreMenu != NULL){
        m_CallScoreMenu->setEnabled(false);
    }
    if(m_DoubleMenu != NULL){
        m_DoubleMenu->setEnabled(false);
    }
    if(m_AutoPlayMenu != NULL){
        m_AutoPlayMenu->setEnabled(false);
    }
    
    m_MenuLayer->setVisible(false);
}

void GameLayer::showPlayMenu(bool show){
}

void GameLayer::showCallScoreMenu(bool show){
}

void GameLayer::showDoubleMenu(bool show){
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
}

void GameLayer::AutoPlayCallBack(){
    
}





