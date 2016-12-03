/*
 * CommandLineWrapper.hpp
 * Copyright (C) 2016 cknapp <cknapp@dhcp-39-4-22.dhcpint.csulb.edu>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef COMMANDLINEWRAPPER_HPP
#define COMMANDLINEWRAPPER_HPP

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

// execute a string, block, and return the output.
std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}

#endif /* !COMMANDLINEWRAPPER_HPP */
