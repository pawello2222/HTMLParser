//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include "Scanner.h"

namespace scanner
{
    Scanner::Scanner( const std::string& path )
    {
        file.open( path );

        if ( !file )
            throw exceptions::custom_exception( "Error: Cannot open source file." );

        state = ReadState::TAG;
        currLine = 1;
        scriptMode = false;
        c = '\0';
    }

    Scanner::~Scanner()
    {
        if ( file )
            file.close();
    }

    TokenPtr Scanner::getNextToken()
    {
        if ( !queue.size() )
            parseFile();

        auto tmp = queue.front();
        queue.pop();
        return tmp;
    }

    void Scanner::parseFile()
    {
        if ( c == '\n' )
            currLine++;

        while ( !file.eof() )
        {
            file.get( c );
            if ( file.eof() )
            {
                addToken( TokenClass::END_OF_FILE );
                break;
            };

            switch ( state )
            {
                case TAG:
                    switch ( c )
                    {
                        case '<':
                            file.get( c );
                            if ( c == '!' )
                            {
                                file.get( c );
                                if ( c == '-' )
                                {
                                    file.get( c );
                                    if ( c == '-' )
                                    {
                                        state = ReadState::COMMENT;
                                        break;
                                    }
                                    file.unget();
                                }
                                file.unget();
                            }
                            else if ( c == '/' )
                            {
                                addToken( TokenClass::OPEN_END_TAG );
                                return;
                            }
                            file.unget();
                            addToken( TokenClass::OPEN_BEGIN_TAG );
                            return;

                        case '/':
                            if ( outputStr != "" )
                                addToken( TokenClass::IDENTIFIER, outputStr );
                            file.get( c );
                            if ( c == '>' )
                            {
                                state = ReadState::TEXT;
                                addToken( TokenClass::AUTO_CLOSE_TAG );
                                return;
                            }
                            file.unget();
                            outputStr += '/';
                            break;

                        case '>':
                            if ( outputStr != "" )
                            {
                                if ( outputStr == "script" && !scriptMode )
                                    scriptMode = true;
                                else if ( outputStr == "script" && scriptMode )
                                    scriptMode = false;
                                addToken( TokenClass::IDENTIFIER, outputStr );
                            }
                            addToken( TokenClass::CLOSE_TAG );
                            state = ReadState::TEXT;
                            return;

                        case '!':
                            addToken( TokenClass::EXCLAMATION_MARK );
                            return;

                        case '=':
                            if ( outputStr != "" )
                                addToken( TokenClass::IDENTIFIER, outputStr );
                            addToken( TokenClass::ASSIGNMENT );
                            return;

                        case '\"':
                        case '\'':
                            addToken( TokenClass::QUOTATION_MARK );
                            file.get( c );
                            while ( c != '\"' && c != '\'' && !file.eof() )
                            {
                                outputStr += c;
                                file.get( c );
                                if ( c == '\n' )
                                    currLine++;
                            }
                            addToken( TokenClass::TEXT, outputStr );
                            addToken( TokenClass::QUOTATION_MARK );
                            return;

                        case ' ':
                            if ( outputStr != "" )
                            {
                                if ( outputStr == "script" && !scriptMode )
                                    scriptMode = true;
                                else if ( outputStr == "script" && scriptMode )
                                    scriptMode = false;
                                addToken( TokenClass::IDENTIFIER, outputStr );
                            }
                            file.get( c );
                            while ( c == ' ' && !file.eof() )
                                file.get( c );
                            file.unget();
                            break;

                        default:
                            outputStr += c;
                            break;

                    }
                    break;

                case TEXT:
                    if ( c == '<' )
                    {
                        char e;
                        file.get( e );
                        if ( e == '/' || e == '!' || ( e != ' ' && e != '=' ) )
                        {
                            addToken( TokenClass::TEXT, outputStr );
                            file.unget();
                            file.unget();
                            state = ReadState::TAG;
                            return;
                        }
                        file.unget();
                    }
                    if ( c == '\'' && scriptMode )
                        state = ReadState::TEXT_QUOTED;
                    if ( c == '\"' && scriptMode )
                        state = ReadState::TEXT_DOUBLE_QUOTED;
                    if ( c == '\n' )
                        currLine++;
                    outputStr += c;
                    break;

                case TEXT_QUOTED:
                    if ( c == '\'' )
                        state = ReadState::TEXT;
                    if ( c == '\n' )
                        currLine++;
                    outputStr += c;
                    break;

                case TEXT_DOUBLE_QUOTED:
                    if ( c == '\"' )
                        state = ReadState::TEXT;
                    if ( c == '\n' )
                        currLine++;
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
                                state = ReadState::TEXT;
                                break;
                            }
                            file.unget();
                        }
                        file.unget();
                    }
                    if ( c == '\n' )
                        currLine++;
                    break;
            }
        }
    }

    TokenPtr Scanner::addToken( TokenClass key, std::string value )
    {
        TokenPtr token = std::shared_ptr< data_structures::Token >( new data_structures::Token( key, value ) );
        outputStr = "";
        if ( queue.size() >= MAX_QUEUE_SIZE )
            queue.pop();
        queue.push( token );
        return token;
    }

    int Scanner::getCurrLine() const
    {
        return currLine;
    }
}