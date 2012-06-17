//
// CommandProccess.h
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

#pragma once

#include <vector>
#include <string>
#include <fstream>

/**
@brief Class for work with commands
* 
* Provides management the commands lists.
* Can add, remove, get list and run command.
*/
class cCommandProcess
{
public:
/**
@brief Construct. Set the _file_name
*/
    cCommandProcess();
 /**
@brief Initialization data. 
* 
* Opening and reading data and filled _command array.
@return Return false if file not found.
True if file found and _command array successfully filled
*/
    bool Init();
 /**
@brief Show commands list. 
*/
    void ShowCommands();
/**
@brief Get command by position. 
@param position Command position in _commands array
@return command name
*/
    std::string GetCommand(int position) const;
/**
@brief Get Validate input data. 
@param position Command position in _commands array
@return Return false if position out of the range
*/
    bool ValidateInputData(unsigned int position) const;
/**
@brief Add new command. 
@param command Command name
@return Return true if command was successful added
*/
    bool AddCommand(std::string command);
 /**
@brief Execute command. 
@param command Command name
*/
    void ExecCommand(unsigned int command);
 /**
@brief Clear command file
*/
    void ClearCommandFile();
/**
@brief Get count of commands. 
@return return count of elements array
 */
    unsigned int GetArraySize() const { return _commands.size(); }
private:
    bool _InitFile();
    std::vector<std::string>_commands;

    std::string _file_name;
};