//
// Created by Pawel Wiszenko on 08.04.2016.
//

#ifndef HTMLPARSER_PARSER_H
#define HTMLPARSER_PARSER_H


#include <sstream>
#include <string>
#include <vector>
#include "../Data Structures/Tree.h"
#include "../Data Structures/Token.h"
#include "../Data Structures/JSONObject.h"
#include "../Exceptions/Exceptions.h"
#include "../Scanner/Scanner.h"

namespace parser
{
    typedef data_structures::TokenClass TokenClass;
    typedef data_structures::Identifier Id;

    typedef data_structures::Tree HTMLTree;
    typedef data_structures::Node HTMLNode;
    typedef data_structures::Attribute HTMLAttribute;

    typedef std::shared_ptr< HTMLTree > TreePtr;
    typedef std::shared_ptr< HTMLNode > NodePtr;
    typedef std::shared_ptr< data_structures::Token > TokenPtr;
    typedef std::unique_ptr< scanner::Scanner > ScannerPtr;

    typedef data_structures::JSONObject OutputObject;
    typedef data_structures::NestedVector NestedVector;

    class Parser
    {
    public:
        Parser();

        void parseDocument( const std::string& path );
        OutputObject& getOutputObject();

    private:
        void throwException();
        void parseDoctype();
        bool parseNode();
        bool parseAttribute();

        void addNode( Id id, std::string name );
        void addAttribute( std::string name, std::string value );

        TokenPtr getNextToken();
        bool assertToken( TokenPtr tokenPtr, TokenClass _class );
        bool assertToken( TokenPtr tokenPtr, TokenClass _class, std::string _value );

        ScannerPtr scanner;
        TreePtr tree;
        NodePtr currNode;
        TokenPtr currToken;
        std::string path;

    private:
        void updateSectionPointers( std::string name, std::string value );
        std::string extractFileSection( NodePtr sectionPtr, unsigned long no );
        NestedVector extractSection( NodePtr sectionPtr );
        NestedVector extractRequestsSection( NodePtr sectionPtr );

        OutputObject outputObject;
        NodePtr fileSectionPtr;
        NodePtr domainsSectionPtr;
        NodePtr hostsSectionPtr;
        NodePtr requestsSectionPtr;
    };
}

#endif //HTMLPARSER_PARSER_H
