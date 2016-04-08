//
// Created by Pawel on 01.04.2016.
//

#include <iostream>
#include "Scanner/Scanner.h"
#include "Parser/Parser.h"

using namespace std;

int main()
{
    Scanner* scanner = new Scanner();
    scanner->readFile( "../resources/basic.html" );
    scanner->printTokens();
    //scanner->getTokenValue( "Domains" );

    return 0;
}