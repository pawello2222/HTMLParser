//
// Created by Pawel on 01.04.2016.
//

#ifndef HTMLPARSER_SCANNER_H
#define HTMLPARSER_SCANNER_H


#include <string>
#include <fstream>
#include <vector>

class Scanner
{
public:
    Scanner();
    ~Scanner();

    void readFile( std::string& path );
    void readURL( std::string& path );
    void readHTML();

private:
    std::vector< std::pair< std::string, std::string > > tokens; // tokens[ token, attribute ]

};


#endif //HTMLPARSER_SCANNER_H
