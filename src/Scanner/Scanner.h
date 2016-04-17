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
#include "../Data Structures/Token.h"
#include "../Exceptions/Exceptions.h"

namespace scanner
{
    typedef std::vector< data_structures::Token* > Tokens;
    typedef data_structures::TokenClass TokenClass;

    enum ReadState
    {
        TAG,
        TEXT,
        TEXT_QUOTED,
        COMMENT
    };

    class Scanner
    {
    public:
        Scanner();
        ~Scanner();

        void readFile( const std::string& path );

        Tokens& getTokens();

    private:
        void addToken( TokenClass key, std::string value );
        TokenClass getLastTokenClass( int index );

        Tokens tokens;

        std::string outputStr;
    };
}


#endif //HTMLPARSER_SCANNER_H
