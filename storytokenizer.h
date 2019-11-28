#ifndef ___STORYTOKENIZER_H
#define ___STORYTOKENIZER_H 
enum{LINK,SET,GOTO,IF,ELSEIF,ELSE,BLOCK,TEXT};
#include <iostream>
#include <string>
using namespace std;

class PartToken
{
    public:
    string part;
    PartToken( string p);
    int getType();
    string getText();
};
class PassageTokenizer
{
public:
    string text;
    int partposition;
    PassageTokenizer(string str);
    bool hasNextPart();
    PartToken nextPart();
};
class PassageToken{
private:
    string name;
    string text;
public:
    PassageToken();
    PassageToken(string);
    string getName(){ return name;}
    string getText(){ return text;}
};
class StoryTokenizer{
public:
    string temp;
    string store;
    StoryTokenizer(string);
    bool hasNextPassage();
    PassageToken nextPassage();
};


#endif