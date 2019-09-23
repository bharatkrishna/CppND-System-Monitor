#include<iostream>

#include "processor.h"
#include "linux_parser.h"

using std::string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<string> cpu_utilizations = LinuxParser::CpuUtilization(); 
    float total_cpu_time;
    float total_cpu_idle_time = stof(cpu_utilizations.at(3)) + stof(cpu_utilizations.at(4));

    for (int i=0; i<8; i++) {
      total_cpu_time += stof(cpu_utilizations.at(i));
    }

    float total_cpu_usage_time = total_cpu_time - total_cpu_idle_time;
    float total_cpu_util_pct = (total_cpu_usage_time / total_cpu_time) * 100;

    return total_cpu_util_pct;
}