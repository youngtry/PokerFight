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
    InfoLayerTag,
    TableLayerTag,
    StoryLayerTag,
    MenuLayerTag,
    HandCardLayerTag,
}LayerTag;

typedef enum {
    GameNull=0,
    GameReady,         //准备状态
    GameDealCard,   //发牌
    GameCallScore,  //叫分
    GameGetLord,    //获得地主
    GameDouble,      //加倍
    GamePlay,           //打牌
    GameOver,          //结束
}GameState;

#define HeadNumber 5    //头像图片数目
#define CloclkTime  15      //倒计时


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
    void showStory();
    
    /*************信息层*************/
    void createInfoLayer();
    void showBaseInfo();            //显示基本信息
    void showLordCard();           //显示地主牌和动画
    
    
    /*************手牌层*************/
    void createHanderLayer();
    
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
    void CallScore(int score);
    void CallDouble();
    void GetLord();
    
    void OutTimehandle();
    void ComputerOperation();
    
    
    /*************理牌调整相关*************/
    void adjustCards();
    void showLeftCardNumber();
    
    /*************调整相关*************/
    void setOrder(std::vector<PokerCard* > &card);
    
     /*************牌桌相关*************/
    void createTableLayer();
    void showClock(int time,int seat);
    void hideClock();
     /*************AI相关*************/
    bool isDouble();
    int AutoCallScore();
    void AutoComputerPlay();
    
    /*************触摸相关*************/
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

    
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
    
    //牌桌层
    Layer* m_TableLayer;
    Sprite* m_Clock;
    Label* m_ClockNum;
    
    //特效层
    Layer* m_AnimLayer;
    
    //信息层
    Layer* m_InfoLayer;
    Sprite* m_TopInfoPanel;
    Label* m_Nickname;
    Label* m_Gold;
    Label* m_Time;
    Label* m_DiFen;
    Label* m_Beishu;
    std::vector<PokerCard* > m_TopLordCard; 
    
    //人物层
    Layer* m_PlayerLayer;
    Sprite* m_LeftPlayer;
    Sprite* m_MyPlayer;
    Sprite* m_RightPlayer;
    Label* m_LeftCardNumberLabel[3];            //剩余牌数label
    Sprite* m_PlayerSpeak[3];                            //玩家说的话
    
    //剧情层
    LayerColor* m_StoryLayer;
    Label* m_Story;
    
    /*****************数据相关*****************/
    Size m_winSize;                             //屏幕尺寸
    
    std::vector<PokerCard* > m_LeftCard;        //左家手牌
    std::vector<PokerCard* > m_MyCard;          //本家手牌
    std::vector<PokerCard* > m_RightCard;       //右家手牌
    std::vector<PokerCard* > m_LordCard;        //地主牌
    
    std::vector<std::string > m_StoryInfo;            //剧情信息
    
    int m_LordIndex;                            //地主编号
    
    int m_RoundIndex;                           //关卡编号
    
    int m_DealIndex;                            //发牌数目：理牌用
    
    
    int m_LeftCardNumber[3];                    //剩余牌数
    
    GameState m_GameState;              //游戏状态
    
    int m_CurrPlayer;                           //当前轮到谁操作
    
};

#endif /* GameLayer_hpp */
