//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include "Scanner/Scanner.h"
#include "Parser/Parser.h"
#include "Exceptions/ParserExceptions.h"

using namespace std;

int main()
{
    Scanner* scanner = new Scanner();
    Parser* parser = new Parser( scanner->getTokens() );
    scanner->readFile( "../resources/original.html" );

    try
    {
        parser->parse();
    }
    catch( parser_exception::doctype_exception& e )
    {
        std::cout << "Error: invalid DOCTYPE tag" << endl;
    }
    catch( parser_exception::node_exception& e )
    {
        std::cout << "Error: invalid tag" << endl;
    }


    //scanner->printTokens();

    return 0;
}