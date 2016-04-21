//
// Created by Pawel Wiszenko on 08.04.2016.
//

#ifndef HTMLPARSER_TOKEN_H
#define HTMLPARSER_TOKEN_H


#include <string>

namespace data_structures
{
    enum TokenClass
    {
        IDENTIFIER,
        TEXT,
        OPEN_BEGIN_TAG,
        OPEN_END_TAG,
        CLOSE_TAG,
        AUTO_CLOSE_TAG,
        ASSIGNMENT,
        QUOTATION_MARK,
        EXCLAMATION_MARK,
        NULL_TOKEN,
        END_OF_FILE
    };

    class Token
    {
    public:
        Token( TokenClass _name, std::string _value );
        ~Token();

        const TokenClass& getClass() const;
//        void setClass( const TokenClass& _class );
        const std::string& getValue() const;
//        void setValue( const std::string& _value );

        std::string description();

    private:
        TokenClass _class;
        std::string _value;
    };
}


#endif //HTMLPARSER_TOKEN_H
