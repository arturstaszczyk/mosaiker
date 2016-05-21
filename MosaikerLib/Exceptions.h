#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class PathDoNotExists : public std::exception
{

};

class CannotLoadImage : public std::exception
{

};

class CannotIndexFiles : public std::exception
{

};


#endif // EXCEPTIONS_H

