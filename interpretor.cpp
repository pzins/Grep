#include "interpretor.h"
#include <gtest/gtest.h>



Interpretor::Interpretor(const QString &color_) : color(color_){

}

void Interpretor::ConvertNewLineToHTML(QString& output)
{
    output = output.replace(QRegExp("\n"), "<br/>");
}

void Interpretor::HighlightWord(QString& output, const QString& word) {
    output = output.replace(word, "<b><font color=" + color + "> " + word+ "</font></b>", Qt::CaseInsensitive);
}



QString Interpretor::Execute(Command* cmd, const QString &command_, QStringList &arguments_, const QString &working_directory_) {
    QString res = cmd->Execute(command_, arguments_, working_directory_);
    ConvertNewLineToHTML(res);
    if(cmd->ShouldHighlight())
        HighlightWord(res, arguments_.back());
    return res;
}
