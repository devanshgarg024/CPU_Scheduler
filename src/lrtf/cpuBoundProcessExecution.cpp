#include "../processService.hpp"
#include "queueService.hpp"
#include <memory>
#include <iostream>
#include "cpuBoundProcessExecution.hpp"
#include <thread>
using namespace std;

namespace lrtf{

    void executeCpuBoundProcess(Process* process, QueueService &q) {
        const int executedTime=min(process->cpu_burst_time,1);
        std::this_thread::sleep_for(std::chrono::milliseconds(executedTime));
        
        process->cpu_burst_time -=executedTime;
    
        if (process->cpu_burst_time > 0) {
            q.push_element(process);
        }
    }
}
