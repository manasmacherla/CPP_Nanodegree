#include <string>
#include <sstream>
#include <stdio.h>
#include "format.h"

using std::string;
using std::ostringstream;

string Format::ElapsedTime(long seconds[[maybe_unused]]) { 
    char output[10];
    int hours = seconds/3600;
    int minutes = (seconds%3600)/60;
    int secs = seconds%60;

    sprintf(output, "%.2d:%.2d:%.2d", hours, minutes, secs);

    return output; }