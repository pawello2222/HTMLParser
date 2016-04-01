//
// Created by Pawel on 01.04.2016.
//

#include "Scanner.h"

Scanner::Scanner()
{

}

Scanner::~Scanner()
{

}

void Scanner::readFile( std::string& path )
{
    std::ifstream file( path );
    std::string line;

    while ( getline( file, line ) )
    {
        if ( !line.length() ) continue;

        bool isInsideTag = false;

        int index = 0;
        while ( index < line.length() )
        {
            switch ( line[ index ] )
            {
                case '<':
                    if ( index + 1 < line.length() && line[ index + 1 ] == '/' )
                    {
                        tokens.push_back( std::make_pair( "end_tag open", "" ) );
                        index++;
                    }
                    else
                    {
                        tokens.push_back( std::make_pair( "begin_tag open", "" ) );
                    }
                    isInsideTag = true;
                    break;

                case '>':
                    tokens.push_back( std::make_pair( "begin_tag open", "" ) );
                    break;

                default:
                    break;
            }

            index++;
        }

    }

    file.close();
}




