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

bool CardAnalysis::CanFixSingle(vector<PokerCard* > card,vector<PokerCard* > origincard){
    if(card.size() ==1){
        return true;
    }
    return false;
}

bool CardAnalysis::CanFixDouble(vector<PokerCard* > card,vector<PokerCard* > origincard){
    if(card.size() == 2){
        if(GetSameValueCount(card, card[0]->getValue()) ==2){
            return true;
        }
    }
    
    return false;
}

bool CardAnalysis::CanFixSanZhang(vector<PokerCard* > card,vector<PokerCard* > origincard){
    if(card.size() == 3){
        if(GetSameValueCount(card, card[0]->getValue()) ==3){
            return true;
        }
    }
    return false;
}

bool CardAnalysis::CanFixSanDaiyi(vector<PokerCard* > card,vector<PokerCard* > origincard){
    MakeCard::getInstance()->sequenceCards(card);
    if(card.size()==4){
        if(GetSameValueCount(card, card[0]->getValue()) == 3 || GetSameValueCount(card, card[3]->getValue()) == 3){
            return true;
        }
    }
    
    return false;
}

bool CardAnalysis::CanFixSanDaier(vector<PokerCard* > card,vector<PokerCard* > origincard){
    MakeCard::getInstance()->sequenceCards(card);
    if(card.size()==5){
        if(GetDeffrientValueCount(card) == 2 || GetSameValueCount(card, card[0]->getValue()) == 3 || GetSameValueCount(card, card[3]->getValue()) == 3){
            return true;
        }
    }
    
    return false;
}

bool CardAnalysis::CanFixShunzi(vector<PokerCard* > card,vector<PokerCard* > origincard,int count){
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

bool CardAnalysis::CanFixLiandui(vector<PokerCard* > card,vector<PokerCard* > origincard,int count){
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

bool CardAnalysis::CanFixFeiji(vector<PokerCard* > card,vector<PokerCard* > origincard,int count){
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

bool CardAnalysis::CanFixFeijiDaidan(vector<PokerCard* > card,vector<PokerCard* > origincard,int count){
    if(card.size() == count*4){
        vector<PokerCard* > feiji;
        vector<PokerCard* > dan;
        vector<PokerCard* >::iterator itr = card.begin();
        while (itr != card.end()) {
            PokerCard* poker = *itr;
        }
    }
    
    return false;
}

bool CardAnalysis::CanFixFeijiDaidui(vector<PokerCard* > card,vector<PokerCard* > origincard,int count){
     return false;
}

bool CardAnalysis::CanFixZhadan(vector<PokerCard* > card,vector<PokerCard* > origincard,int count){
     return false;
}

bool CardAnalysis::CanFixWangzha(vector<PokerCard* > card,vector<PokerCard* > origincard){
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


