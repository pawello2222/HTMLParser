//
// Created by Pawel Wiszenko on 09.04.2016.
//

#include "Writer.h"

namespace writer
{
    writer::Writer::Writer()
    {

    }

    void writer::Writer::exportJSON( writer::OutputObject outputObject )
    {
        file = std::ofstream( "./output.txt" );

        if ( !file )
            throw exceptions::custom_exception( "Error: Cannot save output file." );

        file << "{\n";
        file << " \"name\" : \"" << outputObject.name << "\",\n";
        file << " \"size\" : \"" << outputObject.size << "\",\n";
        file << " \"MD5\" : \"" << outputObject.md5 << "\",\n";
        file << " \"domains\" : { " << writeArray( outputObject.domains ) << "},\n";
        file << " \"hosts\" : { " << writeArray( outputObject.hosts ) << "},\n";
        file << " \"http_requests\" : { " << writeArray( outputObject.http_requests ) << "},\n";
        file << "}\n";

        file.close();
    }

    std::string Writer::writeArray( NestedVector nestedVector )
    {
        std::stringstream sstream;

        for ( auto it = nestedVector.begin(); it != nestedVector.end(); it++ )
        {
            for ( unsigned long i = 0; i < it->second.size(); i++ )
            {
                sstream << "\"" << it->first << "\" : \"" << it->second.at( i ) << "\"";
                if ( it + 1 != nestedVector.end() )
                    sstream << ",";
                sstream << " ";
            }
        }

        return sstream.str();
    }
}