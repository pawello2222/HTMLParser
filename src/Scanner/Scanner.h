//
// Created by Pawel Wiszenko on 01.04.2016.
//

#ifndef HTMLPARSER_SCANNER_H
#define HTMLPARSER_SCANNER_H


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../Data Structures/OrderedDict.h"
#include "../Exceptions/Exceptions.h"

class Scanner
{
public:
    Scanner();
    ~Scanner();

    void readFile( const std::string& path );

    void printTokens();
    OrderedDict* getTokens();

private:
    void addToken( TokenName key, std::string value );
    OrderedDict* tokens;

    std::string specialCharacters;
};


#endif //HTMLPARSER_SCANNER_H
