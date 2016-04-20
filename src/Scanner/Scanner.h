//
// Created by Pawel Wiszenko on 01.04.2016.
//

#ifndef HTMLPARSER_SCANNER_H
#define HTMLPARSER_SCANNER_H


#include <memory>
#include <string>
#include <fstream>
#include <queue>
#include "../Data Structures/Token.h"
#include "../Exceptions/Exceptions.h"

namespace scanner
{
    typedef data_structures::TokenClass TokenClass;
    typedef std::shared_ptr< data_structures::Token > TokenPtr;

    const int MAX_QUEUE_SIZE = 3;

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

        TokenPtr getNextToken();
        int getCurrLine() const;

    private:
        void parseFile();
        TokenPtr addToken( TokenClass key, std::string value = "" );

        std::string outputStr;
        std::ifstream file;
        ReadState state;
        std::queue< TokenPtr > queue;
        int currLine;
    };
}


#endif //HTMLPARSER_SCANNER_H
