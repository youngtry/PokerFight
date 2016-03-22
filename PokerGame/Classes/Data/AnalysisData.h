//
//  AnalysisData.hpp
//  FightWithCard
//
//  Created by tianrunyan on 16/3/11.
//
//

#ifndef AnalysisData_hpp
#define AnalysisData_hpp

#include "cocos2d.h"
#include "PokerCard.h"
using namespace cocos2d;

class AnalysisData : public Ref{
    
public:
    AnalysisData();
    ~AnalysisData();
    
    static AnalysisData* createData();
    
    bool init(std::string filename);
    
    void getPlayInfo(int &lordIndex, std::vector<std::pair<int, PokerColor> > &left,std::vector<std::pair<int, PokerColor> > &my,std::vector<std::pair<int, PokerColor> > &right);
    
private:
    std::vector<std::pair<int, PokerColor> >  m_LeftData;
    std::vector<std::pair<int, PokerColor>>  m_MyData;
    std::vector<std::pair<int, PokerColor>>  m_RightData;
    
    int m_LordIndex;
    
};

#endif /* AnalysisData_hpp */
