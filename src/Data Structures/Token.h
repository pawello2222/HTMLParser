//
// Created by Pawel Wiszenko on 08.04.2016.
//

#ifndef HTMLPARSER_TOKEN_H
#define HTMLPARSER_TOKEN_H

#include <string>

//const int TOKEN_NAME_COUNT = 13;

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
    EXCLAMATION_MARK = 11,
    PLAIN_TEXT = 12
};

struct Token
{
    Token( TokenName _name, std::string _value )
    {
        this->name = _name;
        this->value = _value;
    }

    std::string decription( TokenName tokenName )
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
            case EXCLAMATION_MARK:
                return "EXCLAMATION_MARK";
            case PLAIN_TEXT:
                return "PLAIN_TEXT";
        }

        return std::string();
    }

    TokenName name;
    std::string value;
};


#endif //HTMLPARSER_TOKEN_H
