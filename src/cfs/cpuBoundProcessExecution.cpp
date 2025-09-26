#include "../processService.hpp"
#include "queueService.hpp"
#include <memory>
#include <thread>
#include <iostream>
#include "cpuBoundProcessExecution.hpp"

constexpr int NICE_0_LOAD = 1024;  // Standard Linux value

namespace cfs{
    double weightFunction(int priority) {
        return NICE_0_LOAD / (priority + 1);  // +1 to avoid division by zero
    }
    
    void executeCpuBoundProcess(Process* process, int timeSlice, QueueService &q) {
        const int executedTime = std::min(timeSlice, process->cpu_burst_time);
    
        // Simulate the passage of time that the process runs on the CPU.
        std::this_thread::sleep_for(std::chrono::milliseconds(executedTime));
        
        process->cpu_burst_time -= executedTime;
        
        const double weight = weightFunction(process->priority);
        process->vruntime += (executedTime * NICE_0_LOAD) / weight;
        
        if (process->cpu_burst_time > 0) {
            q.push_element(process);
        }
    }

}
