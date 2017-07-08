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

