//
// Created by Pawel Wiszenko on 10.04.2016.
//

#ifndef HTMLPARSER_TREE_H
#define HTMLPARSER_TREE_H


#include <string>
#include <vector>

namespace data_structures
{
    class Node;
    class Attribute;

    typedef std::shared_ptr< Node > NodePtr;
    typedef std::shared_ptr< Attribute > AttributePtr;
    typedef std::vector< NodePtr > Nodes;
    typedef std::vector< AttributePtr > Attributes;

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
        const std::string& getValue() const;

    private:
        std::string name;
        std::string value;
    };

    class Node
    {
    public:
        Node( Identifier _identifier );
        Node( Identifier _identifier, std::string _name );
        ~Node();

        const Identifier& getIdentifier() const;
        const std::string& getName() const;
        Nodes& getNodes();
        Attributes& getAttributes();
        NodePtr getParent();
        void setParent( NodePtr parent );

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
        Tree( NodePtr root );
        ~Tree() {};

        NodePtr getRoot();
        const std::string& getDoctype() const;
        void setDoctype( const std::string& doctype );

    private:
        NodePtr root;
        std::string doctype;
    };
}


#endif //HTMLPARSER_TREE_H
