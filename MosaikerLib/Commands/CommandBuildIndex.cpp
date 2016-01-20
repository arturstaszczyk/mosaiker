#include "CommandBuildIndex.h"

CommandBuildIndex::CommandBuildIndex(IResourceFinder& finder, QObject* parent)
        : Command(parent)
        , mResourceFinder(finder)
{

}
