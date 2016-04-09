//
// Created by Pawel Wiszenko on 08.04.2016.
//

#include "Parser.h"
#include "../Exceptions/Exceptions.h"

Parser::Parser( OrderedDict* _tokens )
{
    this->tree = new Tree();
    this->tokens = _tokens;
    this->currNode = tree->root = new Node( Identifier::ROOT, "" );
    this->currIndex = 0;
}

void Parser::parse()
{
    if ( !parseDoctype() )
        throw parser_exception( "Error: Invalid DOCTYPE tag." );

    while ( currIndex < tokens->getSize() )
    {
        if ( !parseNode() )
        {
            std::stringstream msg;
            msg << "Error: Invalid tag at index " << currIndex << "\nIndex " << currIndex - 1 << ": Name: "
                << tokens->getToken( currIndex - 1 )->decription( tokens->getToken( currIndex - 1 )->name )
                << " Value: " << tokens->getToken( currIndex - 1 )->value << "\nIndex " << currIndex << ": Name: "
                << tokens->getToken( currIndex )->decription( tokens->getToken( currIndex )->name )
                << " Value: " << tokens->getToken( currIndex )->value << "\nIndex " << currIndex + 1 << ": Name: "
                << tokens->getToken( currIndex + 1 )->decription( tokens->getToken( currIndex + 1 )->name )
                << " Value: " << tokens->getToken( currIndex + 1 )->value;
            throw parser_exception( msg.str() );
        }
    }
}

bool Parser::parseDoctype()
{
    if ( readToken( currIndex, TokenName::OPEN_BEGIN_TAG ) )
    {
        if ( readToken( ++currIndex, TokenName::TAG_ID, "DOCTYPE" )
             && readToken( ++currIndex, TokenName::WHITESPACE )
             && readToken( ++currIndex, TokenName::ATTRIBUTE_NAME ) )
        {
            tree->doctype = tokens->getToken( currIndex )->value;

            if ( readToken( ++currIndex, TokenName::CLOSE_TAG ) )
            {
                ++currIndex;
                return true;
            }
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
            if ( tokens->getToken( currIndex )->value == "COMMENT"
                 && readToken( ++currIndex, TokenName::ATTRIBUTE_NAME ) )
            {
                currNode->nodes.push_back( new Node( Identifier::COMMENT, tokens->getToken( currIndex )->value ) );
                currNode->nodes.back()->parent = currNode;

                if ( readToken( ++currIndex, TokenName::CLOSE_TAG ) )
                {
                    ++currIndex;
                    return true;
                }
                else
                    return false;
            }

            currNode->nodes.push_back( new Node( Identifier::TAG, tokens->getToken( currIndex++ )->value ) );
            currNode->nodes.back()->parent = currNode;
            currNode = currNode->nodes.back();

            while ( readToken( currIndex, TokenName::WHITESPACE ) )
            {
                if ( !readToken( ++currIndex, TokenName::CLOSE_TAG )
                     && !readToken( currIndex, TokenName::AUTO_CLOSE_TAG ) )
                {
                    if ( !parseAttribute() )
                        return false;
                }
            }

            if ( readToken( currIndex, TokenName::CLOSE_TAG ) )
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
        }
    }
    else if ( readToken( currIndex, TokenName::OPEN_END_TAG ) )
    {
        if ( readToken( ++currIndex, TokenName::TAG_ID ) )
        {
            //todo: apparently wrong: ( <td> ... </th> )
            /*if ( tokens->getToken( currIndex )->value != currNode->name )
                return false;*/

            currNode = currNode->parent;

            if ( readToken( ++currIndex, TokenName::CLOSE_TAG ) )
            {
                ++currIndex;
                return true;
            }
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
    if ( readToken( currIndex, TokenName::ATTRIBUTE_NAME ) )
    {
        std::string tmp = tokens->getToken( currIndex )->value;

        if ( readToken( ++currIndex, TokenName::EQUAL_SIGN )
             && readToken( ++currIndex, TokenName::QUOTATION )
             && readToken( ++currIndex, TokenName::ATTRIBUTE_VALUE ) )
        {
            currNode->attributes.push_back( new Attribute( tmp, tokens->getToken( currIndex )->value ) );

            if ( readToken( ++currIndex, TokenName::QUOTATION ) )
            {
                ++currIndex;
                return true;
            }
        }
    }

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
