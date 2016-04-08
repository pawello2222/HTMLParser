//
// Created by Pawel Wiszenko on 03.04.2016.
//

#include "OrderedDict.h"

OrderedDict::OrderedDict()
{
    indexedData.clear();
    orderedData.clear();
}

void OrderedDict::insert( Token token )
{
    indexedData.insert( std::make_pair( token.value, orderedData.size() ) );
    orderedData.push_back( token );
}

void OrderedDict::print()
{
    for( auto it = orderedData.begin(); it != orderedData.end(); it++ )
        std::cout << it->decription( it->name ) << " " << it->value << std::endl;
}

Token* OrderedDict::getToken( int index )
{
    if ( index >= orderedData.size() )
        return nullptr;

    return &orderedData[ index ];
}

Token* OrderedDict::getToken( std::string str )
{
    auto it = indexedData.find( str );
    if ( it != indexedData.end() )
        return &orderedData[ it->second ];
    else
        return nullptr;
}

const long OrderedDict::getSize() const
{
    return orderedData.size();
}
