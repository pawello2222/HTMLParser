//
// Created by Pawel Wiszenko on 08.04.2016.
//

#include "Parser.h"
#include "../Exceptions/ParserExceptions.h"

Parser::Parser( OrderedDict* _tokens )
{
    this->tokens = _tokens;
    this->currIndex = 0;
}

Parser::~Parser()
{
    delete tree; //todo: safe delete
}

void Parser::parse()
{
    tree = new parser::Tree();

    try
    {
        parseDoctype();
    }
    catch( const exception::parser::parser_exception& e )
    {
        throw new exception::parser::parser_exception();
    }

}

void Parser::parseDoctype()
{
    if ( tokens->getToken( currIndex )->name == 0 )
    {

    }
}

void Parser::parseNode()
{

}

void Parser::parseAttribute()
{

}
