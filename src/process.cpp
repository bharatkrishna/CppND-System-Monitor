#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid) {}

// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { return cpu_; }

void Process::CalculateCpuUtilization() {
  long active_jiffies = LinuxParser::ActiveJiffies(pid_);
  long system_jiffies = LinuxParser::Jiffies();

  long diff_active_jiffies{active_jiffies - prev_active_jiffies_};
  long diff_system_jiffies{system_jiffies - prev_total_jiffies_};

  cpu_ = static_cast<float>(diff_active_jiffies) / diff_system_jiffies;
  prev_active_jiffies_ = active_jiffies;
  prev_total_jiffies_ = system_jiffies;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return CpuUtilization() < a.CpuUtilization();
}