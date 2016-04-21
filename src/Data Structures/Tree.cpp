//
// Created by Pawel Wiszenko on 10.04.2016.
//

#include "Tree.h"

namespace data_structures
{
    Attribute::Attribute( std::string _name, std::string _value )
    {
        this->name = _name;
        this->value = _value;
    }

    const std::string& Attribute::getName() const
    {
        return name;
    }

    const std::string& Attribute::getValue() const
    {
        return value;
    }

    Node::Node( Identifier _identifier )
    {
        this->identifier = _identifier;
        this->name = "";
    }

    Node::Node( Identifier _identifier, std::string _name )
    {
        this->identifier = _identifier;
        this->name = _name;
    }

    Node::~Node()
    {
        // TODO
        nodes.clear();
        attributes.clear();
    }

    const Identifier& Node::getIdentifier() const
    {
        return identifier;
    }

    const std::string& Node::getName() const
    {
        return name;
    }

    Nodes& Node::getNodes()
    {
        return nodes;
    }

    Attributes& Node::getAttributes()
    {
        return attributes;
    }

    NodePtr Node::getParent()
    {
        return parent;
    }

    void Node::setParent( NodePtr parent )
    {
        Node::parent = parent;
    }

    NodePtr Tree::getRoot()
    {
        return root;
    }

    Tree::Tree( NodePtr root )
    {
        Tree::root = root;
    }

    const std::string& Tree::getDoctype() const
    {
        return doctype;
    }

    void Tree::setDoctype( const std::string& doctype )
    {
        Tree::doctype = doctype;
    }
}



