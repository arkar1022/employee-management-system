#pragma once // Include guard to ensure the header is included only once

#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
class Logger
{
public:
    // Template function for logging messages to a file and console
    template <typename... Args>
    static void logMsg(const Args &...args)
    {
        // Open the debug file in append mode
        ofstream logfile(msDebugFileName, ios_base::app);
        // Check if file opening fails
        if (logfile.fail())
        {
            cerr << "Unable to open debug file!" << endl;
            return;
        };
        // Log the provided arguments to the file
        ((logfile << args), ...);
        logfile << endl;

        // Log the same arguments to the console
        ((cout << args), ...);
        cout << endl;
    }

private:
    // File name for the debug logMsg
    static const string msDebugFileName;
};

// Initialize the static member with the debug logMsg file name
// const string Logger::msDebugFileName = "debugLog.txt";


// Preprocessor Directive
//#define DEBUG_MODE // Enable debug mode

#ifdef DEBUG_MODE // If debug mode is on

// Macro for logging messages, using the current function name
#define logMsg(...) Logger::logMsg(__func__, "(): ", __VA_ARGS__);

// If debug mode is off, define an empty logMsg macro
#else
#define logMsg(...)

#endif


