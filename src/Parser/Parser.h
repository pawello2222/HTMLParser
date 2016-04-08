//
// Created by Pawel Wiszenko on 08.04.2016.
//

#ifndef HTMLPARSER_PARSER_H
#define HTMLPARSER_PARSER_H

#include <string>
#include <vector>
#include "../Data Structures/OrderedDict.h"

namespace parser
{
    enum Identifier
    {
        TAG = 0,
        TEXT = 1,
        COMMENT = 2
    };

    class Attribute
    {
        std::string name;
        std::string value;
    };

    class TreeNode
    {
        Identifier identifier;

        std::vector< TreeNode* > nodes;
        std::vector< Attribute* > attributes;
    };

    class Tree
    {
        TreeNode* root;

        std::string doctype;
    };
}

class Parser
{
public:
    Parser( OrderedDict* _tokens );
    ~Parser();

    void parse();

private:
    void parseDoctype();
    void parseNode();
    void parseAttribute();

    parser::Tree* tree;
    OrderedDict* tokens;

    int currIndex;
};


#endif //HTMLPARSER_PARSER_H
