//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include "Scanner.h"

namespace scanner
{
    Scanner::Scanner()
    {
        //tokens.clear();
    }

    Scanner::~Scanner()
    {
        //tokens.clear();
    }

    void Scanner::readFile( const std::string& path )
    {
        std::ifstream file( path );
        if ( !file )
            throw exceptions::parser_exception( "Error: Cannot open source file." );

        char c;

        ReadState state = ReadState::TEXT;

        while ( !file.eof() )
        {
            file.get( c );
            if ( file.eof() )
                break;

            switch ( state )
            {
                case TAG:
                    switch ( c )
                    {
                        case '<':
                            addToken( TokenClass::OPEN_BEGIN_TAG, "" );
                            break;

                        case '/':
//                            if ( outputStr != "" )
//                                addToken( TokenClass::IDENTIFIER, outputStr );
                            if ( tokens.back()->getClass() == TokenClass::OPEN_BEGIN_TAG )
                                tokens.back()->setClass( TokenClass::OPEN_END_TAG );
                            else
                            {
                                file.get( c );
                                if ( c == '>' )
                                {
                                    state = ReadState::TEXT;
                                    addToken( TokenClass::AUTO_CLOSE_TAG, "" );
                                    break;
                                }
                                file.unget();
                                outputStr += '/';
                            }
                            break;

                        case '>':
                            if ( outputStr != "" )
                                addToken( TokenClass::IDENTIFIER, outputStr );
                            addToken( TokenClass::CLOSE_TAG, "" );
                            state = ReadState::TEXT;
                            break;

                        case '!':
                            addToken( TokenClass::EXCLAMATION_MARK, "" );
                            break;

                        case '-':
                            if ( getLastTokenClass( 0 ) == TokenClass::EXCLAMATION_MARK
                                 && getLastTokenClass( 1 ) == TokenClass::OPEN_BEGIN_TAG )
                            {
                                file.get( c );
                                if ( c == '-' )
                                {
                                    state = ReadState::COMMENT;
                                    addToken( TokenClass::COMMENT_BEGIN, "" );
                                    break;
                                }
                                file.unget();
                            }
                            outputStr += '-';
                            break;

                        case '=':
                            if ( outputStr != "" )
                                addToken( TokenClass::IDENTIFIER, outputStr );
                            addToken( TokenClass::ASSIGNMENT, "" );
                            break;

                        case '\"':
                            addToken( TokenClass::QUOTATION_MARK, "" );
                            file.get( c );
                            while ( c != '\"' && !file.eof() )
                            {
                                outputStr += c;
                                file.get( c );
                            }
                            addToken( TokenClass::TEXT, outputStr );
                            addToken( TokenClass::QUOTATION_MARK, "" );

                        case ' ':
                            if ( outputStr != "" )
                                addToken( TokenClass::IDENTIFIER, outputStr );
                            file.get( c );
                            while ( c == ' ' && !file.eof() )
                                file.get( c );
                            file.unget();
                            addToken( TokenClass::WHITESPACE, "" );
                            break;

                        default:
                            outputStr += c;
                            break;

                    }
                    break;

                case TEXT:
                    if ( c == '<' )
                    {
                        file.get( c );
                        if ( c == '/' || c == '!' || ( c != ' ' && c != '=' ) )
                        {
                            addToken( TokenClass::TEXT, outputStr );
                            file.unget();
                            file.unget();
                            state = ReadState::TAG;
                            break;
                        }
                        file.unget();
                    }
                    if ( c == '\'' )
                        state = ReadState::TEXT_QUOTED;
                    outputStr += c;
                    break;

                case TEXT_QUOTED:
                    if ( c == '\'' )
                        state = ReadState::TEXT;
                    outputStr += c;
                    break;

                case COMMENT:
                    if ( c == '-' )
                    {
                        file.get( c );
                        if ( c == '-' )
                        {
                            file.get( c );
                            if ( c == '>' )
                            {
                                addToken( TokenClass::TEXT, outputStr );
                                addToken( TokenClass::COMMENT_END, "" );
                                addToken( TokenClass::CLOSE_TAG, "" );
                                state = ReadState::TEXT;
                                break;
                            }
                            file.unget();
                        }
                        file.unget();
                    }
                    outputStr += c;
                    break;
            }
        }
    }



    void Scanner::addToken( TokenClass key, std::string value )
    {
        tokens.push_back( new data_structures::Token( key, value ) );
        outputStr = "";
    }

    TokenClass Scanner::getLastTokenClass( int index )
    {
        if ( tokens.size() - index <= 0 )
            return TokenClass::UNKNOWN;

        return tokens.at( tokens.size() - 1 - index )->getClass();
    }

    Tokens& Scanner::getTokens()
    {
        return tokens;
    }
}