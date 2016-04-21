//
// Created by Pawel Wiszenko on 21.04.2016.
//

#ifndef HTMLPARSER_JSONOBJECT_H
#define HTMLPARSER_JSONOBJECT_H


#include <string>
#include <vector>

namespace data_structures
{
    typedef std::vector< std::pair< std::string, std::vector< std::string > > > NestedVector;

    typedef struct JSONObject_t
    {
        std::string name;
        std::string size;
        std::string md5;
        NestedVector domains;
        NestedVector hosts;
        NestedVector http_requests;
    } JSONObject;
}

#endif //HTMLPARSER_JSONOBJECT_H
