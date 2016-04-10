//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include "Scanner/Scanner.h"
#include "Parser/Parser.h"
#include "Writer/Writer.h"

typedef std::shared_ptr< scanner::Scanner > ScannerPtr;
typedef std::shared_ptr< parser::Parser > ParserPtr;

/*
void printTokens( std::vector< Token >& tokens )
{
    std::cout << "\n";
    for ( unsigned long i = 0; i < tokens.size(); i++ )
        std::cout << tokens[ i ].description( tokens[ i ].name ) << " " << tokens[ i ].value << std::endl;
}
*/
int main()
{
    ScannerPtr scanner = std::shared_ptr< scanner::Scanner >( new scanner::Scanner() );

    try
    {
        scanner->readFile( "../resources/original-edited.html" );
    }
    catch ( const exceptions::parser_exception &e )
    {
        std::cout << e.getMessage() << std::endl;
        return -1;
    }

    std::cout << "Info: Scan successful. File was opened and closed without errors." << std::endl;

    ParserPtr parser = std::shared_ptr< parser::Parser >( new parser::Parser( scanner->getTokens() ) );

    try
    {
        parser->parse();
    }
    catch( const exceptions::parser_exception& e )
    {
        std::cout << e.getMessage() << std::endl;
        return -1;
    }

    std::cout << "Info: Parse successful. HTML file is valid." << std::endl;

    /*Writer& writer = *( new Writer( parser.getTree() ) );

    try
    {
        writer.write( "./output.txt" );
    }
    catch( const exceptions::parser_exception& e )
    {
        std::cout << e.getMessage() << std::endl;
        return -1;
    }

    std::cout << "Info: Write successful. Output file was saved correctly." << std::endl;

    printTokens( scanner.getTokens() );
    */
    //todo: proper delete
    /*delete &scanner;
    delete &parser;
    delete &writer;*/

    return 0;
}