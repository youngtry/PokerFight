//
//  PokerCard.cpp
//  DataProduce
//
//  Created by tianrunyan on 16/3/8.
//
//

#include "PokerCard.h"

PokerCard::PokerCard(int number,PokerColor color,int size){
    Sprite::init();
    m_Number = number;
    m_Color = color;
    m_Value = 0;
    m_Size = size;
    m_CardSize.width = 0;
    m_CardSize.height = 0;
    initCard();
    setAnchorPoint(Vec2(0, 0));
}

PokerCard::PokerCard(){
}

PokerCard::~PokerCard(){
}

PokerCard* PokerCard::createPokerCard(int number, PokerColor color,int size){
    PokerCard * card = new PokerCard(number,color,size);
    if (card && card->init())
    {
        return card;
    }
    CC_SAFE_DELETE(card);
    return NULL;
}

bool PokerCard::init(){
    if(!Sprite::init()){
        return false;
    }
    return true;
}

void PokerCard::initCard(){
    this->removeAllChildrenWithCleanup(true);
    if(m_Number == 14){
        m_Card = Sprite::create(__String::createWithFormat("Card/%d/%d.png",m_Size,m_Number)->getCString());
        m_Color = COLOR_XIAOWANG;
        m_Value = 16;
    }else if(m_Number == 15){
        m_Card = Sprite::create(__String::createWithFormat("Card/%d/%d.png",m_Size,m_Number)->getCString());
        m_Color = COLOR_DAWANG;
        m_Value = 17;
    }else{
        m_Card = Sprite::create(__String::createWithFormat("Card/%d/%d_%d.png",m_Size,m_Number,m_Color)->getCString());
        if(m_Number == 1){
            m_Value = 14;
        }else if (m_Number == 2){
            m_Value = 15;
        }else{
            m_Value = m_Number;
        }
    }
    
    m_Card->setPosition(Vec2(0, 0));
    m_Card->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_Card);
    
    m_CardSize = m_Card->getContentSize();
    
}

