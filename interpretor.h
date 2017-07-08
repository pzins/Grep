#ifndef INTERPRETOR_H
#define INTERPRETOR_H
#include <command.h>
#include <QStringList>

class Interpretor
{
private:
    QString color;
public:
    Interpretor(const QString& color_);
    QString Execute(Command* cmd, const QString& command_, QStringList &arguments_, const QString& working_directory_);

    void HighlightWord(QString& output, const QString& word);
    void ConvertNewLineToHTML(QString& output);

};

#endif // INTERPRETOR_H
