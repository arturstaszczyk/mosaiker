#ifndef IMAGEMATCHERFACTORY_H
#define IMAGEMATCHERFACTORY_H

#include "Models/MatcherModel.h"
#include "Interfaces/IIndexLoader.h"
#include "Interfaces/IIndexMatcherStrategy.h"

class ImageMatcherFactory
{
public:
    static IIndexMatcherStrategy* create(IIndexLoader* indexLoader, const MatcherModel* model);

private:
    ImageMatcherFactory() {}
    ImageMatcherFactory(const ImageMatcherFactory&){}
};

#endif // IMAGEMATCHERFACTORY_H
