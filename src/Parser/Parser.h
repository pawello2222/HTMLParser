//
// Created by Pawel Wiszenko on 08.04.2016.
//

#ifndef HTMLPARSER_PARSER_H
#define HTMLPARSER_PARSER_H

#include <string>
#include <vector>
#include "../Data Structures/OrderedDict.h"

enum Identifier
{
    ROOT = 0,
    TAG = 1,
    TEXT = 2,
    COMMENT = 3
};

class Attribute
{
public:
    Attribute( std::string _name, std::string _value )
    {
        this->name = _name;
        this->value = _value;
    }

    std::string name;
    std::string value;
};

class Node
{
public:
    Node( Identifier _identifier, std::string _name )
    {
        this->identifier = _identifier;
        this->name = _name;
        this->parent = nullptr;
    }

    Identifier identifier;
    std::string name;
    std::vector< Node* > nodes;
    std::vector< Attribute* > attributes;
    Node* parent;
};

class Tree
{
public:
    Tree()
    {
        root = nullptr;
    }

    Node* root;
    std::string doctype;
};

class Parser
{
public:
    Parser( OrderedDict* _tokens );

    void parse();

private:
    bool parseDoctype();
    bool parseNode();
    bool parseAttribute();

    bool readToken( int index, TokenName name );
    bool readToken( int index, TokenName name, std::string value );

    Tree* tree;
    OrderedDict* tokens;

    Node* currNode;
    int currIndex;
};


#endif //HTMLPARSER_PARSER_H
