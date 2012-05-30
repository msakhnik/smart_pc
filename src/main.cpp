#include <iostream>
#include <getopt.h>
#include <cstring>
#include <vector>

//#include "HandDetector.h"
#include "AnnTrain.h"

using namespace std;

static char const* _Basename(char const* fname) {
    char const* res = strrchr(fname, '/');
    return res ? res + 1 : fname;
}

static void _ReadHelp(const char *progname) {
    cout << "Smart_pc\n\n"
            "Synopsis:\n"
            "  " << progname << " [options] file\n\n"
            "Options:\n"
            "  -s,--some\t\tSet scale\n"
            "  -h,--help\t\tThis help message\n\n"
            "Example:\n"
            "  " << progname << " example/example1.asf\n"
            "  " << progname << " -f example/example2.asf\n"
            "  " << progname << " -s2 example/example3.asf\n"
            "  this creates a file test.asf in the directory 'example'"
            << endl;
}

int main(int argc, char** argv) {
    char const* progname = _Basename(argv[0]);
    while (true) {
        static struct option long_options[] = {
            { "some option", required_argument, 0, 's'},
            { "help", no_argument, 0, 'h'},
            { 0, 0, 0, 0}
        };

        int option_index = 0;

        int c = getopt_long(argc, argv, "fr:s:h",
                long_options, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 'h':
                _ReadHelp(progname);
                return 0;

            case 's':
                cerr << "Some option" << endl;
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
     * */
    vector<int> array(10, 0);
    array.push_back(1);
    cAnnTrain train(array);
    if (train.TrainNeiro())
    {
        cerr << "Good train!!!" << endl;
    }

//    train.ClearTrainFiles();

    return 0;
}