#include <gtest/gtest.h>
#include <interpretor.h>


class InterpretorTest: public ::testing::Test
{
public:
    void Initialize(Command* cmd_, QString command_name_, QStringList arguments_, QString working_directory_) {
        interpretor = new Interpretor("blue");
        cmd = cmd_;
        command_name = command_name_;
        arguments = arguments_;
        working_directory = working_directory_;
    }

    void Initialize(QString color) {
        interpretor = new Interpretor(color);
    }
    Command* cmd;
    QString command_name;
    Interpretor* interpretor;
    QStringList arguments;
    QString working_directory;

};



TEST_F(InterpretorTest, grep) {
    Initialize(new GrepCommand(), "grep", QStringList{"-iRn", "azertyuiop"}, "/home/pierre/Desktop");
    QString res = interpretor->Execute(cmd, command_name, arguments, working_directory);
    ASSERT_TRUE((res.compare("") == 0));
}


TEST_F(InterpretorTest, whoami) {
    Initialize(new OtherCommand(), "whoami", QStringList{}, "/home/pierre");
    QString res = interpretor->Execute(cmd, command_name, arguments, working_directory);
    ASSERT_TRUE((res.compare("pierre<br/>") == 0));
}

TEST_F(InterpretorTest, uname) {
    Initialize(new OtherCommand(), "uname", QStringList{}, "/home/pierre");
    QString res = interpretor->Execute(cmd, command_name, arguments, working_directory);
    ASSERT_TRUE((res.compare("Linux<br/>") == 0));
}

TEST_F(InterpretorTest, highlightWord) {
    Initialize("blue");
    QString test_str = "lacazette ol tolisso";
    interpretor->HighlightWord(test_str, "ol");
    ASSERT_TRUE((test_str.compare("lacazette <b><font color=blue> ol </font></b> t<b><font color=blue> ol </font></b>isso") == 0));
}


TEST_F(InterpretorTest, convertNewLineToHTML) {
    Initialize("blue");
    QString test_str = "lacazette \nol \ntolisso";
    interpretor->ConvertNewLineToHTML(test_str);
    ASSERT_TRUE((test_str.compare("lacazette <br/>ol <br/>tolisso") == 0));
}
