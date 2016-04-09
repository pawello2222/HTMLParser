//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include "Scanner/Scanner.h"
#include "Parser/Parser.h"
#include "Exceptions/Exceptions.h"

using namespace std;

int main()
{
    Scanner* scanner = new Scanner();

    try
    {
        scanner->readFile( "../resources/original.html" );
    }
    catch ( const file_read_exception &e )
    {
        std::cout << e.getMessage() << endl;
        return -1;
    }

    std::cout << "Info: Scan successful. File was opened and closed without errors." << std::endl;

    Parser* parser = new Parser( scanner->getTokens() );

    try
    {
        parser->parse();
    }
    catch( const parser_exception& e )
    {
        std::cout << e.getMessage() << endl;
        return -1;
    }

    std::cout << "Info: Parse successful. HTML file is valid." << std::endl;


    //scanner->printTokens();

    return 0;
}