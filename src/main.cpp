//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include <iostream>
#include "Parser/Parser.h"
#include "Writer/Writer.h"

typedef std::unique_ptr< parser::Parser > ParserPtr;

int main()
{
    ParserPtr parser = std::unique_ptr< parser::Parser >( new parser::Parser() );

    try
    {
        parser->parseDocument( "../resources/original.html" );
        auto jsonObject = parser->getJSONObject();
        std::cout << jsonObject.domains.at( 1 ).second.at( 0 ) << std::endl;
    }
    catch( const exceptions::parser_exception& e )
    {
        std::cout << e.getMessage() << std::endl;
        return -1;
    }

    std::cout << "Info: Parse successful. HTML file is valid." << std::endl;

//    Writer& writer = *( new Writer( parser.getTree() ) );
//
//    try
//    {
//        writer.write( "./output.txt" );
//    }
//    catch( const exceptions::parser_exception& e )
//    {
//        std::cout << e.getMessage() << std::endl;
//        return -1;
//    }
//
//    std::cout << "Info: Write successful. Output file was saved correctly." << std::endl;

    return 0;
}