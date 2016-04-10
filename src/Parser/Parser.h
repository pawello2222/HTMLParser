//
// Created by Pawel Wiszenko on 08.04.2016.
//

#ifndef HTMLPARSER_PARSER_H
#define HTMLPARSER_PARSER_H


#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "../Data Structures/Tree.h"
#include "../Data Structures/Token.h"
#include "../Exceptions/Exceptions.h"

namespace parser
{
    typedef data_structures::TokenName TokenId;
    typedef data_structures::Identifier Id;
    typedef data_structures::Tree HTMLTree;
    typedef data_structures::Node HTMLNode;
    typedef data_structures::Attribute HTMLAttribute;

    typedef std::shared_ptr< HTMLNode > NodePtr;
    typedef std::shared_ptr< data_structures::Token > TokenPtr;
    typedef std::vector< TokenPtr > Tokens;

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
