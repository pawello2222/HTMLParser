//
// Created by Pawel Wiszenko on 08.04.2016.
//

#include "Parser.h"
#include "../Exceptions/Exceptions.h"

Parser::Parser( std::vector< Token* > _tokens )
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

    while ( currIndex < tokens.size() )
    {
        if ( !parseNode() )
        {
            std::stringstream msg;
            msg << "Error: Invalid tag at index " << currIndex << "\nIndex " << currIndex - 1 << ": Name: "
                << tokens.at( currIndex - 1 )->decription( tokens.at( currIndex - 1 )->name )
                << " Value: " << tokens.at( currIndex - 1 )->value << "\nIndex " << currIndex << ": Name: "
                << tokens.at( currIndex )->decription( tokens.at( currIndex )->name )
                << " Value: " << tokens.at( currIndex )->value << "\nIndex " << currIndex + 1 << ": Name: "
                << tokens.at( currIndex + 1 )->decription( tokens.at( currIndex + 1 )->name )
                << " Value: " << tokens.at( currIndex + 1 )->value;
            throw parser_exception( msg.str() );
        }
    }
}

bool Parser::parseDoctype()
{
    if ( readToken( currIndex, TokenName::PLAIN_TEXT ) )
        ++currIndex;

    if ( readToken( currIndex, TokenName::OPEN_BEGIN_TAG ) )
    {
        if ( readToken( ++currIndex, TokenName::TAG_ID, "DOCTYPE" )
             && readToken( ++currIndex, TokenName::WHITESPACE )
             && readToken( ++currIndex, TokenName::ATTRIBUTE_NAME ) )
        {
            tree->doctype = tokens.at( currIndex )->value;

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
            if ( tokens.at( currIndex )->value == "COMMENT"
                 && readToken( ++currIndex, TokenName::ATTRIBUTE_NAME ) )
            {
                currNode->nodes.push_back( new Node( Identifier::COMMENT, tokens.at( currIndex )->value ) );
                currNode->nodes.back()->parent = currNode;

                if ( readToken( ++currIndex, TokenName::CLOSE_TAG ) )
                {
                    ++currIndex;
                    return true;
                }
                else
                    return false;
            }

            currNode->nodes.push_back( new Node( Identifier::TAG, tokens.at( currIndex )->value ) );
            currNode->nodes.back()->parent = currNode;
            currNode = currNode->nodes.back();

            ++currIndex;
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
                if ( currNode->name == "link" || currNode->name == "meta" )
                    currNode = currNode->parent;

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
        currNode->nodes.push_back( new Node( Identifier::TEXT, tokens.at( currIndex++ )->value ) );
        currNode->nodes.back()->parent = currNode;
        return true;
    }

    return false;
}

bool Parser::parseAttribute()
{
    if ( readToken( currIndex, TokenName::ATTRIBUTE_NAME ) )
    {
        std::string tmp = tokens.at( currIndex )->value;

        if ( readToken( ++currIndex, TokenName::EQUAL_SIGN )
             && readToken( ++currIndex, TokenName::QUOTATION )
             && readToken( ++currIndex, TokenName::ATTRIBUTE_VALUE ) )
        {
            currNode->attributes.push_back( new Attribute( tmp, tokens.at( currIndex )->value ) );

            if ( readToken( ++currIndex, TokenName::QUOTATION ) )
            {
                ++currIndex;
                return true;
            }
        }
    }

    return false;
}

Tree* Parser::getTree()
{
    return tree;
}

bool Parser::readToken( unsigned long index, TokenName name )
{
    return tokens.at( index )->name == name;
}

bool Parser::readToken( unsigned long index, TokenName name, std::string value )
{
    return tokens.at( index )->name == name
         && tokens.at( index )->value == value;
}
