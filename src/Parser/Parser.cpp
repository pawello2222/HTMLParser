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
            throw exceptions::custom_exception( "Error: Not all tags were closed." );

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

        throw exceptions::custom_exception( "Error: Invalid DOCTYPE tag." );
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
                throw exceptions::custom_exception( "Error: Too many close tags." );
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

                updateSectionPointers( name, currToken->getValue() );

                if ( assertToken( getNextToken(), TokenClass::QUOTATION_MARK ) )
                    return true;
            }
        }

        throwException();
        return false;
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
        throw exceptions::custom_exception( msg.str() );
    }

    void Parser::updateSectionPointers( std::string name, std::string value )
    {
        if ( name == "id" && value == "file" )
            fileSectionPtr = currNode;
        else if ( name == "id" && value == "domains" )
            domainsSectionPtr = currNode;
        if ( name == "id" && value == "hosts" )
            hostsSectionPtr = currNode;
        if ( name == "id" && value == "network_http_tab" )
            requestsSectionPtr = currNode;
    }

    OutputObject& Parser::getOutputObject()
    {
        try
        {
            outputObject.name = extractFileSection( fileSectionPtr, 1 );
            outputObject.size = extractFileSection( fileSectionPtr, 3 );
            outputObject.md5 = extractFileSection( fileSectionPtr, 7 );
            outputObject.domains = extractSection( domainsSectionPtr );
            outputObject.hosts = extractSection( hostsSectionPtr );
            outputObject.http_requests = extractRequestsSection( requestsSectionPtr );
        }
        catch ( std::exception &e )
        {
            throw exceptions::custom_exception( "Error: Corrupted input file." );
        }

        return outputObject;
    }

    std::string Parser::extractFileSection( NodePtr sectionPtr, unsigned long no )
    {
        sectionPtr = sectionPtr->getNodes().at( 3 )->getNodes().at( 1 )->getNodes().at( 1 );

        return sectionPtr->getNodes().at( no )->getNodes().at( 3 )->getNodes().front()->getName();
    }

    NestedVector Parser::extractSection( NodePtr sectionPtr )
    {
        try
        {
            NestedVector result;
            sectionPtr = sectionPtr->getNodes().at( 3 );

            sectionPtr = sectionPtr->getNodes().at( 1 );

            for ( unsigned long i = 1; i <= sectionPtr->getNodes().size() - 1; i += 2 )
            {
                result.push_back( std::make_pair( sectionPtr->getNodes().at( i )->getNodes().front()->getName(),
                                                  std::vector< std::string >() ) );
            }

            sectionPtr = sectionPtr->getParent();

            for ( unsigned long i = 3; i <= sectionPtr->getNodes().size() - 1; i += 2 )
            {
                sectionPtr = sectionPtr->getNodes().at( i );

                for ( unsigned long j = 1, index = 0; j <= sectionPtr->getNodes().size() - 1; j += 2, index++ )
                    result.at( index ).second.push_back( sectionPtr->getNodes().at( j )->getNodes().front()->getName() );

                sectionPtr = sectionPtr->getParent();
            }

            return result;
        }
        catch( std::exception &e )
        {

        }

        return NestedVector();
    }

    NestedVector Parser::extractRequestsSection( NodePtr sectionPtr )
    {
        try
        {
            NestedVector result;

            sectionPtr = sectionPtr->getNodes().at( 3 );
            sectionPtr = sectionPtr->getNodes().at( 1 );

            for ( unsigned long i = 1; i <= sectionPtr->getNodes().size() - 1; i += 2 )
            {
                result.push_back( std::make_pair( sectionPtr->getNodes().at( i )->getNodes().front()->getName(),
                                                  std::vector< std::string >() ) );
            }

            sectionPtr = sectionPtr->getParent();

            for ( unsigned long i = 3; i <= sectionPtr->getNodes().size() - 1; i += 2 )
            {
                sectionPtr = sectionPtr->getNodes().at( i );

                result.at( 0 ).second.push_back( sectionPtr->getNodes().at( 1 )->getNodes().front()->getName() );
                result.at( 1 ).second.push_back(
                        sectionPtr->getNodes().at( 3 )->getNodes().at( 1 )->getNodes().front()->getName() );

                sectionPtr = sectionPtr->getParent();
            }

            return result;
        }
        catch( std::exception &e )
        {

        }

        return NestedVector();
    }
}



