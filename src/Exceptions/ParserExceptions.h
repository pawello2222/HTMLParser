//
// Created by Pawel Wiszenko on 08.04.2016.
//

#ifndef HTMLPARSER_PARSEREXCEPTIONS_H
#define HTMLPARSER_PARSEREXCEPTIONS_H


#include <exception>

namespace exception
{
    namespace parser
    {
        class parser_exception : public std::exception { };
        class doctype_exception : public parser_exception { };
    }
}


#endif //HTMLPARSER_PARSEREXCEPTIONS_H
