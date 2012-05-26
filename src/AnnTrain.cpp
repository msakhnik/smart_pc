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

using namespace std;

cAnnTrain::cAnnTrain() : 
                _num_input(2),
                _num_output(1),
                _num_layers(3),
                _num_neurons_hidden(3),
                _desired_error(0.001),
                _max_epochs(500000),
                _epochs_between_reports(1000)
{
    _DoReadlink();
    
    sAnn = fann_create_standard(_num_layers, _num_input, _num_neurons_hidden, _num_output);

    fann_set_activation_function_hidden(sAnn, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(sAnn, FANN_SIGMOID_SYMMETRIC);
}

cAnnTrain::~cAnnTrain() {
    cerr << "Destructor" << endl;
    fann_destroy(sAnn);
}
    
bool cAnnTrain::TrainNeiro(const vector<int> & data)
{
    cerr << "train" << endl;
    copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
    fann_train_on_file(sAnn, _train_file.c_str(), _max_epochs, _epochs_between_reports, _desired_error);
    fann_save(sAnn, _save_file.c_str());
    return true;
}

void cAnnTrain::_DoReadlink()
{
    char buf[256];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf));
    vector<string> temp;
    string line;
    line = buf;
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