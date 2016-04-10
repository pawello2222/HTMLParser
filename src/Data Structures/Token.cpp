//
// Created by Pawel Wiszenko on 08.04.2016.
//

#include "Token.h"

namespace data_structures
{
    Token::Token( TokenName _name, std::string _value )
    {
        this->name = _name;
        this->value = _value;
    }

    Token::~Token()
    {

    }

    const TokenName& Token::getName() const
    {
        return name;
    }

    void Token::setName( const TokenName& name )
    {
        Token::name = name;
    }

    const std::string& Token::getValue() const
    {
        return value;
    }

    void Token::setValue( const std::string& value )
    {
        Token::value = value;
    }

    std::string Token::description( TokenName tokenName )
    {
        switch ( tokenName )
        {
            case OPEN_BEGIN_TAG:
                return "OPEN_BEGIN_TAG";
            case OPEN_END_TAG:
                return "OPEN_END_TAG";
            case TAG_ID:
                return "TAG_ID";
            case CLOSE_TAG:
                return "CLOSE_TAG";
            case AUTO_CLOSE_TAG:
                return "AUTO_CLOSE_TAG";
            case ATTRIBUTE_NAME:
                return "ATTRIBUTE_NAME";
            case ATTRIBUTE_VALUE:
                return "ATTRIBUTE_VALUE";
            case WHITESPACE:
                return "WHITESPACE";
            case EQUAL_SIGN:
                return "EQUAL_SIGN";
            case DASH:
                return "DASH";
            case QUOTATION:
                return "QUOTATION";
            case PLAIN_TEXT:
                return "PLAIN_TEXT";
        }

        return std::string();
    }
}