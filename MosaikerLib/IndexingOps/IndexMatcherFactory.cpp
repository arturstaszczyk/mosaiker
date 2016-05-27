#include "IndexMatcherFactory.h"

#include "Exceptions.h"
#include "IndexMatcherGreedy.h"
#include "IndexMatcherDistance.h"

IIndexMatcherStrategy* IndexMatcherFactory::create(IIndexLoader* indexLoader, const MatcherModel* model)
{
    switch(model->matcher())
    {
        case MatcherModel::MatcherGreedy:
            return new IndexMatcherGreedy(indexLoader);
        case MatcherModel::MatcherDistance:
            return new IndexMatcherDistance(indexLoader, model->distance());
    }

    throw CannotCreateMatcher();
}
