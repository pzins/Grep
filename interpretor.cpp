#include "interpretor.h"


Interpretor::Interpretor() {

}



QString Interpretor::Execute(Command* cmd, const QString &command_, QStringList &arguments_, const QString &working_directory_) {
    return cmd->Execute(command_, arguments_, working_directory_);
}
