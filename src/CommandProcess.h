/* 
 * File:   CommandProcess.h
 * Author: morwin
 *
 * Created on 30 травня 2012, 13:59
 */

#pragma once

#include <vector>
#include <string>

class cCommandProcess {
public:
    cCommandProcess();
    ~cCommandProcess();
private:
    std::vector<std::string>_commands;
};