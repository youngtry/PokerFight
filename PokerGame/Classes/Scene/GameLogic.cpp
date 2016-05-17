//
//  GameLogic.cpp
//  PokerGame
//
//  Created by  TianRunyan on 16/5/15.
//
//

#include "GameLogic.h"
#include "../Data/MakeCard.h"


GameLogic* GameLogic::m_Instance = NULL;

GameLogic::GameLogic()
:m_Player0Score(0)
,m_Player2Score(0)
{
    
}

GameLogic::~GameLogic(){
    
}

GameLogic* GameLogic::getInstance(){
    if(m_Instance == NULL){
        m_Instance = new GameLogic();
        m_Instance->init();
    }
    return m_Instance;
}

bool GameLogic::init(){
    m_Player0Score = HandCardScore(MakeCard::getInstance()->m_LeftCard);
    m_Player2Score = HandCardScore(MakeCard::getInstance()->m_RightCard);
    return true;
}

int GameLogic::getComputerCallScore(int index, int tempscore){
    if(tempscore<3){
        return tempscore+1;
    }
    return 0;
}

bool GameLogic::getDoubleInfo(int index){
    return true;
}

int GameLogic::HandCardScore(vector<PokerCard *> card){
    m_HandCard.assign(card.begin(), card.end());
    return 100;
}

void GameLogic::ChooseSpecialCard(){
    
}






