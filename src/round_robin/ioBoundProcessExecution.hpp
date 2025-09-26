#ifndef IO_BOUND_PROCESS_EXECUTION_HPP
#define IO_BOUND_PROCESS_EXECUTION_HPP

#include "processService.hpp"
#include "ioBoundProcessExecution.hpp"
#include <iostream>
#include <thread>
#include <time.h>
#include "cpuBoundProcessExecution.hpp"

namespace rr{

    void handleIoBoundProcess(Process* process, int ioWaitTime, int time_quanta, QueueService& q);
}

#endif