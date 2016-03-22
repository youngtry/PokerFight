//
//  GameData.hpp
//  PokerGame
//
//  Created by tianrunyan on 16/3/22.
//
//

#ifndef GameData_hpp
#define GameData_hpp

#include "cocos2d.h"
using namespace cocos2d;

class GameData {
    
public:
    GameData();
    ~GameData();
    
    static GameData* getInstance();
    
    bool init();
    
    std::vector<std::string > StoryInfo;
    int StoryCount;
    
private:
    
    static GameData* m_Instance;

};

#endif /* GameData_hpp */
