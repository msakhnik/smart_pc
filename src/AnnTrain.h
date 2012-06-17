//
// AnnTrain.h
//
//     Created: 16.06.2012
//     Author: Misha Sakhnik
//
// This file is part of SmartPc.
//
// SmartPc is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Asf Player License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SmartPc is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SmartPc.  If not, see <http://www.gnu.org/licenses/>

#pragma once

#include "fann.h"
#include <vector>
#include<cstring>
#include<string>
#include <fstream>

/**
@brief Class for work with artificial neural network
* 
* Provides teaching neural network and getting result by input data
*/
class cAnnTrain
{
public:
/**
@brief Construct. Init additional variables
@param output Number output neirons
@param size Number input neirons
*/
    cAnnTrain(unsigned int output, unsigned int size);
 /**
@brief Destructor. Destroy fann structure
*/
    ~cAnnTrain();
 /**
@brief Teaching network. Getting data from "../data/xor.data" file
 and  recording in "../data/xor_float.net" file
@return True if recording was successfully
*/
    bool TrainNeiro();
/**
@brief Clear files "../data/xor.data" and "../data/xor_float.net"
@return True if clearing was successfully
*/
    bool ClearTrainFiles();
/**
@brief Get answer from neural network.
@param data Array with data
@return Positive number if successfully and -1 if wrong
*/
    int GetAnswer(const std::vector<int> & data);
/**
@brief Save data in "../data/xor.data"
@param data Array with data
 @param answer Positive number with true answer
@return True if data saved successfully
*/
    bool SaveData(const std::vector<int> & data, unsigned int answer);
private:
    unsigned int _num_input;
    unsigned int _num_output;
    unsigned int _count;

    struct fann *sAnn;
    std::string _train_file;
    std::string _save_file;

    std::vector<int> _data;
    std::vector<int> _answer;

    bool _RecordData();
    template<class T> bool _InitFile(T&, bool);

    bool _RecordHead();
    bool _GetHeaderData();
    bool _InitPerceptron();
    int _GetMaxType(fann_type *);
};