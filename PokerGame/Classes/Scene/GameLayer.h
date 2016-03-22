//
//  GameLayer.hpp
//  FightWithCard
//
//  Created by tianrunyan on 16/3/16.
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include "cocos2d.h"
using namespace cocos2d;

typedef enum 
{
    BackeGroundTag=1,
    PlayerLayerTag,
    StoryLayerTag,
    MenuLayerTag,
    
    
}LayerTag;

typedef enum {
    GameNull=0,
    GameReady,         //准备状态
    GameDealCard,   //发牌
    GameCallScore,  //叫分
    GameDouble,      //加倍
    GameGetLord,    //抢地主
    GamePlay,           //打牌
    GameOver,          //结束
}GameState;

#define HeadNumber 5    //头像图片数目


class PokerCard;

class GameLayer : public Layer {
    
public:
    
    GameLayer();
    virtual ~GameLayer();
    
    virtual void onEnter();
    virtual void onExit();
    
    static Scene* createGameScene();
    
    virtual bool init();
    
    /*************背景层*************/
    void createBackground();
    void changeBackground();
    
    /*************人物层*************/
    void createPlayersLayer();
    
    
    /*************情节层*************/
    void createStoryLayer();
    void showStoryWithStringLength(int length);
    
    /*************菜单层*************/
    void createMenuLayer();             //创建菜单层内容
    void removeMenuLayer();             //删除菜单层
    void showMenuLayer();               //显示菜单层
    void hideMenuLayer();               //隐藏菜单层
    
    void showPlayMenu(bool show);       //根据show值选择显示或者隐藏大牌菜单
    void showCallScoreMenu(bool show);  //根据show值选择显示或者隐藏叫分菜单
    void showDoubleMenu(bool show);     //根据show值选择显示或者隐藏加倍菜单
    void showAutoPlayMenu(bool show);   //根据show值选择显示或者隐藏托管按钮
    
    void PlayCallBack(int tag);         //打牌回调
    void ScroeCallBack(int tag);        //叫分回调
    void DoubleCallBack(int tag);       //加倍回调
    void AutoPlayCallBack();            //托管回调
    
    
    /*************流程相关*************/
    void changeToGameState(GameState state);    //切换流程
    void DealCards();       //发牌
    
    
    CREATE_FUNC(GameLayer);
    
private:
    
    //背景层
    Layer* m_BackgroundLayer;
    Sprite* m_Background;   //背景图
    std::string m_BackgroundName; //背景图名字
    
    //菜单层
    Layer* m_MenuLayer;
    Menu* m_CallScoreMenu;  //叫分菜单
    Menu* m_DoubleMenu;      //加倍菜单
    Menu* m_PlayMenu;          //打牌菜单
    Menu* m_AutoPlayMenu;  //托管菜单
    
    //手牌层
    Layer* m_HandCardLayer;
    
    //出牌层
    Layer* m_OutCardLayer;
    
    //特效层
    Layer* m_AnimLayer;
    
    //信息层
    Layer* m_InfoLayer;
    Sprite* m_TopInfoPanel;
    Label* m_Time;
    
    //人物层
    Layer* m_PlayerLayer;
    Sprite* m_LeftPlayer;
    Sprite* m_MyPlayer;
    Sprite* m_RightPlayer;
    
    //剧情层
    Layer* m_StoryLayer;
    Label* m_Story;
    
    /*****************数据相关*****************/
    Size m_winSize;                             //屏幕尺寸
    
    std::vector<PokerCard* > m_LeftCard;        //左家手牌
    std::vector<PokerCard* > m_MyCard;          //本家手牌
    std::vector<PokerCard* > m_RightCard;       //右家手牌
    std::vector<PokerCard* > m_LordCard;        //地主牌
    
    int m_LordIndex;                            //地主编号
    
    int m_RoundIndex;                           //关卡编号
    
};

#endif /* GameLayer_hpp */
