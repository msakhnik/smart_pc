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
            "  -h,--help\t\tThis is help message\n\n"
            "Example:\n"
            << endl;
}

bool _Finish()
{
    char c;
    cerr << "Do you want finish train?(y/n)" << endl;
    while (true)
    {
        cin >> c;
        if (c == 'y' || c == 'Y')
            return true;
        else if (c == 'n' || c == 'N')
            return false;
        cerr << "Please select \"y\" or \"n\"" << endl;
    }

    return false;
}

void _TrainAnn()
{
    while (true)
    {
        cHandDetector detector;
        if (detector.Start())
        {
            vector<int> myvect;
            myvect = detector.GetImageArray();
            cerr << "\n\nYou hand was detected\n\n" << endl;
            cCommandProcess command;
            command.Init();
            command.ShowCommands();
            while (true)
            {
                cerr << "Please enter the number of command in range [1 .. "
                        << command.GetArraySize() << "]" << endl;
                int input;
                cin >> input;
                if (command.ValidateInputData(input))
                {
                    cAnnTrain train(myvect, command.GetArraySize());
                    train.TrainNeiro(input);
                    break;
                }
            }
        }
        if (_Finish())
            break;
        else
            continue;
    }
}

void _ClearTrainFile()
{
    cerr << "in clear func" << endl;
    cAnnTrain ann;
    ann.ClearTrainFiles();
}

void _GetAnswer()
{
    cHandDetector detector;
    if (detector.Start())
    {
        vector<int> myvect;
        myvect = detector.GetImageArray();
        cerr << "\n\nYou hand was detected\n\n" << endl;
        cAnnTrain check(myvect);
        check.GetAnswer();
    }
}

int main(int argc, char** argv)
{
    char const* progname = _Basename(argv[0]);
    while (true)
    {
        static struct option long_options[] = {
            { "train", no_argument, 0, 't'},
            { "answer", no_argument, 0, 'a'},
            { "clear-train", no_argument, 0, 'c'},
            { "help", no_argument, 0, 'h'},
            { 0, 0, 0, 0}
        };

        int option_index = 0;

        int c = getopt_long(argc, argv, "tach",
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
        case 'a':
            _GetAnswer();
            break;
        case 'c':
            _ClearTrainFile();
            break;

        default:
            cerr << "Unknown option '" << c << "'" << endl;
            return 1;
        }
    }

    //cHandDetector detector;
    /*if (detector.Start())
    {
        vector<int>  myvect;
        myvect = detector.GetImageArray();

        int i = 0;
        for(std::vector<int>::iterator j=myvect.begin(); j!=myvect.end(); ++j)
        {
            cout << (*j );
            if (i == 99)
            {
                cout << endl;
                i = 0;
                continue;
            }
            i++;
        }l
     * 
     * 
     * 
     * 
     * 
 

    }
    vector<int> array(10, 0);
    array.push_back(1);
    cAnnTrain train(array);
    if (train.TrainNeiro())
    {
        cerr << "Good train!!!" << endl;
    }

    //    train.ClearTrainFiles();

    cCommandProcess command;
    if (!command.Init())
        return false;
    else {
        t = 1
        command.ValidateInputData(t);
        command.GetCommand(t);
         
        command.AddCommand("geany");
        command.ShowCommands();
    }
     */
    return 0;
}