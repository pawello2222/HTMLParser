//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include "Scanner.h"

namespace scanner
{
    Scanner::Scanner()
    {
        tokens.clear();

        specialCharacters = "</> !=-\"";
    }

    Scanner::~Scanner()
    {
        tokens.clear();
    }

    void Scanner::readFile( const std::string& path )
    {
        std::ifstream file( path );
        if ( !file )
            throw exceptions::parser_exception( "Error: Cannot open source file." );

        char c;
        std::string str = "";

        ReadState state = ReadState::READ_TEXT;
        ScriptState scriptState = ScriptState::NO_SCRIPT;

        while ( !file.eof() )
        {
            file.get( c );
            if ( file.eof() )
                break;

            if ( state == ReadState::READ_TEXT )
            {
                if ( scriptState != ScriptState::NO_SCRIPT )
                {
                    if ( c == '\'' )
                    {
                        if ( scriptState == ScriptState::READ_SCRIPT )
                            scriptState = ScriptState::READ_QUOTED_TEXT;
                        else
                            scriptState = ScriptState::READ_SCRIPT;
                        str += c;
                        continue;
                    }


                    if ( !( c == '<' && scriptState != ScriptState::READ_QUOTED_TEXT ) )
                    {
                        str += c;
                        continue;
                    }

                    char tmp;
                    file.get( tmp );
                    if ( tmp != '/' )
                    {
                        str = str + c + tmp;
                        continue;
                    }
                    file.unget();
                    scriptState = ScriptState::NO_SCRIPT;
                }

                if ( c != '<' )
                {
                    str += c;
                    continue;
                }

                if ( str != "" )
                {
                    addToken( TokenId::PLAIN_TEXT, str );
                    str = "";
                }

                file.get( c );

                if ( c == '/' )
                {
                    addToken( TokenId::OPEN_END_TAG, "" );
                }
                else
                {
                    addToken( TokenId::OPEN_BEGIN_TAG, "" );
                    file.unget();
                }

                state = ReadState::READ_TAG;
            }
            else if ( state == ReadState::READ_COMMENT )
            {
                if ( c != '-' )
                {
                    str += c;
                    continue;
                }

                file.get( c );
                if ( c == '-' )
                {
                    file.get( c );
                    if ( c == '>' )
                    {
                        addToken( TokenId::ATTRIBUTE_NAME, str );
                        str = "";
                        addToken( TokenId::CLOSE_TAG, "" );
                        state = ReadState::READ_TEXT;
                    }
                    else
                        str += c;
                }
                else
                    str += c;
            }
            else if ( state != ReadState::READ_VALUE )
            {
                if ( specialCharacters.find( c ) == std::string::npos
                     || ( state == ReadState::READ_TAG_INSIDE && c == '-' ) )
                {
                    str += c;
                    continue;
                }

                if ( str != "" )
                {
                    if ( state == ReadState::READ_TAG )
                    {
                        if ( str == "script" && tokens.back().get()->getName() != TokenId::OPEN_END_TAG )
                            scriptState = ScriptState::READ_SCRIPT;
                        addToken( TokenId::TAG_ID, str );
                        state = ReadState::READ_TAG_INSIDE;
                    }
                    else
                        addToken( TokenId::ATTRIBUTE_NAME, str );
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
                            addToken( TokenId::TAG_ID, "COMMENT" );
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
                    addToken( TokenId::EQUAL_SIGN, "" );
                else if ( c == ' ' )
                {
                    do
                        file.get( c );
                    while ( !file.eof() && c == ' ' );
                    file.unget();

                    addToken( TokenId::WHITESPACE, "" );
                }
                else if ( c == '>' )
                {
                    addToken( TokenId::CLOSE_TAG, "" );
                    state = ReadState::READ_TEXT;
                }
                else if ( c == '/' )
                {
                    file.get( c );
                    if ( c == '>' )
                    {
                        addToken( TokenId::AUTO_CLOSE_TAG, "" );
                        state = ReadState::READ_TEXT;
                    }
                    else
                        file.unget();
                }
                else if ( c == '"' )
                {
                    addToken( TokenId::QUOTATION, "" );
                    state = ReadState::READ_VALUE;
                }
            }
            else
            {
                if ( c != '"' )
                {
                    str += c;
                    continue;
                }
                else
                {
                    addToken( TokenId::ATTRIBUTE_VALUE, str );
                    str = "";

                    addToken( TokenId::QUOTATION, "" );

                    state = ReadState::READ_TAG_INSIDE;
                }
            }
        }

        file.close();
    }

    void Scanner::addToken( TokenId key, std::string value )
    {
        tokens.push_back( std::shared_ptr< data_structures::Token >( new data_structures::Token( key, value ) ) );
    }

    Tokens& Scanner::getTokens()
    {
        return tokens;
    }
}