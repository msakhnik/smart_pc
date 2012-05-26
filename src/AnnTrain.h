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

class cAnnTrain {
public:
    cAnnTrain();
    ~cAnnTrain();
    
    
    bool TrainNeiro(const std::vector<int> &);
private:
    unsigned int _num_input ;
    unsigned int _num_output;
    unsigned int _num_layers;
    unsigned int _num_neurons_hidden;
    float _desired_error;
    unsigned int _max_epochs;
    unsigned int _epochs_between_reports;

    struct fann *sAnn;
    std::string _train_file;
    std::string _save_file;

    void _DoReadlink();
};