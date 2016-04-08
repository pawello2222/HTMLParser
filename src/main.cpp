//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include "Scanner/Scanner.h"
#include "Parser/Parser.h"

using namespace std;

int main()
{
    Scanner* scanner = new Scanner();
    Parser* parser = new Parser( scanner->getTokens() );
    scanner->readFile( "../resources/basic.html" );
    parser->parse();


    scanner->printTokens();

    return 0;
}