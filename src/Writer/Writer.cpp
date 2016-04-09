//
// Created by Pawel Wiszenko on 09.04.2016.
//

#include "Writer.h"

Writer::Writer( Tree* _tree )
{
    this->tree = _tree;
}

void Writer::write( std::string path )
{
    std::ofstream file( path );
    if ( !file )
        throw parser_exception( "Error: Cannot open output file." );

    file << "ASD";

    file.close();
}

void Writer::generateJSONTree()
{

}
