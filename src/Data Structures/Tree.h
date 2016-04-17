//
// Created by Pawel Wiszenko on 10.04.2016.
//

#ifndef HTMLPARSER_TREE_H
#define HTMLPARSER_TREE_H


#include <string>
#include <vector>

namespace data_structures
{
    enum Identifier
    {
        ROOT = 0,
        TAG = 1,
        PLAIN_TEXT = 2,
        COMMENT = 3
    };

    class Attribute
    {
    public:
        Attribute( std::string _name, std::string _value );

        const std::string& getName() const;
        void setName( const std::string& name );
        const std::string& getValue() const;
        void setValue( const std::string& value );

    private:
        std::string name;
        std::string value;
    };

    class Node
    {
    public:
        Node( Identifier _identifier, std::string _name );
        ~Node();

        const Identifier& getIdentifier() const;
        void setIdentifier( const Identifier& identifier );
        const std::string& getName() const;
        void setName( const std::string& name );
        std::vector< Node* >& getNodes();
        void setNodes( const std::vector< Node* >& nodes );
        std::vector< Attribute* >& getAttributes();
        void setAttributes( const std::vector< Attribute* >& attributes );
        Node* getParent() const;
        void setParent( Node* parent );

    private:
        Identifier identifier;
        std::string name;
        std::vector< Node* > nodes;
        std::vector< Attribute* > attributes;
        Node* parent;
    };

    class Tree
    {
    public:
        Tree() {};
        ~Tree() {};

        Node* getRoot() const;
        void setRoot( Node* root );
        const std::string& getDoctype() const;
        void setDoctype( const std::string& doctype );

    private:
        Node* root;
        std::string doctype;
    };
}


#endif //HTMLPARSER_TREE_H
