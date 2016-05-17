//
//  CardAnalysis.hpp
//  PokerGame
//
//  Created by tianrunyan on 16/5/17.
//
//

#ifndef CardAnalysis_hpp
#define CardAnalysis_hpp

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class PokerCard;

typedef enum {
    TYPE_NULL=-1,
    TYPE_SINGLE = 0,
    TYPE_DOUBLE,
    TYPE_SANZHANG,
    TYPE_SANDAIYI,
    TYPE_SANDAIER,
    TYPE_SHUNZI,
    TYPE_LIANDUI,
    TYPE_FEIJI,
    TYPE_FEIJIDAIDAN,
    TYPE_FEIJIDAIDUI,
    TYPE_ZHADAN,
    TYPE_WANGZHA,
}CardType;

class CardAnalysis : Node {
    
public:
    CardAnalysis();
    ~CardAnalysis();
    
    static CardAnalysis* CreateAnalysis();
    
    bool CanMatchOthers(vector<PokerCard* > card,vector<PokerCard* > origincard);
    
    bool CanFixSingle(vector<PokerCard* > card,vector<PokerCard* > origincard);
    
    bool CanFixDouble(vector<PokerCard* > card,vector<PokerCard* > origincard);
    
    bool CanFixSanZhang(vector<PokerCard* > card,vector<PokerCard* > origincard);
    
    bool CanFixSanDaiyi(vector<PokerCard* > card,vector<PokerCard* > origincard);
    
    bool CanFixSanDaier(vector<PokerCard* > card,vector<PokerCard* > origincard);
    
    bool CanFixShunzi(vector<PokerCard* > card,vector<PokerCard* > origincard,int count);
    
    bool CanFixLiandui(vector<PokerCard* > card,vector<PokerCard* > origincard,int count);
    
    bool CanFixFeiji(vector<PokerCard* > card,vector<PokerCard* > origincard,int count);

    bool CanFixFeijiDaidan(vector<PokerCard* > card,vector<PokerCard* > origincard,int count);

    bool CanFixFeijiDaidui(vector<PokerCard* > card,vector<PokerCard* > origincard,int count);
    
    bool CanFixZhadan(vector<PokerCard* > card,vector<PokerCard* > origincard,int count);
    
    bool CanFixWangzha(vector<PokerCard* > card,vector<PokerCard* > origincard);
    
    int GetSameValueCount(vector<PokerCard* > card,int value);    //获取card中与value值相同的个数
    
    int GetDeffrientValueCount(vector<PokerCard* > card);   //获取card中有几种值
    
};

#endif /* CardAnalysis_hpp */
