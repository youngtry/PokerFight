//
//  tools.cpp
//  FightWithCard
//
//  Created by tianrunyan on 16/3/18.
//
//

#include "tools.h"

string getString(string key){
    string a = "";
//    NSString* text = [[NSBundle mainBundle] localizedStringForKey:[NSString stringWithUTF8String:key.c_str()]  value:@"" table:@"ASLocalized"];
    NSString* text =NSLocalizedString([NSString stringWithUTF8String:key.c_str()], nil);
    
    a = [text UTF8String];
    return a;
}

string getCurrentLanguage()
{
    NSArray *languages = [NSLocale preferredLanguages];
    NSString *currentLanguage = [languages objectAtIndex:0];
    log("%s" , [currentLanguage UTF8String]);
    return [currentLanguage UTF8String];
}
