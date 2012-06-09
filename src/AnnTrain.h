/* 
 * File:   AnnTrain.h
 * Author: morwin
 *
 * Created on 17 травня 2012, 10:13
 */

#pragma once

#include "fann.h"
#include <vector>
#include<cstring>
#include<string>
#include <fstream>

class cAnnTrain
{
public:
    cAnnTrain(unsigned int);
    cAnnTrain(const std::vector<int> &, unsigned int);
    cAnnTrain();
    ~cAnnTrain();
    bool TrainNeiro();
    bool ClearTrainFiles();
    int GetAnswer(const std::vector<int> &);
    bool SaveData(const std::vector<int> &, unsigned int);
private:
    unsigned int _num_input;
    unsigned int _num_output;
    unsigned int _count;

    struct fann *sAnn;
    std::string _train_file;
    std::string _save_file;

    std::vector<int> _data;
    std::vector<int> _answer;

    void _DoReadlink();
    bool _RecordData();
    template<class T> bool _InitFile(T&, bool);

    bool _RecordHead();
    bool _GetHeaderData();
    bool _InitPerceptron();
    int _GetMaxType(fann_type *);
};