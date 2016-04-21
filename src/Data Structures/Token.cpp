//
// Created by Pawel Wiszenko on 08.04.2016.
//

#include "Token.h"

namespace data_structures
{
    Token::Token( TokenClass _class, std::string _value )
    {
        this->_class = _class;
        this->_value = _value;
    }

    Token::~Token()
    {

    }

    const TokenClass& Token::getClass() const
    {
        return _class;
    }

//    void Token::setClass( const TokenClass& _class )
//    {
//        this->_class = _class;
//    }

    const std::string& Token::getValue() const
    {
        return _value;
    }

//    void Token::setValue( const std::string& _value )
//    {
//        this->_value = _value;
//    }

    std::string Token::description()
    {
        switch ( _class )
        {
            case OPEN_BEGIN_TAG:
                return "OPEN_BEGIN_TAG";
            case OPEN_END_TAG:
                return "OPEN_END_TAG";
            case IDENTIFIER:
                return "IDENTIFIER";
            case TEXT:
                return "TEXT";
            case CLOSE_TAG:
                return "CLOSE_TAG";
            case AUTO_CLOSE_TAG:
                return "AUTO_CLOSE_TAG";
            case ASSIGNMENT:
                return "ASSIGNMENT";
            case QUOTATION_MARK:
                return "QUOTATION_MARK";
            case EXCLAMATION_MARK:
                return "EXCLAMATION_MARK";
            case NULL_TOKEN:
                return "NULL_TOKEN";
            case END_OF_FILE:
                return "END_OF_FILE";
        }

        return std::string();
    }
}