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
    
    bool CanMatchOthers(vector<PokerCard* > card,vector<PokerCard* > origincard);   //是否能跟其他牌组成一定牌型
    
    bool CanFixSingle(vector<PokerCard* > card);            //是否是单张
    
    bool CanFixDouble(vector<PokerCard* > card);           //是否是对子
    
    bool CanFixSanZhang(vector<PokerCard* > card);      //是否是三张
    
    bool CanFixSanDaiyi(vector<PokerCard* > card);        //是否是三带一
    
    bool CanFixSanDaier(vector<PokerCard* > card);          //是否是三带二
    
    bool CanFixShunzi(vector<PokerCard* > card,int count);//是否是顺子
    
    bool CanFixLiandui(vector<PokerCard* > card,int count);//是否是连对
    
    bool CanFixFeiji(vector<PokerCard* > card,int count);//是否是飞机

    bool CanFixFeijiDaidan(vector<PokerCard* > card,int count);//是否是飞机带单张

    bool CanFixFeijiDaidui(vector<PokerCard* > card,int count);//是否是飞机带对子
    
    bool CanFixZhadan(vector<PokerCard* > card,int count);//是否是炸弹
    
    bool CanFixWangzha(vector<PokerCard* > card);//是否是王炸
    
    int GetSameValueCount(vector<PokerCard* > card,int value);    //获取card中与value值相同的个数
    
    int GetDeffrientValueCount(vector<PokerCard* > card);   //获取card中有几种值
    
    
    /******************************提取各种牌型的全部组合(包括拆牌的)******************************/
    //Alltips——按提示时说提取的牌型，同值的只提取一次
    //AllCards——所有的可能，同值不同色的牌也算在内
    void getAllSingle(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard);
    
    void getAllDoubles(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard);
    
    void getAllSanzhang(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard);
    
    void getAllSandaiyi(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard);
    
    void getAllSandaier(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard);
    
    void getAllShunzi(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count);
    
    void getAllLiandui(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count);
    
    void getAllFeiji(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count);
    
    void getAllFeijidaidan(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count);
    
    void getAllFeijidaidui(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count);
    
    void getAllZhadan(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard,int count);
    
    void getAllWangzha(vector<vector<PokerCard* > >  &AllTips,vector<vector<PokerCard* > > &AllCards,vector<PokerCard* > origincard);
};

#endif /* CardAnalysis_hpp */
