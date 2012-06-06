/* 
 * File:   CommandProcess.cpp
 * Author: morwin
 * 
 * Created on 30 травня 2012, 13:59
 */

#include "CommandProcess.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <bits/stl_bvector.h>

using namespace std;

cCommandProcess::cCommandProcess() :
_file_name(_DoReadlink())
{
}

cCommandProcess::~cCommandProcess()
{
}

bool cCommandProcess::Init()
{
    ifstream fileCommand;
    fileCommand.open(_file_name.c_str());
    if (!fileCommand.is_open())
    {
        cerr << "Command file not found" << endl;
        return false;
    }

    string line;
    while (fileCommand.good())
    {
        getline(fileCommand, line);
        if (line.length() > 0)
            _commands.push_back(line);
    }
    return true;
}

string cCommandProcess::_DoReadlink()
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
    s = "data/commands.data";
    line += s;
    return line.c_str();
}

void cCommandProcess::ShowCommands()
{
    vector<string>::iterator it;
    for (unsigned int i = 0; i < _commands.size(); i++)
        cerr << (i + 1) << ". " << _commands[i] << endl;
}

string cCommandProcess::GetCommand(int number)
{
    return _commands[number - 1];
}

bool cCommandProcess::ValidateInputData(unsigned int number)
{
    return (number > 0 && number <= _commands.size());
}

bool cCommandProcess::AddCommand(string command)
{
    ofstream fileCommand;
    fileCommand.open(_file_name.c_str(), ios::app);
    if (!fileCommand.is_open())
    {
        cerr << "Command file not found" << endl;
        return false;
    }
    fileCommand << "\n" << command;
    fileCommand.close();
    return true;
}