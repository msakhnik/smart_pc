//
// CommandProccess.cpp
//
//     Created: 16.06.2012
//      Author: Misha Sakhnik
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

#include "CommandProcess.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <bits/stl_bvector.h>
#include <stdlib.h>

using namespace std;

cCommandProcess::cCommandProcess() :
_file_name("../data/commands.data")
{
}

bool cCommandProcess::Init()
{
    ifstream fileCommand;
    fileCommand.open(_file_name.c_str());
    if (!fileCommand.is_open())
    {
        cerr << "File " << _file_name <<  " not found" << endl;
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

void cCommandProcess::ShowCommands()
{
    vector<string>::iterator it;
    for (it = _commands.begin(); it != _commands.end(); ++it)
        cerr <<  distance(_commands.begin(), it) + 1 << ". " << *it << endl;
}

string cCommandProcess::GetCommand(int position) const
{
    return _commands[position - 1];
}

bool cCommandProcess::ValidateInputData(unsigned int position) const
{
    return (position > 0 && position <= _commands.size());
}

bool cCommandProcess::AddCommand(string command)
{
    ofstream fileCommand;
    fileCommand.open(_file_name.c_str(), ios::app);
    if (!fileCommand.is_open())
    {
        cerr << "File " << _file_name <<  " not found" << endl;
        return false;
    }
    fileCommand << "\n" << command;
    fileCommand.close();
    return true;
}

void cCommandProcess::ExecCommand(unsigned int command)
{
    if (system(_commands[command -1].c_str()))
        cerr << "Cannot run " << _commands[command - 1] << endl;
}

void cCommandProcess::ClearCommandFile()
{
    ofstream fileRecord;
    fileRecord.open(_file_name.c_str());
    if (!fileRecord.is_open())
    {
        cerr << "File " << _file_name <<  " not found" << endl;
    }
    fileRecord << "";
    fileRecord.close();
}