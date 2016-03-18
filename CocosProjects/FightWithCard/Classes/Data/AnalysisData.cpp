//
//  AnalysisData.cpp
//  FightWithCard
//
//  Created by tianrunyan on 16/3/11.
//
//

#include "AnalysisData.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;
using namespace std;

AnalysisData::AnalysisData():
m_LordIndex(-1)
{
    log("----------------AnalysisData----------------");
    m_LeftData.clear();
    m_MyData.clear();
    m_RightData.clear();
}

AnalysisData::~AnalysisData(){
    
}

AnalysisData* AnalysisData::createData(){
    AnalysisData* pRest = new AnalysisData();
    if(pRest){
        pRest->autorelease();
        return pRest;
    }
    CC_SAFE_DELETE(pRest);
    return NULL;
}

bool AnalysisData::init(std::string filename){
    if(!FileUtils::getInstance()->isFileExist(filename)){
        CCLOG("Can not find the file");
        return false;
    }
    string filepath  = FileUtils::getInstance()->fullPathForFilename(filename);
    XMLDocument* pDoc = new XMLDocument();
    
    XMLError errorId = pDoc->LoadFile(filepath.c_str());
    log("filepath = %s",filepath.c_str());
    if(errorId != 0){
        CCLOG("xml格式错误");
        return false;
    }
    
    XMLElement* rootEle = pDoc->RootElement(); //读取根元素
    while (rootEle) {
        if(strcmp(rootEle->Name(), "CardInfo") == 0){
            //取地主编号
            const XMLAttribute* attribute = rootEle->FirstAttribute(); //读取根元素里的属性
            if(attribute != NULL){
                m_LordIndex = atoi(attribute->Value()) ;
                CCLOG("lordid = %d",m_LordIndex);
            }
        }
        
        const XMLElement* childEle = rootEle->FirstChildElement();
        
        while (childEle) {
            if(strcmp(childEle->Name(), "PlayerInfo") == 0){
                //取座位编号
                const XMLAttribute* attribute = childEle->FirstAttribute(); //读取PlayerInfo里的属性
                int seatid = -1;
                if(attribute != NULL && strcmp(attribute->Name(), "id") == 0){
                    seatid = atoi(attribute->Value()) ;
                    CCLOG("seatid = %d",seatid);
                }
                
                const XMLElement* cardEle = childEle->FirstChildElement();
                
                while (cardEle) {
                    if(strcmp(cardEle->Name(),"card") == 0){
                        const XMLAttribute* cardattribute = cardEle->FirstAttribute();
                        while (cardattribute) {
                            int number = -1;
                            int color = -1;
                            if(strcmp(cardattribute->Name(), "number") == 0){
                                number = atoi(cardattribute->Value());
                                CCLOG("number = %d",number);
                                if (strcmp(cardattribute->Next()->Name(), "color")==0){
                                    color = atoi(cardattribute->Next()->Value());
                                    CCLOG("color  = %d",color);
                                }
                            }
                            
                            if(number != -1 && color != -1 && seatid != -1){
                                if(seatid ==0){
                                    m_LeftData.push_back(make_pair(number, (PokerColor)color));
                                }else if (seatid == 1){
                                    m_MyData.push_back(make_pair(number,(PokerColor)color));
                                }else if (seatid == 2){
                                    m_RightData.push_back(make_pair(number,(PokerColor)color));
                                }
                            }
                            cardattribute = cardattribute->Next();
                        }
                    }
                    cardEle = cardEle->NextSiblingElement();
                }
            }
            childEle = childEle->NextSiblingElement();
        }
        rootEle = rootEle->NextSiblingElement();
    }
    return true;
}

void AnalysisData::getPlayInfo(int &lordIndex, std::vector<std::pair<int, PokerColor> > &left, std::vector<std::pair<int, PokerColor> > &my, std::vector<std::pair<int, PokerColor> > &right)
{
    lordIndex = m_LordIndex;
    left = m_LeftData;
    my = m_MyData;
    right = m_RightData;
}






