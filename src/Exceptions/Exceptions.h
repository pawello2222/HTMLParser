//
// Created by Pawel Wiszenko on 08.04.2016.
//

#ifndef HTMLPARSER_EXCEPTIONS_H
#define HTMLPARSER_EXCEPTIONS_H


#include <exception>
#include <string>

namespace exceptions
{
    class custom_exception : public std::exception
    {
    public:
        custom_exception( std::string _message )
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
}


#endif //HTMLPARSER_EXCEPTIONS_H
