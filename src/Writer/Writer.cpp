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
        file << " " << writeField( "Name", outputObject.name ) << ",\n";
        file << " " << writeField( "Size", outputObject.size ) << ",\n";
        file << " " << writeField( "MD5", outputObject.md5 ) << ",\n";
        file << " " << "\"Domains\" : " << writeArray( outputObject.domains ) << ",\n";
        file << " " << "\"Hosts\" : " << writeArray( outputObject.hosts ) << ",\n";
        file << " " << "\"Http Requests\" : " << writeArray( outputObject.http_requests ) << "\n";
        file << "}\n";

        file.close();
    }

    std::string Writer::writeArray( NestedVector nestedVector )
    {
        if ( !nestedVector.size() )
            return "{ }";

        std::stringstream sstream;

        sstream << "{ ";

        for ( unsigned long i = 0; i < nestedVector.front().second.size(); i++ )
        {
            if ( nestedVector.front().second.size() > 1 )
                sstream << "{ ";

            for ( unsigned long j = 0; j < nestedVector.size(); j++ )
            {
                if ( nestedVector.at( j ).first == "Data" )
                    sstream << "\"" << nestedVector.at( j ).first << "\" : "
                            << writeHTTPMethod( nestedVector.at( j ).second.at( i ) );
                else
                    sstream << writeField( nestedVector.at( j ).first, nestedVector.at( j ).second.at( i ) );
                if ( j + 1 != nestedVector.size() )
                {
                    sstream << ",";
                    sstream << " ";
                }
            }

            if ( nestedVector.front().second.size() > 1 )
                sstream << "}";

            if ( i + 1 != nestedVector.front().second.size() )
                sstream << ", ";
        }

        sstream << " }";

        return sstream.str();
    }

    std::string Writer::writeField( std::string name, std::string value )
    {
        std::stringstream sstream;
        sstream << "\"" << name << "\" : \"" << value << "\"";
        return sstream.str();
    }

    std::vector< std::string > split( std::string& data )
    {
        std::vector< std::string > result;

        unsigned long index = data.find_first_of( "\n" );

        while( index != std::string::npos )
        {
            result.push_back( data.substr( 0, index - 1 ) );
            data.erase( 0, index + 1 );
            index = data.find_first_of( '\n' );
        }
        result.push_back( data );

        return result;
    }

    std::string Writer::writeHTTPMethod( std::string data )
    {
        std::stringstream sstream;

        std::vector< std::string > lines = split( data );

        unsigned long index;
        sstream << "{ " << writeField( "Method", lines.at( 0 ) ) << ", ";

        unsigned long i;
        for ( i = 1; i < lines.size() - 1; i++ )
        {
            index = lines.at( i ).find_first_of( ':' );
            if ( index == std::string::npos )
                break;
            sstream << writeField( lines.at( i ).substr( 0, index ), lines.at( i ).substr( index + 2, lines.at( i ).length() - index - 2 ) ) << ", ";
        }

        if ( i + 1 < lines.size() )
            sstream << writeField( "Data", lines.at( i + 1 ) ) << " } ";

        return sstream.str();
    }
}