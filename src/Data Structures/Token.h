//
// Created by Pawel Wiszenko on 08.04.2016.
//

#ifndef HTMLPARSER_TOKEN_H
#define HTMLPARSER_TOKEN_H


#include <string>

namespace data_structures
{
    enum TokenName
    {
        OPEN_BEGIN_TAG = 0,
        OPEN_END_TAG = 1,
        TAG_ID = 2,
        CLOSE_TAG = 3,
        AUTO_CLOSE_TAG = 4,
        ATTRIBUTE_NAME = 5,
        ATTRIBUTE_VALUE = 6,
        WHITESPACE = 7,
        EQUAL_SIGN = 8,
        DASH = 9,
        QUOTATION = 10,
        PLAIN_TEXT = 11
    };

    class Token
    {
    public:
        Token( TokenName _name, std::string _value );
        ~Token();

        const TokenName& getName() const;
        void setName( const TokenName& name );
        const std::string& getValue() const;
        void setValue( const std::string& value );

        std::string description( TokenName tokenName );

    private:
        TokenName name;
        std::string value;
    };
}


#endif //HTMLPARSER_TOKEN_H
