//
//  GameLogic.hpp
//  PokerGame
//
//  Created by  TianRunyan on 16/5/15.
//
//

#ifndef GameLogic_hpp
#define GameLogic_hpp

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class PokerCard;

class GameLogic:public Node {
    
public:
    GameLogic();
    ~GameLogic();
    
    static GameLogic* getInstance();
    
    bool init();
    
    int getComputerCallScore(int index,int tempscore);  //电脑人叫分逻辑
    
    bool getDoubleInfo(int index);                      //电脑人是否加倍
    
    int HandCardScore(vector<PokerCard* > card);                                //根据手牌打分，决定后面的叫分和加倍
    
private:
    
    static GameLogic* m_Instance;
    
    int m_Player0Score;     //玩家0的评分
    int m_Player2Score;     //玩家2的评分
};

#endif /* GameLogic_hpp */
