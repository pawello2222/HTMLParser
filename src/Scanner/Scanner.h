//
// Created by Pawel Wiszenko on 01.04.2016.
//

#ifndef HTMLPARSER_SCANNER_H
#define HTMLPARSER_SCANNER_H


#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>
#include "../Data Structures/Token.h"
#include "../Exceptions/Exceptions.h"

namespace scanner
{
    typedef std::shared_ptr< data_structures::Token > TokenPtr;
    typedef std::vector< TokenPtr > Tokens;
    typedef data_structures::TokenName TokenId;

    enum ReadState
    {
        READ_TAG = 0,
        READ_TAG_INSIDE = 1,
        READ_VALUE = 2,
        READ_TEXT = 3,
        READ_COMMENT = 4
    };

    enum ScriptState
    {
        NO_SCRIPT = 0,
        READ_SCRIPT = 1,
        READ_QUOTED_TEXT = 2,
    };

    class Scanner
    {
    public:
        Scanner();
        ~Scanner();

        void readFile( const std::string& path );

        Tokens& getTokens();

    private:
        void addToken( data_structures::TokenName key, std::string value );

        Tokens tokens;

        std::string specialCharacters;
    };
}


#endif //HTMLPARSER_SCANNER_H
