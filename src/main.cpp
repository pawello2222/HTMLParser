//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include <iostream>
#include "Parser/Parser.h"
#include "Writer/Writer.h"

typedef std::unique_ptr< parser::Parser > ParserPtr;

int main()
{
//    typedef std::unique_ptr< scanner::Scanner > ScannerPtr;
//    ScannerPtr scanner = std::unique_ptr< scanner::Scanner >( new scanner::Scanner( "../resources/basic.html" ) );
//
//    try
//    {
//        std::shared_ptr<data_structures::Token> token;
//        do
//        {
//            token = scanner->getNextToken();
//            std::cout << token->description() << " " << token->getValue() << std::endl;
//        }
//        while ( token->getClass() != data_structures::TokenClass::END_OF_FILE );
//    }
//    catch ( const exceptions::parser_exception &e )
//    {
//        std::cout << e.getMessage() << std::endl;
//        return -1;
//    }
//
//    std::cout << "Info: Scan successful. File was opened and closed without errors." << std::endl;

    ParserPtr parser = std::unique_ptr< parser::Parser >( new parser::Parser( "../resources/original-edited.html" ) );

    try
    {
        parser->parseDocument();
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