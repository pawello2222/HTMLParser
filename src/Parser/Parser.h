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
    typedef std::shared_ptr< HTMLAttribute > AttributePtr;
    typedef std::shared_ptr< data_structures::Token > TokenPtr;
    typedef std::unique_ptr< scanner::Scanner > ScannerPtr;

    typedef std::vector< std::pair< std::string, std::vector< std::string > > > JSONArray;

    typedef struct JSONObject_t
    {
        std::string name;
        std::string size;
        std::string md5;
        JSONArray domains;
        JSONArray hosts;
        JSONArray http_requests;
    } JSONObject;

    class Parser
    {
    public:
        Parser();

        void parseDocument( const std::string& path );
        JSONObject& serializeJSONObject();

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
        JSONArray extractSection( NodePtr sectionPtr );
        JSONArray extractRequestsSection( NodePtr sectionPtr );

        JSONObject jsonObject;
        NodePtr fileSectionPtr;
        NodePtr domainsSectionPtr;
        NodePtr hostsSectionPtr;
        NodePtr requestsSectionPtr;
    };
}

#endif //HTMLPARSER_PARSER_H
