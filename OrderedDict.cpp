//
// Created by Pawel Wiszenko on 03.04.2016.
//

#include "OrderedDict.h"

void OrderedDict::insert( Token token )
{
    indexedData.insert( std::make_pair( token.value, orderedData.size() ) );
    orderedData.push_back( token );
}

/*Token OrderedDict::getToken( std::string str )
{
    auto it = indexedData.find( str );
    if ( it != indexedData.end() )
        return orderedData[ it->second ];
    else
        return Token( "", "" );
}*/

void OrderedDict::print()
{
    for( auto it = orderedData.begin(); it != orderedData.end(); it++ )
        std::cout << it->name << " " << it->value << std::endl;
}