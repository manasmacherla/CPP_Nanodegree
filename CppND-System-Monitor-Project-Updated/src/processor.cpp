#include "processor.h"
#include <linux_parser.h>

using std::stoi;
using std::string;

float Processor::Utilization() { 
  string cpu, user, nice, system, idle, iowait, irq, softirq, steal, guest,guest_nice;
  string line;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
  }

  // Method from https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
  int const IdleTime = stoi(idle) + stoi(iowait);
  int const NonIdleTime = stoi(user) + stoi(nice) + stoi(system) + stoi(irq) + stoi(softirq) + stoi(steal);
  float const TotalTime = IdleTime + NonIdleTime;
  
  return (TotalTime - IdleTime)/TotalTime;
 }