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

enum ScriptState
{
    NO_SCRIPT = 0,
    READ_SCRIPT = 1,
    READ_QUOTED_TEXT = 2,
};

void Scanner::readFile( const std::string& path )
{
    std::ifstream file( path );
    if ( !file )
        throw file_read_exception( "Error: Cannot open source file." );

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
                    if ( str == "script" && tokens->getToken( tokens->getSize() - 1 )->name != TokenName::OPEN_END_TAG )
                        scriptState = ScriptState::READ_SCRIPT;
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
