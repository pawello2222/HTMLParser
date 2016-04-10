//
// Created by Pawel Wiszenko on 10.04.2016.
//

#ifndef HTMLPARSER_TREE_H
#define HTMLPARSER_TREE_H


#include <memory>
#include <string>
#include <vector>

namespace data_structures
{
    class Attribute;
    class Node;

    typedef std::shared_ptr< Attribute > AttributePtr;
    typedef std::shared_ptr< Node > NodePtr;

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
        std::vector< NodePtr >& getNodes();
        void setNodes( const std::vector< NodePtr >& nodes );
        std::vector< AttributePtr >& getAttributes();
        void setAttributes( const std::vector< AttributePtr >& attributes );
        const NodePtr& getParent() const;
        void setParent( const NodePtr& parent );

    private:
        Identifier identifier;
        std::string name;
        std::vector< NodePtr > nodes;
        std::vector< AttributePtr > attributes;
        NodePtr parent;
    };

    class Tree
    {
    public:
        Tree() {};
        ~Tree() {};

        const NodePtr& getRoot() const;
        void setRoot( const NodePtr& root );
        const std::string& getDoctype() const;
        void setDoctype( const std::string& doctype );

    private:
        NodePtr root;
        std::string doctype;
    };
}


#endif //HTMLPARSER_TREE_H
