#ifndef SJF_HPP
#define SJF_HPP

#include <vector>
#include <ctime>
#include "../processService.hpp"
#include "../processLog.hpp"
#include "queueService.hpp"
#include "cpuBoundProcessExecution.hpp"
#include "ioBoundProcessExecution.hpp"

namespace sjf{

    class schedular {
    private:
        void createProcessLog(std::vector<ProcessLog*> &logs, long long startTime, long long endTime, int pid);
    
    public:
        std::vector<ProcessLog*> schedule(std::vector<Process*> processList);
    };
}

#endif 
