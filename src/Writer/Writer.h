//
// Created by Pawel Wiszenko on 09.04.2016.
//

#ifndef HTMLPARSER_WRITER_H
#define HTMLPARSER_WRITER_H

#include <fstream>
#include "../Parser/Parser.h"
#include "../Exceptions/Exceptions.h"

class Writer
{
public:
    Writer( Tree* _tree );

    void write( std::string path );

private:
    void generateJSONTree();

    Tree* tree;
};


#endif //HTMLPARSER_WRITER_H
