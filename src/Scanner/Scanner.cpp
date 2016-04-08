//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include "Scanner.h"

Scanner::Scanner()
{
    tokens = new OrderedDict();

    specialCharacters = "</> !=-\"";
}

Scanner::~Scanner()
{
    delete tokens;
}

enum ReadState
{
    READ_TAG = 0,
    READ_TAG_INSIDE = 1,
    READ_VALUE = 2,
    READ_TEXT = 3,
    READ_COMMENT = 4
};

void Scanner::readFile( const std::string& path )
{
    std::ifstream file( path );

    char c;
    std::string str = "";

    ReadState state = ReadState::READ_TEXT;

    while ( !file.eof() )
    {
        file.get( c );
        if ( file.eof() )
            break;

        if ( state == ReadState::READ_TEXT )
        {
            if ( c != '<' )
            {
                str += c;
                continue;
            }
            else
            {
                if ( str != "" )
                {
                    addToken( TokenName::PLAIN_TEXT, str );
                    str = "";
                }

                file.get( c );

                if ( c == '/' )
                {
                    addToken( TokenName::OPEN_END_TAG, "" );
                }
                else
                {
                    addToken( TokenName::OPEN_BEGIN_TAG, "" );
                    file.unget();
                }

                state = ReadState::READ_TAG;
            }
        }
        else if ( state == ReadState::READ_COMMENT )
        {
            if ( c != '-' )
            {
                str += c;
                continue;
            }
            else
            {
                file.get( c );
                if ( c == '-' )
                {
                    file.get( c );
                    if ( c == '>' )
                    {
                        addToken( TokenName::ATTRIBUTE_NAME, str );
                        str = "";
                        addToken( TokenName::CLOSE_TAG, "" );
                        state = ReadState::READ_TEXT;
                    }
                    else
                        str += c;
                }
                else
                    str += c;
            }
        }
        else if ( state != ReadState::READ_VALUE )
        {
            if ( specialCharacters.find( c ) == std::string::npos )
            {
                str += c;
                continue;
            }
            else
            {
                if ( str != "" )
                {
                    if ( state == ReadState::READ_TAG )
                    {
                        addToken( TokenName::TAG_ID, str );
                        state = ReadState::READ_TAG_INSIDE;
                    }
                    else
                        addToken( TokenName::ATTRIBUTE_NAME, str );
                    str = "";
                }

                if ( c == '!' )
                {
                    file.get( c );
                    if ( c == '-' )
                    {
                        file.get( c );
                        if ( c == '-' )
                        {
                            addToken( TokenName::TAG_ID, "COMMENT" );
                            state = ReadState::READ_COMMENT;
                            continue;
                        }
                        else
                            file.unget();
                    }
                    else
                        file.unget();
                }
                else if ( c == '=' )
                    addToken( TokenName::EQUAL_SIGN, "" );
                else if ( c == ' ' )
                {
                    do
                        file.get( c );
                    while ( !file.eof() && c == ' ' );
                    file.unget();

                    addToken( TokenName::WHITESPACE, "" );
                }
                else if ( c == '>' )
                {
                    addToken( TokenName::CLOSE_TAG, "" );
                    state = ReadState::READ_TEXT;
                }
                else if ( c == '/' )
                {
                    file.get( c );
                    if ( c == '>' )
                    {
                        addToken( TokenName::AUTO_CLOSE_TAG, "" );
                        state = ReadState::READ_TEXT;
                    }
                    else
                        file.unget();
                }
                else if ( c == '"' )
                {
                    addToken( TokenName::QUOTATION, "" );
                    state = ReadState::READ_VALUE;
                }
            }
        }
        else //if ( state == ReadState::READ_VALUE )
        {
            if ( c != '"' )
            {
                str += c;
                continue;
            }
            else
            {
                addToken( TokenName::ATTRIBUTE_VALUE, str );
                str = "";

                addToken( TokenName::QUOTATION, "" );

                state = ReadState::READ_TAG_INSIDE;
            }
        }
    }

    file.close();
}

void Scanner::addToken( TokenName key, std::string value )
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

OrderedDict* Scanner::getTokens()
{
    return tokens;
}
