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
    void insert( Token token );
    //Token getToken( std::string str );
    void print();

private:
    std::map< std::string ,int > indexedData;
    std::vector< Token > orderedData;
};


#endif //HTMLPARSER_ORDEREDDICT_H
