/* 
 * File:   AnnTrain.cpp
 * Author: morwin
 * 
 * Created on 17 травня 2012, 10:13
 */

#include "AnnTrain.h"
#include<iostream>
#include "floatfann.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<iterator>
#include<algorithm>
#include <sstream>
#include <fstream>
#include <ostream>

using namespace std;

cAnnTrain::cAnnTrain(unsigned int output) :
_num_input(10000),
_num_output(output),
_count(0)
{
    //    copy(_answer.begin(), _answer.end(), ostream_iterator<int>(cout, " "));
    _DoReadlink();

}

cAnnTrain::cAnnTrain()
{
    _DoReadlink();
}

cAnnTrain::cAnnTrain(const vector<int> & data) :
    _num_input(10000),
    _data(data)
{
    _DoReadlink();
}

cAnnTrain::~cAnnTrain()
{
    cerr << "Destructor" << endl;
    fann_destroy(sAnn);
}

bool cAnnTrain::TrainNeiro()
{
    //    copy(_answer.begin(), _answer.end(), ostream_iterator<int>(cout, " "));
    float desired_error = 0.001;
    unsigned int max_epochs = 500000;
    unsigned int epochs_between_reports = 1000;
    if (!_GetHeaderData())
        return false;
    _InitPerceptron();
//    if (!_SaveData())
//        return false;
    //    copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
    fann_train_on_file(sAnn, _train_file.c_str(), max_epochs, epochs_between_reports, desired_error);
    fann_save(sAnn, _save_file.c_str());
    return true;
}

void cAnnTrain::_DoReadlink()
{
    char buf[256];
    if (!readlink("/proc/self/exe", buf, sizeof (buf)))
        cerr << "Cannot to read path to file" << endl;
    vector<string> temp;
    string line(buf);
    istringstream is(line);
    string s;
    while (getline(is, s, '/'))
        temp.push_back(s.c_str());
    line = "";
    for (unsigned int i = 0; i < temp.size() - 2; i++)
        line += temp[i] + "/";
    s = "/data/xor.data";
    _train_file = line + s;
    s = "/data/xor_float.net";
    _save_file = line + s;
}

bool cAnnTrain::SaveData(const vector<int> & data, unsigned int answer)
{
    _data = data;
    _answer.clear();
    _answer.resize(_num_output, 0);
    _answer[answer - 1] = 1;
    if (!_GetHeaderData())
        return false;
    if (!_RecordHead())
        return false;
    if (!_RecordData())
        return false;
    //    copy(_data.begin(), _data.end(), ostream_iterator<int>(cout, " "));
    cerr << "Data is successfully stored" << endl;
    return true;
}

bool cAnnTrain::_RecordData()
{
    ofstream fileRecord;
    if (!_InitFile(fileRecord, true))
        return false;
    for (unsigned int i = 0; i < _data.size(); ++i)
        fileRecord << _data[i] << " ";
    fileRecord << "\n";
    for (unsigned int i = 0; i < _answer.size(); ++i)
        fileRecord << _answer[i] << " ";
    fileRecord << "\n";

    fileRecord.close();
    return true;
}

bool cAnnTrain::_RecordHead()
{
    fstream ss;
    if (!_InitFile(ss, false))
        return false;
    ss.seekg(0);
    ostringstream out;
    ++_count;
    out << _count << " " << _num_input << " " << _num_output;
    string line = out.str();
    while (line.length() < 20)
        line += " ";
    ss << line << endl;
    ss.close();
    return true;
}
//TODO: Create template for checking file

bool cAnnTrain::_GetHeaderData()
{
    ifstream final_file;
    if (!_InitFile(final_file, false))
        return false;
    string line;
    char* pch;
    getline(final_file, line);
    final_file.close();
    char *tmp_str = const_cast<char*> (line.c_str());
    pch = strtok(tmp_str, " ");
    _count = atoi(pch);
    pch = strtok(NULL, " ");
    _num_input = atoi(pch);
    pch = strtok(NULL, " ");
    unsigned int output = atoi(pch);
    if (output != _num_output)
    {
        ClearTrainFiles();
        _num_output = output;
    }
    pch = strtok(NULL, " ");
    if (pch == NULL)
        return true;
    else
    {
        cerr << "Train file is failed" << endl;
        return false;
    }
}

bool cAnnTrain::ClearTrainFiles()
{
    ofstream fileRecord;
    if (!_InitFile(fileRecord, false))
        return false;
    fileRecord.open(_train_file.c_str());
    fileRecord << "";
    fileRecord.close();
    _count = -1;
    _RecordHead();
    return true;
}

template<class T> bool cAnnTrain::_InitFile(T & file, bool add)
{
    if (add)
        file.open(_train_file.c_str(), ios::app);
    else
        file.open(_train_file.c_str());
    if (!file.is_open())
    {
        cerr << "Cannot create or open file" << endl;
        return false;
    }
    return true;
}

bool cAnnTrain::_InitPerceptron()
{
    unsigned int num_layers = 3;
    unsigned int num_neurons_hidden = 3;
    sAnn = fann_create_standard(num_layers, _num_input, num_neurons_hidden, _num_output);

    fann_set_activation_function_hidden(sAnn, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(sAnn, FANN_SIGMOID_SYMMETRIC);

    return true;
}

int cAnnTrain::GetAnswer()
{
    fann_type *calc_out;
    fann_type input[_data.size()];
    sAnn = fann_create_from_file(_save_file.c_str());
    for (unsigned int i = 0; i < _data.size(); ++i)
        input[i] = _data[i];

    calc_out = fann_run(sAnn, input);
//    _GetMaxType(calc_out);
    cerr << calc_out[0] << endl;
    cerr << calc_out[1] << endl;
    cerr << calc_out[2] << endl;
    cerr << calc_out[3] << endl;

    return 1;
}

int cAnnTrain::_GetMaxType(fann_type * data)
{
    float max = 0.0;
    unsigned int pos = 0; 
    for (unsigned int i = 0; i < 10000; ++i)
        if (data[i] > max)
        {
            max = data[i];
            pos = i;
        }
    
    return 1;
}