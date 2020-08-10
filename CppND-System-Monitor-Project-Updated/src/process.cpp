#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid) {}

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
// Followed the procedure from 
// https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
float Process::CpuUtilization() { 
  float TotalTime = LinuxParser::ActiveJiffies(Pid());
  float UpTime = LinuxParser::UpTime();                 // In seconds
  float seconds_active = UpTime - (Process::UpTime() / sysconf(_SC_CLK_TCK));  // In seconds
  float Cpu_Usage = (TotalTime / sysconf(_SC_CLK_TCK)) / seconds_active;  // In seconds
  return Cpu_Usage;
 }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return stol(LinuxParser::Ram(pid_)) > stol(LinuxParser::Ram(a.pid_)); }