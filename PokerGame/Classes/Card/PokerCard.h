//
//  PokerCard.hpp
//  DataProduce
//
//  Created by tianrunyan on 16/3/8.
//
//

#ifndef PokerCard_h
#define PokerCard_h

#include "cocos2d.h"
using namespace cocos2d;

typedef enum {
    COLOR_FANGPIAN = 0,           //方片
    COLOR_MEIHUA,               //梅花
    COLOR_HONGTAO,            //红桃
    COLOR_HEITAO ,           //黑桃
    COLOR_XIAOWANG,         //小王
    COLOR_DAWANG,              //大王
    COLOR_NULL,                     //空值
}PokerColor;

class PokerCard : public Sprite {
    
public:
    
    PokerCard(int number,PokerColor color,int size = 1);
    PokerCard();
    virtual ~PokerCard();
    
    static PokerCard* createPokerCard(int number,PokerColor color,int size = 1);
    
    virtual bool init();
    
    void initCard();
    
    Size getCardSize(){return m_CardSize;};
    
    int getNumber() {return m_Number;};
    PokerColor getColor(){return m_Color;};
    int getValue(){return m_Value;};
    
private:
    
    int m_Number;
    PokerColor m_Color;
    int m_Value;
    int m_Size;
    Sprite* m_Card;
    Size m_CardSize;
    
};

#endif /* PokerCard_h */
