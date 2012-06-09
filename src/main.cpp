#include <iostream>
#include <getopt.h>
#include <cstring>
#include <vector>

#include "HandDetector.h"
#include "AnnTrain.h"
#include "CommandProcess.h"

using namespace std;

static char const* _Basename(char const* fname)
{
    char const* res = strrchr(fname, '/');
    return res ? res + 1 : fname;
}

static void _ReadHelp(const char *progname)
{
    cout << "Smart_pc\n\n"
            "Synopsis:\n"
            "  " << progname << " [options] file\n\n"
            "Options:\n"
            "  -t,--train\t\tTrain you perceptron\n"
            "  -c,--clear-train\t\tClear you train file\n"
            "  -r,--answer\t\tRun proccess and getcommand\n"
            "  -h,--help\t\tThis is help message\n\n"
            "Example:\n"
            << endl;
}

bool _Finish()
{
    char c;
    cerr << "Continue train?(y/n)" << endl;
    while (true)
    {
        cin >> c;
        if (c == 'y' || c == 'Y')
            return false;
        else if (c == 'n' || c == 'N')
            return true;
        cerr << "\"y\" or \"n\"!" << endl;
    }

    return false;
}

void _TrainAnn()
{
    cCommandProcess command;
    command.Init();
    if (command.GetArraySize() == 0)
    {
        cerr << "Command list is empty" << endl;
        return;
    }
    cHandDetector detector;
    cAnnTrain train(command.GetArraySize());
    while (true)
    {
        if (!detector.Start())
            break;
        vector<int> myvect;
        myvect = detector.GetImageArray();
        cerr << "\n\nYou hand was detected\n\n" << endl;
        command.ShowCommands();
        while (true)
        {
            cerr << "Please enter the number of command in range [1 .. "
                    << command.GetArraySize() << "]" << endl;
            int answer;
            cin >> answer;
            if (command.ValidateInputData(answer))
            {
                train.SaveData(myvect, answer);
                break;
            }
        }
        detector.ReleaseData();
        if (_Finish())
        {
            train.TrainNeiro();
            break;
        }
        else
            continue;
    }
}

void _ClearTrainFile()
{
    cCommandProcess command;
    command.Init();
    cAnnTrain train(command.GetArraySize());
    if (train.ClearTrainFiles())
        cerr << "Train faile was saccessfuly rewrited" << endl;
}

void _GetAnswer()
{
    cCommandProcess command;
    command.Init();
    if (command.GetArraySize() == 0)
    {
        cerr << "Command list is empty, please add command " << endl;
        return;
    }
    cHandDetector detector;
    cAnnTrain train(command.GetArraySize());
    if (detector.Start())
    {
        vector<int> myvect;
        myvect = detector.GetImageArray();
        cerr << "\n\nYou hand was detected\n\n" << endl;
        command.ExecCommand(train.GetAnswer(myvect));
    }
}

void _ClearCommandList()
{
    cCommandProcess command;
    command.Init();
    command.ClearCommandFile();
}

void _AddCommand()
{
    string line;
    cerr << "Enter command: ";
    cin >> line;
    cCommandProcess command;
    command.Init();
    command.AddCommand(line);
}

int main(int argc, char** argv)
{
    char const* progname = _Basename(argv[0]);

    while (true)
    {
        static struct option long_options[] = {
            { "train", no_argument, 0, 't'},
            { "add", no_argument, 0, 'a'},
            { "run", no_argument, 0, 'r'},
            { "clear-train", no_argument, 0, 'c'},
            { "list-remove", no_argument, 0, 'l'},
            { "help", no_argument, 0, 'h'},
            { 0, 0, 0, 0}
        };

        int option_index = 0;

        int c = getopt_long(argc, argv, "taclrh",
                            long_options, &option_index);

        if (c == -1)
            break;

        switch (c)
        {
        case 'h':
            _ReadHelp(progname);
            return 0;

        case 't':
            _TrainAnn();
            break;
        case 'r':
            _GetAnswer();
            break;
        case 'a':
            _AddCommand();
            break;
        case 'c':
            _ClearTrainFile();
            break;
        case 'l':
            _ClearCommandList();
            break;

        default:
            cerr << "Unknown option '" << c << "'" << endl;
            return 1;
        }
    }
    return 0;
}