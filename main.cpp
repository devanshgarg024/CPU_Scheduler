// #include <iostream>
// #include "src/processService.hpp"
// #include <vector>
// #include "src/processLog.hpp"
// #include "src/round_robin/rr.hpp"
// #include "src/cfs/cfs.hpp"
// #include "src/fcfs/fcfs.hpp"
// #include "src/lrtf/lrtf.hpp"
// #include "src/pbs/pbs.hpp"
// #include "src/sjf/sjf.hpp"
// #include <fstream>

// int main(int argv, char* argc[]) {
//     std::vector<Process*> processes = getProcessFromJson("../resources/process.json");
//     cfs::schedular sch;
//     std::vector<ProcessLog*> logs = sch.schedule(processes);
    
//     std::ofstream outFile("../process_schedule.csv");
    
//     outFile << "pid,start_time,end_time" << std::endl;
    
//     for(auto processLog: logs) {
//         outFile << processLog->pid << ","
//                 << processLog->startTime << ","
//                 << processLog->endTime << std::endl;
//     }
    
//     outFile.close();
//     return 0;
// }

