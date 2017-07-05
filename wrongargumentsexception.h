#ifndef WRONGARGUMENTSEXCEPTION_H
#define WRONGARGUMENTSEXCEPTION_H
#include <exception>
#include <QString>

class WrongArgumentsException : public std::exception
{
public:
    WrongArgumentsException(const char* msg_) : msg(msg_) {}

    const char* what() const throw() {
        return msg;
    }
private:
    const char* msg;

};

#endif // WRONGARGUMENTSEXCEPTION_H
