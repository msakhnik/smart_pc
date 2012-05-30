/* 
 * File:   AnnTrain.h
 * Author: morwin
 *
 * Created on 17 травня 2012, 10:13
 */

#pragma once

#include<fann.h>
#include <vector>
#include<cstring>
#include<string>
#include <fstream>

class cAnnTrain {
public:
    cAnnTrain(const std::vector<int> &);
    ~cAnnTrain();
    bool TrainNeiro();
    bool ClearTrainFiles();
private:
    unsigned int _num_input ;
    unsigned int _num_output;
    unsigned int _num_layers;
    unsigned int _num_neurons_hidden;
    float _desired_error;
    unsigned int _max_epochs;
    unsigned int _epochs_between_reports;
    unsigned int _count;

    struct fann *sAnn;
    std::string _train_file;
    std::string _save_file;

    std::vector<int> _data;

    void _DoReadlink();
    bool _SaveData();
    bool _RecordData();
    template<class T> bool _InitFile(T&, bool);
    
    bool _RecordHead();
    bool _GetHeaderData();
};