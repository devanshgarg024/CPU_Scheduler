#include "ioBoundProcessExecution.hpp"
#include <thread>
using namespace std;

namespace rr{

    void handleIoBoundProcess(Process* process, int ioWaitTime,int time_quanta, QueueService& q) {
        // Simulate IO wait
        std::this_thread::sleep_for(std::chrono::milliseconds(ioWaitTime));
        
        // Deduct CPU burst time (1 time slice after IO)
        const int executedTime = min(process->cpu_burst_time,time_quanta);  // Same as CPU time slice
        std::this_thread::sleep_for(std::chrono::milliseconds(executedTime));
        
        process->cpu_burst_time -=executedTime;
    
        if (process->cpu_burst_time > 0) {
            q.push_element(process);
        }
    
    }
}