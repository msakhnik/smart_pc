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
            "  -a,--add\t\tAdd command\n"
            "  -s,--search\t\tRun detector and search result\n"
            "  -r,--rewrite\t\tRewrite train files to default\n"
            "  -c,--clear\t\tClear command list file\n"
            "  -l,--list\t\tShow command list\n"
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
    cerr << detector.GetImageArray().size() << endl;
    cAnnTrain train(command.GetArraySize(), detector.GetImageArray().size());
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
    cHandDetector detector;
    command.Init();
    cAnnTrain train(command.GetArraySize(), detector.GetImageArray().size());
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
    cAnnTrain train(command.GetArraySize(), detector.GetImageArray().size());
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

void _ShowCommandList()
{
    cCommandProcess command;
    command.Init();
    command.ShowCommands();
}

int main(int argc, char** argv)
{
    char const* progname = _Basename(argv[0]);

    while (true)
    {
        static struct option long_options[] = {
            { "train", no_argument, 0, 't'},
            { "add", no_argument, 0, 'a'},
            { "search", no_argument, 0, 's'},
            { "rewrite", no_argument, 0, 'r'},
            { "clear", no_argument, 0, 'c'},
            { "list", no_argument, 0, 'l'},
            { "help", no_argument, 0, 'h'},
            { 0, 0, 0, 0}
        };

        int option_index = 0;

        int c = getopt_long(argc, argv, "tasrclh",
                            long_options, &option_index);

        if (c == -1)
        {
//            _ReadHelp(progname);
            break;
        }

        switch (c)
        {
        case 't':
            _TrainAnn();
            break;
        case 'a':
            _AddCommand();
            break;
        case 's':
            _GetAnswer();
            break;
        case 'r':
            _ClearTrainFile();
            break;
        case 'c':
            _ClearCommandList();
            break;
        case 'l':
            _ShowCommandList();
            break;
        case 'h':
            _ReadHelp(progname);
            return 0;

        default:
            cerr << "Unknown option '" << c << "'" << endl;
            return 1;
        }
    }
    return 0;
}