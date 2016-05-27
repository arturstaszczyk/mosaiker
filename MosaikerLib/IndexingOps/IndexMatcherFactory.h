#ifndef IMAGEMATCHERFACTORY_H
#define IMAGEMATCHERFACTORY_H

#include "Models/MatcherModel.h"
#include "Interfaces/IIndexLoader.h"
#include "Interfaces/IIndexMatcherStrategy.h"

class IndexMatcherFactory
{
public:
    static IIndexMatcherStrategy* create(IIndexLoader* indexLoader, const MatcherModel* model);

private:
    IndexMatcherFactory() {}
    IndexMatcherFactory(const IndexMatcherFactory&){}
};

#endif // IMAGEMATCHERFACTORY_H
