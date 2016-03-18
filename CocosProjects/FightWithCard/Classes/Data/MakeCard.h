//
//  MakeCard.hpp
//  FightWithCard
//
//  Created by tianrunyan on 16/3/11.
//
//

#ifndef MakeCard_hpp
#define MakeCard_hpp

#include "cocos2d.h"
#include "PokerCard.h"

using namespace cocos2d;

class MakeCard {
    
public:
    MakeCard();
    ~MakeCard();
    
    static MakeCard* getInstance();
    
    void initData(std::string filename);
    
    void createAllCard();
    
    bool removeCardFromAll(int number,PokerColor color);
    
    void createPlayersCard();
    
    std::vector<PokerCard* > m_AllCard;
    std::vector<PokerCard* > m_LeftCard;
    std::vector<PokerCard* > m_MyCard;
    std::vector<PokerCard* > m_RightCard;
    
    std::vector<PokerCard* > m_LordCard;
    
    int m_LordIndex;
private:
    
    static MakeCard* m_Instance;
    
    
    std::vector<std::pair<int, PokerColor> > m_LeftCardData;
    std::vector<std::pair<int, PokerColor> > m_MyCardData;
    std::vector<std::pair<int, PokerColor> > m_RightCardData;
    
    
};

#endif /* MakeCard_hpp */
