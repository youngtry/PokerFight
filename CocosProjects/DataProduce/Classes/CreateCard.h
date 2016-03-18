//
//  CreateCard.hpp
//  DataProduce
//
//  Created by tianrunyan on 16/3/3.
//
//

#ifndef CreateCard_hpp
#define CreateCard_hpp

#include "cocos2d.h"
#include "PokerCard.h"
using namespace cocos2d;
using namespace std;

class CreateCard : public Layer{
    
public:
    
    CreateCard();
    virtual ~CreateCard();
    
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    static Scene* createScene();
    
    virtual bool init();
    
    void createAllCard();
    
    CREATE_FUNC(CreateCard);
    
private:
    
    Size m_WinSize;
    
    Menu* m_Menu;
    
    Vector<PokerCard* > m_AllCard;
    Vector<PokerCard* > m_LeftCard;
    Vector<PokerCard* > m_RightCard;
    Vector<PokerCard* > m_MyCard;
    
};

#endif /* CreateCard_hpp */
