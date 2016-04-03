//
// Created by Pawel on 01.04.2016.
//

#include "Scanner.h"

Scanner::Scanner()
{
    tokens = new OrderedDict();
}

Scanner::~Scanner()
{
    delete tokens;
}

enum State
{
    TAG_BEGIN = 0,
    TAG_INSIDE = 1,
    PLAIN_TEXT = 2,
    DOCTYPE = 3,
    COMMENT = 4
};

void Scanner::readFile( const std::string& path )
{
    std::ifstream file( path );

    char c;
    std::string str = "";

    bool beginTag;

    State state = PLAIN_TEXT;

    while ( !file.eof() )
    {
        switch ( state )
        {
            case TAG_BEGIN:
                do
                    file.get( c );
                while ( !file.eof() && c == ' ' );

                if ( c == '!' )
                {
                    file.get( c );
                    if ( c == '-' )
                        state = COMMENT;
                    else
                        state = DOCTYPE;
                    break;
                }
                else if ( c == '/' )
                {
                    beginTag = false;
                    file.get( c );
                }
                else
                    beginTag = true;

                str = "";
                do
                {
                    str += c;
                    file.get( c );
                }
                while ( !file.eof() && c != '/' && c != '>' && c != ' ');

                addToken( beginTag ? "begin_tag" : "end_tag", str );

                state = TAG_INSIDE;
                break;

            case TAG_INSIDE:
                if ( c == ' ' )
                {
                    do
                        file.get( c );
                    while ( !file.eof() && c == ' ' );
                }

                if ( c == '/' )
                    file.get( c );

                if ( c == '>' )
                {
                     //addToken( "tag close", "" );
                    state = PLAIN_TEXT;
                    break;
                }

                str = "";
                while ( !file.eof() && c != '=' )
                {
                    str += c;
                    c = ' ';
                    file.get( c );
                }

                addToken( "identifier", str );
                addToken( "equals", "" );

                file.get( c );
                file.get( c );
                //str += c;

                str = "";
                do
                {
                    str += c;
                    file.get( c );

                }
                while ( !file.eof() && c != '"');

                file.get( c );

                addToken( "value", str );
                break;

            case PLAIN_TEXT:
                file.get( c );

                str = "";
                while ( !file.eof() && c != '<' )
                {
                    str += c;
                    c = ' ';
                    file.get( c );
                }

                if ( str != "" /*&& str != "\n"*/ )
                    addToken( "text", str );

                state = TAG_BEGIN;
                break;

            case DOCTYPE:
                while ( !file.eof() && c != ' ' )
                    file.get( c );

                while ( !file.eof() && c == ' ' )
                    file.get( c );

                str = "";
                while ( !file.eof() && c != '>' )
                {
                    str += c;
                    c = ' ';
                    file.get( c );
                }

                addToken( "DOCTYPE", str );
                state = PLAIN_TEXT;
                break;

            case COMMENT:
                file.get( c );
                file.get( c );

                if ( c == '>' )
                {
                    addToken( "comment", "" );
                    state = PLAIN_TEXT;
                    break;
                }

                str = "";
                while ( !file.eof() )
                {
                    str += c;
                    c = ' ';
                    file.get( c );

                    if ( c == '-' )
                    {
                        file.get( c );
                        if ( c == '-' )
                        {
                            file.get( c );
                            if ( c == '>' )
                            {
                                addToken( "comment", str );
                                state = PLAIN_TEXT;
                                break;
                            }
                            else
                                str += "--";
                        }
                    }
                }

                break;
        }
    }

    file.close();
}

void Scanner::addToken( std::string key, std::string value )
{
    tokens->insert( Token( key, value ) );
}

void Scanner::printTokens()
{
    tokens->print();
}

/*void Scanner::getTokenValue( std::string value )
{
    if ( tokens->getToken( value ).name == "" )
        return;

    std::cout << tokens->getToken( value ).value << std::endl;
}*/










