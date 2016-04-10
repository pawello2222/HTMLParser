//
// Created by Pawel Wiszenko on 08.04.2016.
//

#include "Parser.h"

namespace parser
{
    Parser::Parser( Tokens& _tokens ) : tokens( _tokens )
    {
        this->tree.setRoot( std::shared_ptr< HTMLNode >( new HTMLNode( Id::ROOT, "" ) ) );
        this->currNode = tree.getRoot();
        this->currIndex = 0;
    }

    void Parser::parse()
    {
        if ( !parseDoctype() )
            throw exceptions::parser_exception( "Error: Invalid DOCTYPE tag." );

        while ( currIndex < tokens.size() )
        {
            if ( !parseNode() )
            {
                std::stringstream msg;
                msg << "Error: Invalid tag at index " << currIndex << "\nIndex " << currIndex - 1 << ": Name: "
                << tokens.at( currIndex - 1 ).get()->description( tokens.at( currIndex - 1 ).get()->getName() )
                << " Value: " << tokens.at( currIndex - 1 ).get()->getValue() << "\nIndex " << currIndex << ": Name: "
                << tokens.at( currIndex ).get()->description( tokens.at( currIndex ).get()->getName() )
                << " Value: " << tokens.at( currIndex ).get()->getValue() << "\nIndex " << currIndex + 1 << ": Name: "
                << tokens.at( currIndex + 1 ).get()->description( tokens.at( currIndex + 1 ).get()->getName() )
                << " Value: " << tokens.at( currIndex + 1 ).get()->getValue();
                throw exceptions::parser_exception( msg.str() );
            }
        }
    }

    bool Parser::parseDoctype()
    {
        if ( readToken( currIndex, TokenId::PLAIN_TEXT ) )
            ++currIndex;

        if ( readToken( currIndex, TokenId::OPEN_BEGIN_TAG ) )
        {
            if ( readToken( ++currIndex, TokenId::TAG_ID, "DOCTYPE" )
                 && readToken( ++currIndex, TokenId::WHITESPACE )
                 && readToken( ++currIndex, TokenId::ATTRIBUTE_NAME ) )
            {
                tree.setDoctype( tokens.at( currIndex ).get()->getValue() );

                if ( readToken( ++currIndex, TokenId::CLOSE_TAG ) )
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
        if ( readToken( currIndex, TokenId::OPEN_BEGIN_TAG ) )
        {
            if ( readToken( ++currIndex, TokenId::TAG_ID ) )
            {
                if ( tokens.at( currIndex ).get()->getValue() == "COMMENT"
                     && readToken( ++currIndex, TokenId::ATTRIBUTE_NAME ) )
                {
                    currNode->getNodes().push_back( std::shared_ptr< HTMLNode >( new HTMLNode( Id::COMMENT, tokens.at( currIndex ).get()->getValue() ) ) );
                    currNode->getNodes().back().get()->setParent( currNode );

                    if ( readToken( ++currIndex, TokenId::CLOSE_TAG ) )
                    {
                        ++currIndex;
                        return true;
                    }
                    else
                        return false;
                }

                currNode->getNodes().push_back( std::shared_ptr< HTMLNode >( new HTMLNode( Id::TAG, tokens.at( currIndex ).get()->getValue() ) ) );
                currNode->getNodes().back().get()->setParent( currNode );
                currNode = currNode->getNodes().back();

                ++currIndex;
                while ( readToken( currIndex, TokenId::WHITESPACE ) )
                {
                    if ( !readToken( ++currIndex, TokenId::CLOSE_TAG )
                         && !readToken( currIndex, TokenId::AUTO_CLOSE_TAG ) )
                    {
                        if ( !parseAttribute() )
                            return false;
                    }
                }

                if ( readToken( currIndex, TokenId::CLOSE_TAG ) )
                {
                    if ( currNode->getName() == "link" || currNode->getName() == "meta" )
                        currNode = currNode->getParent();

                    ++currIndex;
                    return true;
                }
                else if ( readToken( currIndex, TokenId::AUTO_CLOSE_TAG ) )
                {
                    currNode = currNode->getParent();
                    ++currIndex;
                    return true;
                }
            }
        }
        else if ( readToken( currIndex, TokenId::OPEN_END_TAG ) )
        {
            if ( readToken( ++currIndex, TokenId::TAG_ID ) )
            {
                //todo: apparently wrong: ( <td> ... </th> )
                /*if ( tokens->getToken( currIndex )->getValue() != currNode->getName() )
                    return false;*/

                currNode = currNode->getParent();

                if ( readToken( ++currIndex, TokenId::CLOSE_TAG ) )
                {
                    ++currIndex;
                    return true;
                }
            }
        }
        else if ( readToken( currIndex, TokenId::PLAIN_TEXT ) )
        {
            currNode->getNodes().push_back( std::shared_ptr< HTMLNode >( new HTMLNode( Id::TEXT, tokens.at( currIndex ).get()->getValue() ) ) );
            currNode->getNodes().back().get()->setParent( currNode );
            return true;
        }

        return false;
    }

    bool Parser::parseAttribute()
    {
        if ( readToken( currIndex, TokenId::ATTRIBUTE_NAME ) )
        {
            std::string tmp = tokens.at( currIndex ).get()->getValue();

            if ( readToken( ++currIndex, TokenId::EQUAL_SIGN )
                 && readToken( ++currIndex, TokenId::QUOTATION )
                 && readToken( ++currIndex, TokenId::ATTRIBUTE_VALUE ) )
            {
                currNode->getAttributes().push_back( std::shared_ptr< HTMLAttribute >( new HTMLAttribute( tmp, tokens.at( currIndex ).get()->getValue() ) ) );

                if ( readToken( ++currIndex, TokenId::QUOTATION ) )
                {
                    ++currIndex;
                    return true;
                }
            }
        }

        return false;
    }

    HTMLTree& Parser::getTree()
    {
        return tree;
    }

    bool Parser::readToken( unsigned long index, TokenId name )
    {
        return tokens.at( index ).get()->getName() == name;
    }

    bool Parser::readToken( unsigned long index, TokenId name, std::string value )
    {
        return tokens.at( index ).get()->getName() == name
               && tokens.at( index ).get()->getValue() == value;
    }
}