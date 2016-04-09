//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include "Scanner/Scanner.h"
#include "Parser/Parser.h"
#include "Writer/Writer.h"

void printTokens( std::vector< Token* > tokens )
{
    std::cout << "\n";
    for ( auto token : tokens )
        std::cout << token->decription( token->name ) << " " << token->value << std::endl;
}

int main()
{
    Scanner* scanner = new Scanner();

    try
    {
        scanner->readFile( "../resources/original-edited.html" );
    }
    catch ( const parser_exception &e )
    {
        std::cout << e.getMessage() << std::endl;
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
        std::cout << e.getMessage() << std::endl;
        return -1;
    }

    std::cout << "Info: Parse successful. HTML file is valid." << std::endl;

    Writer* writer = new Writer( parser->getTree() );

    try
    {
        writer->write( "./output.txt" );
    }
    catch( const parser_exception& e )
    {
        std::cout << e.getMessage() << std::endl;
        return -1;
    }

    std::cout << "Info: Write successful. Output file was saved correctly." << std::endl;

    printTokens( scanner->getTokens() );

    return 0;
}