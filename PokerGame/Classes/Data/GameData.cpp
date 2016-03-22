//
//  GameData.cpp
//  PokerGame
//
//  Created by tianrunyan on 16/3/22.
//
//

#include "GameData.h"

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