//
//  GameData.cpp
//  PokerGame
//
//  Created by tianrunyan on 16/3/22.
//
//

#include "GameData.h"
#include "../Tools/tools.h"

using namespace std;

GameData* GameData::m_Instance = NULL;

GameData::GameData(){
    StoryInfo.clear();
    StoryCount = 0;
}

GameData::~GameData(){
    
}

GameData* GameData::getInstance(){
    if(m_Instance == NULL){
        m_Instance = new GameData();
        m_Instance->init();
    }
    return m_Instance;
}

bool GameData::init(){
    return true;
}

string GameData::getPlayerName(){
    if(UserDefault::getInstance()->getBoolForKey("FirstIn", true)){
        srand((unsigned int)time(0));
        int namechuan = rand()%1000000000;
        CCLOG("namechuan = %d",namechuan);
        
        UserDefault::getInstance()->setIntegerForKey("PlayerGold", 2000);
        
        UserDefault::getInstance()->setStringForKey("NickName",__String::createWithFormat("%s%d",getString("NamePre").c_str(),namechuan)->getCString());
        
        UserDefault::getInstance()->setBoolForKey("FirstIn", false);
        UserDefault::getInstance()->flush();
    }
    
    return UserDefault::getInstance()->getStringForKey("NickName");
    
}

void GameData::setPlayerName(std::string name){
    UserDefault::getInstance()->setStringForKey("NickName",name.c_str());
    UserDefault::getInstance()->flush();
}

int GameData::getPlayerGold(){
    if(UserDefault::getInstance()->getBoolForKey("FirstIn", true)){
        srand((unsigned int)time(0));
        int namechuan = rand()%1000000000;
        CCLOG("namechuan = %d",namechuan);
        
        UserDefault::getInstance()->setIntegerForKey("PlayerGold", 2000);
        
        UserDefault::getInstance()->setStringForKey("NickName",__String::createWithFormat("%s%d",getString("NamePre").c_str(),namechuan)->getCString());
        
        UserDefault::getInstance()->setBoolForKey("FirstIn", false);
        UserDefault::getInstance()->flush();
    }
    
    return UserDefault::getInstance()->getIntegerForKey("PlayerGold");
}

void GameData::setPlayerGold(int gold){
    UserDefault::getInstance()->setIntegerForKey("PlayerGold", gold);
    UserDefault::getInstance()->flush();
}