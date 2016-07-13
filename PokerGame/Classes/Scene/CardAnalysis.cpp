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
    _MinValue = 0;
    m_TempTipCard.clear();
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

int a[100];
void CardAnalysis::GetSameValueCardsWithsCount(vector<PokerCard* > card,int value,int count,bool isAll){
    
    m_TempTipCard.clear();
    
    if(GetSameValueCount(card, value) < count){
        CCLOG("少于所需张数");
        return;
    }
    int _count = GetSameValueCount(card, value);
    int num = getCountKind(_count, count);
    
    vector<PokerCard* >::iterator itr = card.begin();
    vector<PokerCard* > temp;
    while (itr!=card.end()) {
        PokerCard* _card = *itr;
        if(_card->getValue() == value){
            if(!isAll || _count == count){
                if(temp.size() < count){
                    temp.push_back(PokerCard::createPokerCard(_card->getNumber(), _card->getColor()));
                }else if (m_TempTipCard.size() == count){
                    m_TempTipCard.push_back(temp);
                    return;
                }
            }else{
                temp.push_back(PokerCard::createPokerCard(_card->getNumber(), _card->getColor()));
            }
        }
        
        itr++;
    }
    if(num>1 && temp.size()>count){
        a[0] = count;
        getCombo(temp, _count, count);
    } 
}

void CardAnalysis::getCombo(vector<PokerCard* > &card,int m,int k){
    int i,j;
    for (i=m;i>=k;i--)
    {
        a[k]=i;
        if (k>1)
        {
            getCombo(card,i-1,k-1);
        }
        else
        { 
            vector<PokerCard* > temp;
            for (j=a[0];j>0;j--)
            {
                CCLOG("a[%d] = %d",j,a[j]);
                if(a[j]-1<card.size()){
                    temp.push_back(PokerCard::createPokerCard(card[a[j]-1]->getNumber(), card[a[j]-1]->getColor()));
                }
            }
            if(temp.size()>0){
               m_TempTipCard.push_back(temp); 
            }
            
            CCLOG("*********************");
            
        }
    }
}

int CardAnalysis::getCountKind(int count, int needcount){
    if(count<needcount){
        return 0;
    }
    if(count == needcount){
        return 1;
    }
    vector<PokerCard* > card;
    a[0] = 1;
    getCombo(card, 4, 1);
    int num = 0;
    std::function<int(int)> fac = [&fac](int n) ->int{ return n == 1 ? 1 : n*fac(n - 1); } ;
    num = fac(count)/(fac(count-needcount)*fac(needcount));
    CCLOG("*******num = %d*********",num);
    return num;
}

#pragma mark 提取各种牌型的全部组合(包括拆牌的)

void CardAnalysis::getAllSingle(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards, vector<PokerCard *> origincard){
    
    getSameValueWithViceCards(AllTips, AllCards, origincard, 1);    
}

void CardAnalysis::getAllDoubles(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard){
    
    getSameValueWithViceCards(AllTips, AllCards, origincard, 2);
}

void CardAnalysis::getAllSanzhang(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard){
    
    getSameValueWithViceCards(AllTips, AllCards, origincard, 3);
}

void CardAnalysis::getAllSandaiyi(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard){
    vector<vector<PokerCard* > >  AllSanzhangTips;
    vector<vector<PokerCard* > > AllSanzhangCards;
    getAllSanzhang(AllSanzhangTips, AllSanzhangCards, origincard);
    vector<vector<PokerCard* > >  AllSingleTips;
    vector<vector<PokerCard* > > AllSingleCards;
    getAllSingle(AllSingleTips, AllSingleCards, origincard);
    for(int i=0;i<AllSanzhangTips.size();i++)
    {
        int value = AllSanzhangTips[i][0]->getValue();
        for(int j=0;j<AllSingleTips.size();j++){
            if(value != AllSingleTips[j][0]->getValue()){
                vector<PokerCard* > temp;
                temp.assign(AllSanzhangTips[i].begin(), AllSanzhangTips[i].end());
                temp.insert(temp.end(), AllSingleTips[j].begin(),AllSingleTips[j].end());
                AllTips.push_back(temp);
            }
        }
    }
    for(int i=0;i<AllSanzhangCards.size();i++)
    {
        int value = AllSanzhangCards[i][0]->getValue();
        for(int j=0;j<AllSingleCards.size();j++){
            if(value != AllSingleCards[j][0]->getValue()){
                vector<PokerCard* > temp;
                temp.assign(AllSanzhangCards[i].begin(), AllSanzhangCards[i].end());
                temp.insert(temp.end(), AllSingleCards[j].begin(),AllSingleCards[j].end());
                AllTips.push_back(temp);
            }
        }
    } 
}

void CardAnalysis::getAllSandaier(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard){
    
}

void CardAnalysis::getAllShunzi(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllLiandui(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllFeiji(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllFeijidaidan(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllFeijidaidui(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllZhadan(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count){
}

void CardAnalysis::getAllWangzha(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard){
}

void CardAnalysis::getSameValueWithViceCards(vector<vector<PokerCard *> > &AllTips, vector<vector<PokerCard *> > &AllCards, vector<PokerCard *> origincard,int count,bool withVice,int vicecount){
    MakeCard::getInstance()->sequenceCardsWithBigger(origincard);
    vector<PokerCard* >::iterator itr = origincard.begin();
    int value = 0;
    while (itr != origincard.end()) {
        PokerCard* card = *itr;
        if(GetSameValueCount(origincard, card->getValue()) == count && card->getValue()>_MinValue ){
            if(value != card->getValue()){
                GetSameValueCardsWithsCount(origincard, card->getValue(), count);
                AllTips.assign(m_TempTipCard.begin(), m_TempTipCard.end());
                GetSameValueCardsWithsCount(origincard, card->getValue(), count,true);
                AllCards.assign(m_TempTipCard.begin(), m_TempTipCard.end());
            }else{
                value = card->getValue();
            }
        }
        itr++;
    }
    while (itr != origincard.end()) {
        PokerCard* card = *itr;
        if(GetSameValueCount(origincard, card->getValue()) > count && card->getValue()>_MinValue ){
            if(value != card->getValue()){
                GetSameValueCardsWithsCount(origincard, card->getValue(), count);
                AllTips.assign(m_TempTipCard.begin(), m_TempTipCard.end());
                GetSameValueCardsWithsCount(origincard, card->getValue(), count,true);
                AllCards.assign(m_TempTipCard.begin(), m_TempTipCard.end());
            }else{
                value = card->getValue();
            }
        }
        itr++;
    }
}




