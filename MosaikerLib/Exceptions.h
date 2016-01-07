#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class ResourcesDirDoNotExists : public std::exception
{

};

class ImageDoNotExists : public std::exception
{

};

class CannotLoadImage : public std::exception
{

};

class CannotCreateImage : public std::exception
{

};

#endif // EXCEPTIONS_H

