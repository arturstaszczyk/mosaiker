#include "ImageMatcherFactory.h"

#include "Exceptions.h"
#include "ImageMatcherGreedy.h"
#include "ImageMatcherDistance.h"

IIndexMatcherStrategy* ImageMatcherFactory::create(IIndexLoader* indexLoader, const MatcherModel* model)
{
    switch(model->matcher())
    {
        case MatcherModel::MatcherGreedy:
            return new ImageMatcherGreedy(indexLoader);
        case MatcherModel::MatcherDistance:
            return new ImageMatcherDistance(indexLoader, model->distance());
    }

    throw CannotCreateMatcher();
}
