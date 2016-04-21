//
// Created by Pawel Wiszenko on 09.04.2016.
//

#ifndef HTMLPARSER_WRITER_H
#define HTMLPARSER_WRITER_H


#include <fstream>
#include <sstream>
#include "../Data Structures/JSONObject.h"
#include "../Exceptions/Exceptions.h"

namespace writer
{
    typedef data_structures::JSONObject OutputObject;
    typedef data_structures::NestedVector NestedVector;

    class Writer
    {
    public:
        Writer();

        void exportJSON( OutputObject outputObject );

    private:
        std::string writeArray( NestedVector nestedVector );
        std::string writeField( std::string name, std::string value );
        std::string writeHTTPMethod( std::string data );

        std::ofstream file;
    };

}

#endif //HTMLPARSER_WRITER_H
