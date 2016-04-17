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

    void Attribute::setName( const std::string& name )
    {
        Attribute::name = name;
    }

    const std::string& Attribute::getValue() const
    {
        return value;
    }

    void Attribute::setValue( const std::string& value )
    {
        Attribute::value = value;
    }

    Node::Node( Identifier _identifier, std::string _name )
    {
        this->identifier = _identifier;
        this->name = _name;
    }
    Node::~Node()
    {
        nodes.clear();
        attributes.clear();
    }

    const Identifier& Node::getIdentifier() const
    {
        return identifier;
    }

    void Node::setIdentifier( const Identifier& identifier )
    {
        Node::identifier = identifier;
    }

    const std::string& Node::getName() const
    {
        return name;
    }

    void Node::setName( const std::string& name )
    {
        Node::name = name;
    }

    std::vector< Node* >& Node::getNodes()
    {
        return nodes;
    }

    void Node::setNodes( const std::vector< Node* >& nodes )
    {
        Node::nodes = nodes;
    }

    std::vector< Attribute* >& Node::getAttributes()
    {
        return attributes;
    }

    void Node::setAttributes( const std::vector< Attribute* >& attributes )
    {
        Node::attributes = attributes;
    }

    Node* Node::getParent() const
    {
        return parent;
    }

    void Node::setParent( Node* parent )
    {
        Node::parent = parent;
    }

    Node* Tree::getRoot() const
    {
        return root;
    }

    void Tree::setRoot( Node* root )
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



