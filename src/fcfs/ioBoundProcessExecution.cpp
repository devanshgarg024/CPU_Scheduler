#include "ioBoundProcessExecution.hpp"
#include <thread>


namespace fcfs{
    
    void handleIoBoundProcess(Process* process, int ioWaitTime, QueueService& q) {
        // Simulate IO wait
        std::this_thread::sleep_for(std::chrono::milliseconds(ioWaitTime));
        
        // Deduct CPU burst time (1 time slice after IO)
        const int executedTime = process->cpu_burst_time;  // Same as CPU time slice
        std::this_thread::sleep_for(std::chrono::milliseconds(executedTime));
        
        process->cpu_burst_time =0;
    
    }
}