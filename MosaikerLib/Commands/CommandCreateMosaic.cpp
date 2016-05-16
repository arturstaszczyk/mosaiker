#include "CommandCreateMosaic.h"

CommandCreateMosaic::CommandCreateMosaic(QObject* parent)
    : Command(COMMAND_NAME(CommandCreateMosaic), parent)
{

}

void CommandCreateMosaic::execute()
{
    CommandFinisher finisher(this);
}
