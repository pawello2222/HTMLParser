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

namespace parser
{
    typedef data_structures::TokenClass TokenId;
    typedef data_structures::Identifier Id;
    typedef data_structures::Tree HTMLTree;
    typedef data_structures::Node HTMLNode;
    typedef data_structures::Attribute HTMLAttribute;

    typedef std::shared_ptr< HTMLNode > NodePtr;
    typedef std::shared_ptr< data_structures::Token > TokenPtr;
    typedef std::vector< TokenPtr > Tokens;


    /*enum ReadState
    {
        TAG = 0,
        TAG_SPECIAL,
        TAG_INSIDE,
        ATTRIBUTE_NAME,
        ATTRIBUTE_VALUE,
        COMMENT,
        TEXT,
        TEXT_QUOTED
    };*/

    class Parser
    {
    public:
        Parser( Tokens& _tokens );

        void parse();

        HTMLTree& getTree();

    private:
        bool parseDoctype();
        bool parseNode();
        bool parseAttribute();

        bool readToken( unsigned long index, TokenId name );
        bool readToken( unsigned long index, TokenId name, std::string value );

        HTMLTree tree;
        NodePtr currNode;
        Tokens tokens;
        unsigned long currIndex;
    };
}

#endif //HTMLPARSER_PARSER_H
