#include "lexer.h"

char travel_line_curr(t_parser* parser, bool proceed, bool current, bool upcome)
{
    if(!parser || !parser->begining || !*parser->begining)
        return '\0';
    if(proceed)
    {
        parser->current++;
        return parser->current[-1];
    }
    else if(current)
        return *parser->current;
    else if(upcome)
    {
        if(isEnd(parser))
            return ('\0');
        return parser->current[1];
    }
    return '\0';
    
}
char travel_line_beg(t_parser* parser, bool proceed, bool current, bool upcome)
{
    if(!parser || !parser->begining || !*parser->begining)
    return '\0';
    if(proceed)
    {
        parser->begining++;
        return parser->begining[-1];
    }
    else if(current)
        return *parser->begining;
    else if(upcome)
    {
        if(!*parser->begining){
            return ('\0');
        }
        return parser->begining[1];
    }
    return '\0';
}