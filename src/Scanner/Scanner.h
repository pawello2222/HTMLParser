//
// Created by Pawel Wiszenko on 01.04.2016.
//

#ifndef HTMLPARSER_SCANNER_H
#define HTMLPARSER_SCANNER_H


#include <string>
#include <fstream>
#include <queue>
#include "../Data Structures/Token.h"
#include "../Exceptions/Exceptions.h"

namespace scanner
{
    typedef data_structures::TokenClass TokenClass;

    const int MAX_QUQUE_SIZE = 3;

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
        Scanner( const std::string& path );
        ~Scanner();

        data_structures::Token* getNextToken();

    private:
        void parseFile();
        data_structures::Token* addToken( TokenClass key, std::string value = "" );

        std::string outputStr;
        std::ifstream file;
        ReadState state;
        std::queue< data_structures::Token* > queue;
    };
}


#endif //HTMLPARSER_SCANNER_H
