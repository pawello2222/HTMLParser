//
// Created by Pawel Wiszenko on 03.04.2016.
//

#ifndef HTMLPARSER_ORDEREDDICT_H
#define HTMLPARSER_ORDEREDDICT_H

#include <iostream>
#include <map>
#include <vector>
#include "Token.h"

class OrderedDict
{
public:
    OrderedDict();

    void insert( Token token );
    void print();

    Token* getToken( long index );
    Token* getToken( std::string str );

    const long getSize() const;

private:
    std::map< std::string, int > indexedData;
    std::vector< Token > orderedData;
};


#endif //HTMLPARSER_ORDEREDDICT_H
