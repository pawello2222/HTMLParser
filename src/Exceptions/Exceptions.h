//
// Created by Pawel Wiszenko on 08.04.2016.
//

#ifndef HTMLPARSER_EXCEPTIONS_H
#define HTMLPARSER_EXCEPTIONS_H


#include <exception>
#include <string>

//todo: make one base class for all derived custom exceptions

class parser_exception : public std::exception
{
public:
    parser_exception()
    {
        this->message = "";
    }
    parser_exception( std::string _message )
    {
        this->message = _message;
    }

    const std::string& getMessage() const
    {
        return message;
    }

private:
    std::string message;
};

class file_read_exception : public std::exception
{
public:
    file_read_exception()
    {
        this->message = "";
    }
    file_read_exception( std::string _message )
    {
        this->message = _message;
    }

    const std::string& getMessage() const
    {
        return message;
    }

private:
    std::string message;
};


#endif //HTMLPARSER_EXCEPTIONS_H
