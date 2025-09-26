#ifndef CPU_BOUND_PROCESS_EXECUTION_HPP
#define CPU_BOUND_PROCESS_EXECUTION_HPP

#include "../processService.hpp"
#include "queueService.hpp"

#define CPU_INSTRUCTIONS_IN_MS 200


namespace rr{

    void executeCpuBoundProcess(Process* process, int time_quanta, QueueService& q);
}

#endif // CPU_BOUND_PROCESS_EXECUTION_HPP
