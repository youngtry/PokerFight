//
//  MakeCard.cpp
//  FightWithCard
//
//  Created by tianrunyan on 16/3/11.
//
//

#include "MakeCard.h"
#include "AnalysisData.h"
using namespace std;
MakeCard* MakeCard::m_Instance = NULL;

MakeCard::MakeCard(){
}

MakeCard::~MakeCard(){
}

MakeCard* MakeCard::getInstance(){
    if(m_Instance == NULL){
        m_Instance = new MakeCard();
    }
    return m_Instance;
}

void MakeCard::initData(std::string filename){

    AnalysisData* data = AnalysisData::createData();
    data->init(filename);
    data->getPlayInfo(m_LordIndex, m_LeftCardData, m_MyCardData, m_RightCardData);
    log("lordIndex = %d",m_LordIndex);
    log("left.size() = %lu",m_LeftCardData.size());
    log("my.size() = %lu",m_MyCardData.size());
    log("right.size() = %lu",m_RightCardData.size());
    
    createAllCard();
    createPlayersCard();
}

void MakeCard::createAllCard(){
    for(int i=0;i<4;i++){
        for(int j=1;j<14;j++){
            if(!removeCardFromAll(j, (PokerColor)i)){
                PokerCard* card = PokerCard::createPokerCard(j, (PokerColor)i);
                m_AllCard.push_back(card);
            }
        }
    }
    
    PokerCard* card1 = PokerCard::createPokerCard(14, COLOR_XIAOWANG);
    PokerCard* card2 = PokerCard::createPokerCard(15, COLOR_DAWANG);
    
    m_AllCard.push_back(card1);
    m_AllCard.push_back(card2);
}

void MakeCard::createPlayersCard(){
    //打乱所有牌

    srand((unsigned int)time(0));
    
    int orgsize = (int)m_AllCard.size();
    vector<PokerCard* >temp;
    temp.clear();
    for(int i=0;i<orgsize;i++){
        int index = rand()%(m_AllCard.size());
        vector<PokerCard* >::iterator itr = m_AllCard.begin();
        if(m_AllCard.size()>0){
            PokerCard* card = PokerCard::createPokerCard(m_AllCard[index]->getNumber(), m_AllCard[index]->getColor());
            temp.push_back(card);
            m_AllCard.erase(itr+index);
            CCLOG("m_AllCard.size = %lu",m_AllCard.size());
        }
    }
    
    m_AllCard.clear();
    m_AllCard = temp;
    
    //把预设牌先压进容器
    if(m_LeftCardData.size()>0){
        for(int i=0;i<m_LeftCardData.size();i++){
            PokerCard* card = PokerCard::createPokerCard(m_LeftCardData[i].first, m_LeftCardData[i].second);
            m_LeftCard.push_back(card);
        }
    }
    
    if(m_MyCardData.size()>0){
        for(int i=0;i<m_MyCardData.size();i++){
            PokerCard* card = PokerCard::createPokerCard(m_MyCardData[i].first, m_MyCardData[i].second);
            m_MyCard.push_back(card);
        }
    }
    
    if(m_RightCardData.size()>0){
        for(int i=0;i<m_RightCardData.size();i++){
            PokerCard* card = PokerCard::createPokerCard(m_RightCardData[i].first, m_RightCardData[i].second);
            m_RightCard.push_back(card);
        }
    }
    
    //分发牌给三个玩家
    for(int i=0;i<17-m_LeftCardData.size();i++){
        if(i>=m_AllCard.size()){
            break;
        }
        PokerCard* card = PokerCard::createPokerCard(m_AllCard[i]->getNumber(), m_AllCard[i]->getColor());
        m_LeftCard.push_back(card);
    }
    
    for(int i=17-(int)m_LeftCardData.size();i<34-m_MyCardData.size()-m_LeftCardData.size();i++){
        if(i>=m_AllCard.size()){
            break;
        }
        PokerCard* card = PokerCard::createPokerCard(m_AllCard[i]->getNumber(), m_AllCard[i]->getColor());
        m_MyCard.push_back(card);
    }
    
    for(int i=34-(int)m_MyCardData.size()-(int)m_LeftCardData.size();i<51-m_LeftCardData.size()-m_MyCardData.size()-m_RightCardData.size();i++){
        if(i>=m_AllCard.size()){
            break;
        }
        PokerCard* card = PokerCard::createPokerCard(m_AllCard[i]->getNumber(), m_AllCard[i]->getColor());
        m_RightCard.push_back(card);
    }
    
    //地主牌
    for(int i=51-(int)m_LeftCardData.size()-(int)m_MyCardData.size()-(int)m_RightCardData.size();i<m_AllCard.size();i++){
        PokerCard* card = PokerCard::createPokerCard(m_AllCard[i]->getNumber(), m_AllCard[i]->getColor());
        m_LordCard.push_back(card);
    }
    
    sequenceCards(m_MyCard);
    sequenceCards(m_LeftCard);
    sequenceCards(m_RightCard);

}

bool MakeCard::removeCardFromAll(int number,PokerColor color){
    if(m_LeftCardData.size()>0){
        for(int i=0;i<m_LeftCardData.size();i++){
            if(number == m_LeftCardData[i].first && color == m_LeftCardData[i].second){
                return true;
            }
        }
    }
    
    if(m_MyCardData.size()>0){
        for(int i=0;i<m_MyCardData.size();i++){
            if(number == m_MyCardData[i].first && color == m_MyCardData[i].second){
                return true;
            }
        }
    }
    
    if(m_RightCardData.size()>0){
        for(int i=0;i<m_RightCardData.size();i++){
            if(number == m_RightCardData[i].first && color == m_RightCardData[i].second){
                return true;
            }
        }
    }
    
    return false;
}

void MakeCard::sequenceCards(std::vector<PokerCard *> &card){
    for(int i=0;i<card.size();i++){
        for(int j=0;j<card.size()-i-1;j++){
            if(card[j]->getValue()<card[j+1]->getValue()){
                PokerCard* card1 = card[j];
                card[j] = card[j+1];
                card[j+1] = card1;
            }
        }
    }
}

void MakeCard::sequenceCardsWithBigger(std::vector<PokerCard *> &card){
    for(int i=0;i<card.size();i++){
        for(int j=0;j<card.size()-i-1;j++){
            if(card[j]->getValue()>card[j+1]->getValue()){
                PokerCard* card1 = card[j];
                card[j] = card[j+1];
                card[j+1] = card1;
            }
        }
    }
}




