//
// Created by Pawel on 01.04.2016.
//

#ifndef HTMLPARSER_SCANNER_H
#define HTMLPARSER_SCANNER_H


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "OrderedDict.h"

class Scanner
{
public:
    Scanner();
    ~Scanner();

    void readFile( const std::string& path );

    void printTokens();
    //void getTokenValue( std::string value );

private:
    void addToken( std::string key, std::string value );
    OrderedDict* tokens;

};


#endif //HTMLPARSER_SCANNER_H
