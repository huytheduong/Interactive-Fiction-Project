#include "storytokenizer.h"
StoryTokenizer::StoryTokenizer(string line)
{
    int index = line.find("<tw-passagedata");
    store = line.substr(index);

}
bool StoryTokenizer::hasNextPassage()
{
    string header="</tw-passagedata>";
    if(store.find(header)!=::string::npos)
    {
        return true;
    }
    else 
    {
        return false;
    }
}
PassageToken StoryTokenizer::nextPassage()
{
    int endOfpassage = store.find("</tw-passagedata>");
    string temp = store.substr(0,endOfpassage);

    string temp2 = store.substr(endOfpassage+16);
    store = temp2;

    PassageToken ss(temp);
    return ss;
}
PassageToken::PassageToken(string line)
{
    int index_name = line.find("name");
    int index_tag = line.find("tags=");
    int first_text = line.find("\">");
    name = line.substr(index_name+6,index_tag-index_name-8);
    text = line.substr(first_text+2);
}
PassageTokenizer::PassageTokenizer(string str)
{
    text = str; // store the text
    partposition  = 0;
}
bool PassageTokenizer::hasNextPart()
{
    return (partposition != string::npos);//find length
}
PartToken PassageTokenizer::nextPart()
{
    string part;
    char first = text.at(partposition); // first letter as identifier
    int position2 ;
    if( partposition != string::npos)
    {
        if ( first == '(')
        {
            position2 = text.find(')',partposition);
            part = text.substr(partposition, position2 - partposition + 1);

        }
        else if( first == '[')
        {
            if ( text.at(partposition + 1) == '[')
            {
                position2 = (text.find(']',partposition ))+ 1;
                part = text.substr(partposition, position2 - partposition + 1);
            }
            
            else
            {
                int temp = partposition; // holds position for [ between []
                position2 = text.find(']',partposition);

                while( temp != string::npos && position2 != (text.length() - 1))
                {
                    temp = text.find('[', temp  + 1);

                    if ( temp == -1 || temp < partposition)
                        break;
                    if ( temp != -1 && temp < position2)
                    {
                        position2 =  text.find(']', position2  + 1);
                    }

                }
                part = text.substr(partposition, position2 - partposition + 1 );
            }
        }
        else
        {
            int pos1 = text.find('(',partposition);
            int pos2 = text.find('[', partposition);
            if ( (pos1 < pos2) && (pos1 > 0) && (pos2 > 0) )
                position2 = pos1 -1;
            else
                position2 = pos2-1 ;
            part = text.substr(partposition, position2 - partposition  );

        }
    }
    partposition = position2 + 1;//update position
    if( partposition == text.length())
        partposition = -1;
    PartToken ptk(part);

    return ptk;

}

PartToken::PartToken(string str)
{
    part = str;
}
int PartToken::getType()
{
    int val;
    if ( part.at(0) == '('){//look for command
        int pos2 = part.find(':');
        string tp = part.substr(1, pos2-1);

        if( tp == "set")
            return SET;
        else if ( tp == "if")
            return IF;
        else if ( tp == "else")
            return ELSE;
        else if ( tp =="go-to")
            return GOTO;
        else if ( tp =="else-if")
            return ELSEIF;
    }
    // look for link
    else if ( part.at(0) == '[' && part.at(1) == '[')
        return LINK;
    else if ( part.at(0) == '[' && part.at(1) != '[')
        return BLOCK;
    else
        return TEXT;

return val;   
}
string PartToken::getText()
{
    return part;
}
