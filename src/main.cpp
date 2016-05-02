//
// Created by Pawel Wiszenko on 01.04.2016.
//

#include <iostream>
#include "Parser/Parser.h"
#include "Writer/Writer.h"

typedef std::unique_ptr< parser::Parser > ParserPtr;
typedef std::unique_ptr< writer::Writer > WriterPtr;

int main()
{
    ParserPtr parser = std::unique_ptr< parser::Parser >( new parser::Parser() );

    try
    {
        parser->parseDocument( "../resources/malwr/Malwr7.html" );
    }
    catch( const exceptions::custom_exception& e )
    {
        std::cout << e.getMessage() << std::endl;
        return -1;
    }

    std::cout << "Info: Parse successful. HTML file is valid." << std::endl;

    WriterPtr writer = std::unique_ptr< writer::Writer >( new writer::Writer() );

    try
    {
        writer->exportJSON( parser->getOutputObject() );
    }
    catch( const exceptions::custom_exception& e )
    {
        std::cout << e.getMessage() << std::endl;
        return -1;
    }

    std::cout << "Info: Write successful. Output file was saved correctly." << std::endl;

    return 0;
}