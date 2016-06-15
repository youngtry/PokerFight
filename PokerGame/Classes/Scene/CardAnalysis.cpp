//
//  CardAnalysis.cpp
//  PokerGame
//
//  Created by tianrunyan on 16/5/17.
//
//

#include "CardAnalysis.h"
#include "../Card/PokerCard.h"
#include "../Data/MakeCard.h"

CardAnalysis::CardAnalysis(){
}

CardAnalysis::~CardAnalysis(){
}

CardAnalysis* CardAnalysis::CreateAnalysis(){
    CardAnalysis* pRset = new CardAnalysis();
    if(pRset != NULL){
        pRset->autorelease();
        return pRset;
    }
    
    CC_SAFE_DELETE(pRset);
    return NULL;
}

bool CardAnalysis::CanMatchOthers(vector<PokerCard *> card, vector<PokerCard *> origincard){
    
}

bool CardAnalysis::CanFixSingle(vector<PokerCard* > card){
    if(card.size() ==1){
        return true;
    }
    return false;
}

bool CardAnalysis::CanFixDouble(vector<PokerCard* > card){
    if(card.size() == 2){
        if(GetSameValueCount(card, card[0]->getValue()) ==2){
            return true;
        }
    }
    
    return false;
}

bool CardAnalysis::CanFixSanZhang(vector<PokerCard* > card){
    if(card.size() == 3){
        if(GetSameValueCount(card, card[0]->getValue()) ==3){
            return true;
        }
    }
    return false;
}

bool CardAnalysis::CanFixSanDaiyi(vector<PokerCard* > card){
    MakeCard::getInstance()->sequenceCards(card);
    if(card.size()==4){
        if(GetSameValueCount(card, card[0]->getValue()) == 3 || GetSameValueCount(card, card[3]->getValue()) == 3){
            return true;
        }
    }
    
    return false;
}

bool CardAnalysis::CanFixSanDaier(vector<PokerCard* > card){
    MakeCard::getInstance()->sequenceCards(card);
    if(card.size()==5){
        if(GetDeffrientValueCount(card) == 2 || GetSameValueCount(card, card[0]->getValue()) == 3 || GetSameValueCount(card, card[3]->getValue()) == 3){
            return true;
        }
    }
    
    return false;
}

bool CardAnalysis::CanFixShunzi(vector<PokerCard* > card,int count){
    if(card.size() == count){
        MakeCard::getInstance()->sequenceCards(card);
        int value = card[0]->getValue();
        for(int i=1;i<count;i++){
            if(value - card[i]->getValue() != 1){
                return false;
            }else{
                value = card[i]->getValue();
            }
        }
        return true;
    }
    return false;
}

bool CardAnalysis::CanFixLiandui(vector<PokerCard* > card,int count){
    if(card.size() == count*2){
        MakeCard::getInstance()->sequenceCards(card);
        int value = card[0]->getValue();
        for(int i=2;i<count;){
            if(value - card[i]->getValue() != 1){
                return false;
            }else{
                value = card[i]->getValue();
                i=i+2;
            }
        }
        return true;
    }
    return false;
}

bool CardAnalysis::CanFixFeiji(vector<PokerCard* > card,int count){
    if(card.size() == count*3){
        MakeCard::getInstance()->sequenceCards(card);
        int value = card[0]->getValue();
        for(int i=3;i<count;){
            if(value - card[i]->getValue() != 1){
                return false;
            }else{
                value = card[i]->getValue();
                i=i+3;
            }
        }
        return true;
    }
    return false;
}

bool CardAnalysis::CanFixFeijiDaidan(vector<PokerCard* > card,int count){
    if(card.size() == count*4){
        vector<PokerCard* > feiji;
        vector<PokerCard* > dan;
        vector<PokerCard* >::iterator itr = card.begin();
        while (itr != card.end()) {
            PokerCard* poker = *itr;
            if(GetSameValueCount(card, poker->getValue()) == 3){
                PokerCard* _poker = PokerCard::createPokerCard(poker->getNumber(), poker->getColor());
                feiji.push_back(_poker);
            }else if (GetSameValueCount(card, poker->getValue()) == 1){
                PokerCard* _poker = PokerCard::createPokerCard(poker->getNumber(), poker->getColor());
                dan.push_back(_poker);
            }
            itr++;
        }
        if(CanFixFeiji(feiji,count) && dan.size() == count && feiji.size()+dan.size() == card.size()){
            return true;
        }
    }
    
    return false;
}

bool CardAnalysis::CanFixFeijiDaidui(vector<PokerCard* > card,int count){
    if(card.size() == count*5){
        vector<PokerCard* > feiji;
        vector<PokerCard* > dan;
        vector<PokerCard* >::iterator itr = card.begin();
        while (itr != card.end()) {
            PokerCard* poker = *itr;
            if(GetSameValueCount(card, poker->getValue()) == 3){
                PokerCard* _poker = PokerCard::createPokerCard(poker->getNumber(), poker->getColor());
                feiji.push_back(_poker);
            }else if (GetSameValueCount(card, poker->getValue()) == 2){
                PokerCard* _poker = PokerCard::createPokerCard(poker->getNumber(), poker->getColor());
                dan.push_back(_poker);
            }
            itr++;
        }
        if(CanFixFeiji(feiji,count) && dan.size() == count*2 && feiji.size()+dan.size() == card.size()){
            return true;
        }
    }
    
    return false;
}

bool CardAnalysis::CanFixZhadan(vector<PokerCard* > card,int count){
    if(card.size()== count){
        if(GetSameValueCount(card, card[0]->getValue())==count){
            return true;
        }
    }
     return false;
}

bool CardAnalysis::CanFixWangzha(vector<PokerCard* > card){
    if(card.size() == 2){
        MakeCard::getInstance()->sequenceCards(card);
        if(card[0]->getValue() == 17 && card[1]->getValue() == 16){
            return true;
        }
    }
     return false;
}

int CardAnalysis::GetSameValueCount(vector<PokerCard *> card, int value){
    int count = 0;
    vector<PokerCard* >::iterator itr = card.begin();
    while(itr != card.end()){
        PokerCard* poker = *itr;
        if(poker->getValue() == value){
            count++;
        }
        itr++;
    }
    return count;
}

int CardAnalysis::GetDeffrientValueCount(vector<PokerCard *> card){
    int count = 0;
    int value = 0;
    MakeCard::getInstance()->sequenceCards(card);
    vector<PokerCard* >::iterator itr = card.begin();
    while (itr != card.end()) {
        PokerCard* poker = *itr;
        if(poker->getValue() != value){
            count++;
            value = poker->getValue();
        }
        itr++;
    }
    
    return count;
}

#pragma mark 提取各种牌型的全部组合(包括拆牌的)

void CardAnalysis::getAllSingle(vector<PokerCard *> &AllTips, vector<PokerCard *> &AllCards, vector<PokerCard *> origincard){
    MakeCard::getInstance()->sequenceCardsWithBigger(origincard);
    
    
}

void CardAnalysis::getAllDoubles(vector<PokerCard* > &AllTips,vector<PokerCard* > &AllCards,vector<PokerCard* > origincard){
    
}

void CardAnalysis::getAllSanzhang(vector<PokerCard* > &AllTips,vector<PokerCard* > &AllCards,vector<PokerCard* > origincard){
}

void CardAnalysis::getAllSandaiyi(vector<PokerCard* > &AllTips,vector<PokerCard* > &AllCards,vector<PokerCard* > origincard){
}

void CardAnalysis::getAllSandaier(vector<PokerCard* > &AllTips,vector<PokerCard* > &AllCards,vector<PokerCard* > origincard){
}

void CardAnalysis::getAllShunzi(vector<PokerCard* > &AllTips,vector<PokerCard* > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllLiandui(vector<PokerCard* > &AllTips,vector<PokerCard* > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllFeiji(vector<PokerCard* > &AllTips,vector<PokerCard* > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllFeijidaidan(vector<PokerCard* > &AllTips,vector<PokerCard* > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllFeijidaidui(vector<PokerCard* > &AllTips,vector<PokerCard* > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllZhadan(vector<PokerCard* > &AllTips,vector<PokerCard* > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllWangzha(vector<PokerCard* > &AllTips,vector<PokerCard* > &AllCards,vector<PokerCard* > origincard){
}




