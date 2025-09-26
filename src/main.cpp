#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "processService.hpp"
#include "processLog.hpp"

// Include all your scheduler headers
#include "cfs/cfs.hpp"
#include "fcfs/fcfs.hpp"
#include "sjf/sjf.hpp"
#include "lrtf/lrtf.hpp"
#include "round_robin/rr.hpp"
#include "pbs/pbs.hpp"

void writeLogsToCsv(const std::vector<ProcessLog*>& logs, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for writing." << std::endl;
        return;
    }

    file << "pid,start_time,end_time\n";
    for (const auto& log : logs) {
        file << log->pid << "," << log->startTime << "," << log->endTime << "\n";
    }
    file.close();
    std::cout << "Successfully wrote logs to " << filename << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <algorithm>" << std::endl;
        std::cerr << "Available algorithms: cfs, fcfs, sjf, lrtf, rr, pbs" << std::endl;
        return 1;
    }

    std::string algorithm = argv[1];
    std::vector<Process*> processList;
    try {
        processList = getProcessFromJson("resources/process.json");
    } catch (const std::exception& e) {
        std::cerr << "Error reading process data: " << e.what() << std::endl;
        return 1;
    }

    std::vector<ProcessLog*> logs;

    std::cout << "Running scheduler: " << algorithm << std::endl;

    if (algorithm == "cfs") {
        cfs::schedular scheduler;
        logs = scheduler.schedule(processList);
    } else if (algorithm == "fcfs") {
        fcfs::schedular scheduler;
        logs = scheduler.schedule(processList);
    } else if (algorithm == "sjf") {
        sjf::schedular scheduler;
        logs = scheduler.schedule(processList);
    } else if (algorithm == "lrtf") {
        lrtf::schedular scheduler;
        logs = scheduler.schedule(processList);
    } else if (algorithm == "rr") {
        rr::schedular scheduler;
        logs = scheduler.schedule(processList);
    } else if (algorithm == "pbs") {
        pbs::schedular scheduler;
        logs = scheduler.schedule(processList);
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << std::endl;
        // Clean up allocated processes
        for (auto p : processList) delete p;
        return 1;
    }

    writeLogsToCsv(logs, "process_schedule.csv");

    // Clean up allocated memory
    for (auto p : processList) delete p;
    for (auto log : logs) delete log;

    return 0;
}