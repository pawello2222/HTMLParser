//
// Created by Pawel Wiszenko on 08.04.2016.
//

#include "Parser.h"
#include "../Exceptions/ParserExceptions.h"

Parser::Parser( OrderedDict* _tokens )
{
    this->tree = new Tree();
    this->tokens = _tokens;
    this->currNode = tree->root = new Node( Identifier::ROOT, "" );
    this->currIndex = 0;
}

void Parser::parse()
{
    parseDoctype();
    parseNode();
    parseNode();

    /*if ( parseDoctype() )
    {

    }
    else
    {
        throw new exception::parser::parser_exception();
    }*/
}

bool Parser::parseDoctype()
{
    if ( readToken( currIndex, TokenName::OPEN_BEGIN_TAG ) )
    {
        if ( readToken( ++currIndex, TokenName::TAG_ID, "DOCTYPE" )
             && readToken( ++currIndex, TokenName::WHITESPACE )
             && readToken( ++currIndex, TokenName::ATTRIBUTE_NAME ) )
        {
            tree->doctype = tokens->getToken( currIndex++ )->value;

            if ( readToken( ++currIndex, TokenName::CLOSE_TAG ) )
                return true;
        }
    }

    return false;
}

bool Parser::parseNode()
{
    if ( readToken( currIndex, TokenName::OPEN_BEGIN_TAG ) )
    {
        if ( readToken( ++currIndex, TokenName::TAG_ID ) )
        {
            currNode->nodes.push_back( new Node( Identifier::TAG, tokens->getToken( currIndex )->value ) );
            currNode->parent = currNode;
            currNode = currNode->nodes.back();

            if ( readToken( ++currIndex, TokenName::CLOSE_TAG ) )
            {
                ++currIndex;
                return true;
            }
            else if ( readToken( currIndex, TokenName::AUTO_CLOSE_TAG ) )
            {
                currNode = currNode->parent;
                ++currIndex;
                return true;
            }
            else
            {
                parseAttribute();
            }
        }
    }
    else if ( readToken( currIndex, TokenName::CLOSE_TAG ) )
    {
        if ( readToken( ++currIndex, TokenName::TAG_ID ) )
        {
            if ( tokens->getToken( currIndex )->value != currNode->name )
                return false;

            currNode = currNode->parent;
            return true;
        }
    }
    else if ( readToken( currIndex, TokenName::PLAIN_TEXT ) )
    {
        currNode->nodes.push_back( new Node( Identifier::TEXT, tokens->getToken( currIndex++ )->value ) );
        return true;
    }

    return false;
}

bool Parser::parseAttribute()
{

    return false;
}

bool Parser::readToken( int index, TokenName name )
{
    return tokens->getToken( index )->name == name;
}

bool Parser::readToken( int index, TokenName name, std::string value )
{
    return tokens->getToken( index )->name == name
         && tokens->getToken( index )->value == value;
}
