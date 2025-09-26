#include "../processService.hpp"
#include "queueService.hpp"
#include <memory>
#include <iostream>
#include "cpuBoundProcessExecution.hpp"
#include <thread>

namespace fcfs{

    void executeCpuBoundProcess(Process* process, QueueService &q) {
        const int executedTime = process->cpu_burst_time;
        std::this_thread::sleep_for(std::chrono::milliseconds(executedTime));
        
        process->cpu_burst_time =0;
        
    }
}
