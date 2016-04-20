//
// Created by Pawel Wiszenko on 08.04.2016.
//

#include "Parser.h"

namespace parser
{
    Parser::Parser()
    {
        tree = std::unique_ptr< HTMLTree >( new HTMLTree(
                std::shared_ptr< HTMLNode >( new HTMLNode( Id::ROOT ) ) ) );
        currNode = tree->getRoot();
    }

    void Parser::parseDocument( const std::string& path )
    {
        scanner = std::unique_ptr< scanner::Scanner >( new scanner::Scanner( this->path = path ) );

        parseDoctype();

        while ( parseNode() );

        if ( currNode->getIdentifier() != Id::ROOT )
            throw exceptions::parser_exception( "Error: Not all tags were closed." );

        scanner.reset();
    }

    void Parser::parseDoctype()
    {
        if ( assertToken( getNextToken(), TokenClass::OPEN_BEGIN_TAG )
             && assertToken( getNextToken(), TokenClass::EXCLAMATION_MARK )
             && assertToken( getNextToken(), TokenClass::IDENTIFIER, "DOCTYPE" )
             && assertToken( getNextToken(), TokenClass::IDENTIFIER ) )
        {
            tree->setDoctype( currToken->getValue() );
            if ( assertToken( getNextToken(), TokenClass::CLOSE_TAG ) )
                return;
        }

        throw exceptions::parser_exception( "Error: Invalid DOCTYPE tag." );
    }

    bool Parser::parseNode()
    {
        // end of file
        if ( assertToken( getNextToken(), TokenClass::END_OF_FILE ) )
            return false;

        // plain text
        if ( assertToken( currToken, TokenClass::TEXT ) )
        {
            addNode( Id::PLAIN_TEXT, currToken->getValue() );
            return true;
        }

        // open begin tag
        if ( assertToken( currToken, TokenClass::OPEN_BEGIN_TAG ) )
        {
            if ( assertToken( getNextToken(), TokenClass::IDENTIFIER ) )
            {
                addNode( Id::TAG, currToken->getValue() );
                if ( currNode->getName() != "link" && currNode->getName() != "meta" )
                    currNode = currNode->getNodes().back();

                while ( assertToken( getNextToken(), TokenClass::IDENTIFIER ) )
                    parseAttribute();

                if ( assertToken( currToken, TokenClass::CLOSE_TAG ) )
                    return true;
                else if ( assertToken( currToken, TokenClass::AUTO_CLOSE_TAG ) )
                {
                    currNode = currNode->getParent();
                    return true;
                }
            }
        }

        // open end tag
        if ( assertToken( currToken, TokenClass::OPEN_END_TAG )
             && assertToken( getNextToken(), TokenClass::IDENTIFIER ) )
        {
            currNode = currNode->getParent();
            if ( !currNode )
                throw exceptions::parser_exception( "Error: Too many close tags." );
            if ( assertToken( getNextToken(), TokenClass::CLOSE_TAG ) )
                return true;
        }

        throwException();
        return false;
    }

    bool Parser::parseAttribute()
    {
        if ( assertToken( currToken, TokenClass::IDENTIFIER ) )
        {
            auto name = currToken->getValue();
            if ( assertToken( getNextToken(), TokenClass::ASSIGNMENT )
                 && assertToken( getNextToken(), TokenClass::QUOTATION_MARK )
                 && assertToken( getNextToken(), TokenClass::TEXT ) )
            {
                addAttribute( name, currToken->getValue() );
                if ( assertToken( getNextToken(), TokenClass::QUOTATION_MARK ) )
                    return true;
            }
        }

        throwException();
        return false;
    }

    TreePtr Parser::getTree()
    {
        return tree;
    }

    void Parser::addNode( Id id, std::string name )
    {
        currNode->getNodes().push_back( std::shared_ptr< HTMLNode >( new HTMLNode( id, name ) ) );
        currNode->getNodes().back().get()->setParent( currNode );
    }

    void Parser::addAttribute( std::string name, std::string value )
    {
        currNode->getAttributes().push_back( std::shared_ptr< HTMLAttribute >( new HTMLAttribute( name, value ) ) );
    }

    TokenPtr Parser::getNextToken()
    {
        currToken = scanner->getNextToken();
        return currToken;
    }

    bool Parser::assertToken( TokenPtr tokenPtr, TokenClass _class )
    {
        return tokenPtr->getClass() == _class;
    }

    bool Parser::assertToken( TokenPtr tokenPtr, TokenClass _class, std::string _value )
    {
        return tokenPtr->getClass() == _class && tokenPtr->getValue() == _value;
    }

    void Parser::throwException()
    {
        std::stringstream msg;
        msg << "Error in file " << path << " at line " << scanner->getCurrLine()
        << ".\nCurrent node: " << currNode->getName()
        << "\nUnexpected token: " << currToken->description() << "(" << currToken->getValue() << ")";
        throw exceptions::parser_exception( msg.str() );
    }
}