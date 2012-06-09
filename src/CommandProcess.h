/* 
 * File:   CommandProcess.h
 * Author: morwin
 *
 * Created on 30 травня 2012, 13:59
 */

#pragma once

#include <vector>
#include <string>
#include <fstream>

class cCommandProcess
{
public:
    cCommandProcess();
    ~cCommandProcess();
    bool Init();
    void ShowCommands();
    std::string GetCommand(int);
    bool ValidateInputData(unsigned int);
    bool AddCommand(std::string);
    void ExecCommand(unsigned int);
    void ClearCommandFile();

    unsigned int GetArraySize() { return _commands.size(); }
private:
    bool _InitFile();
    std::string _DoReadlink();
    std::vector<std::string>_commands;

    std::string _file_name;
};