//
//  CreateCard.cpp
//  DataProduce
//
//  Created by tianrunyan on 16/3/3.
//
//

#include "CreateCard.h"

CreateCard::CreateCard()
:m_Menu(NULL)
{
    
}

CreateCard::~CreateCard(){
    
}

Scene* CreateCard::createScene(){
    auto scene = Scene::create();
    auto layer = CreateCard::create();
    scene->addChild(layer);
    return scene;
}

bool CreateCard::init(){
    if(!Layer::init()){
        return false;
    }
    m_WinSize = Director::getInstance()->getWinSize();
    LayerColor* bg = LayerColor::create(Color4B::WHITE, m_WinSize.width, m_WinSize.height);
    bg->setPosition(Vec2::ZERO);
    addChild(bg);
    
    MenuItem* createbtn = MenuItemSprite::create(Sprite::create("button/buttondi_n.png"), Sprite::create("button/buttondi_d.png"));
    createbtn->setCallback(CC_CALLBACK_0(CreateCard::createAllCard, this));
    createbtn->setPosition(Vec2(m_WinSize.width/2, m_WinSize.height/2));
    createbtn->setTag(1);
    createbtn->setName("createbtn");
    
    m_Menu = Menu::create(createbtn, NULL);
    m_Menu->setPosition(Vec2::ZERO);
    addChild(m_Menu);

    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CreateCard::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CreateCard::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(CreateCard::onTouchCancelled, this);
    listener->onTouchEnded = CC_CALLBACK_2(CreateCard::onTouchEnded, this);
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void CreateCard::createAllCard(){
    log("createAllCard");
    
    MenuItemSprite* createbtn = (MenuItemSprite*)m_Menu->getChildByName("createbtn");
    createbtn->setVisible(false);
    createbtn->setEnabled(false);
    
    for(int i=0;i<54;i++){
        int num = (i+1)%13;
        PokerColor color = PokerColor((i+1)/13);
        if(i == 51){
            color = COLOR_HEITAO;
            num = 13;
        }else if(i == 52){
            color = COLOR_XIAOWANG;
            num = 1;
        }else if (i == 53){
            color  = COLOR_DAWANG;
            num = 2;
        }
        PokerCard* card = PokerCard::createPokerCard(num, color);
        card->setPosition(Vec2(m_WinSize.width*0.2+(i%13)*m_WinSize.width*0.04, m_WinSize.height*0.6-(i/13)*m_WinSize.height*0.08));
        addChild(card);
        m_AllCard.pushBack(card);
        card->setScale(0.7, 0.7);
    }

}

bool CreateCard:: onTouchBegan(Touch *touch, Event *unused_event){
    for(int i=0;i<m_AllCard.size();i++){
        PokerCard* card = *(m_AllCard.begin()+i);
        Point pos =card->convertTouchToNodeSpace(touch);
        Rect rect;
        if(i<m_MyCard.size()-1){
            rect = Rect(0, 0, (*(m_AllCard.begin()+i+1))->getPosition().x-card->getPosition().x, card->getCardSize().height);
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
void CreateCard::onTouchMoved(Touch *touch, Event *unused_event){}
void CreateCard::onTouchEnded(Touch *touch, Event *unused_event){}
void CreateCard::onTouchCancelled(Touch *touch, Event *unused_event){}
