# CPU Scheduler Simulation

[![Live Demo](https://img.shields.io/badge/Live-Demo-brightgreen?style=for-the-badge)](https://cpu-scheduler-4dgk.onrender.com/)

This project is a simulation environment for various CPU scheduling algorithms. It allows users to define a set of processes with different characteristics (e.g., CPU burst time, priority, I/O-bound vs. CPU-bound) and visualize how different schedulers execute these processes over time. The simulation generates a timeline plot for easy comparison and analysis of algorithm performance.

---

## Table of Contents
1. Overview
2. Supported Algorithms
3. Process Types
   - CPU-Bound Tasks
   - I/O-Bound Tasks
4. How It Works
5. Getting Started
6. Simulation Examples

---

## Overview

This project simulates and visualizes the behavior of several common CPU scheduling algorithms. You can add processes, configure their properties, select a scheduling algorithm, and run the simulation to see a Gantt chart of the process execution timeline. This is useful for understanding and comparing the performance and behavior of different scheduling strategies.

---

## Supported Algorithms

The simulation supports the following scheduling algorithms:

- **Completely Fair Scheduler (CFS)**: The default scheduler in many modern Linux distributions. It aims to provide a fair share of CPU time to all running processes. It uses a red-black tree to store processes and picks the one with the lowest `vruntime` (virtual runtime) to run next, ensuring that processes that have run less get a higher priority.

- **First-Come, First-Served (FCFS)**: A non-preemptive algorithm where processes are executed in the order they arrive. It's simple but can suffer from the "convoy effect," where a long process blocks shorter processes that arrive after it.

- **Shortest Job First (SJF)**: A non-preemptive algorithm that selects the process with the smallest CPU burst time. It is provably optimal for minimizing the average waiting time but requires knowing the burst time in advance, which is not always possible in a real system.

- **Longest Remaining Time First (LRTF)**: A preemptive algorithm that is the inverse of Shortest Remaining Time First (SRTF). It prioritizes the process with the longest remaining execution time. This is generally used for specific use cases and is not a common general-purpose scheduler.

- **Round Robin (RR)**: A preemptive algorithm where each process is assigned a fixed time slice (quantum). The scheduler cycles through the ready queue, running each process for one time quantum. If a process is not finished, it's moved to the back of the queue. It provides good response time for interactive tasks.

- **Priority Based Scheduling (PBS)**: A scheduling method where each process is assigned a priority. The process with the highest priority is selected to run. This can be either preemptive (a higher priority process can interrupt a running lower priority one) or non-preemptive.

---

## Process Types

The simulation supports two main types of processes to model real-world workloads:

### CPU-Bound Tasks
- Tasks that primarily use the CPU.
- Each task has:
  - `cpu_burst_time`: Total CPU time required.
  - `priority`: Determines the task's weight.
- Execution:
  - These tasks will continuously run on the CPU until their burst time is completed, or until they are preempted by the scheduler.

### I/O-Bound Tasks
- Tasks that frequently wait for I/O.
- Each task has:
  - `cpu_burst_time`: Total CPU time required.
  - `priority`: Determines the task's weight.
  - `iowait`: Simulated I/O wait time.
- Execution:
  - These tasks run on the CPU for a short period and then enter a waiting state to simulate an I/O operation. After the I/O wait, they return to the ready queue to be scheduled again.

---

## How It Works

1. **Add Processes**: Use the "Add Process" button to create new processes. You can specify the CPU Burst Time, Priority, and Process Nature (CPU Bound or I/O Bound).
2. **Select Algorithm**: Choose a scheduling algorithm from the dropdown menu.
3. **Run Simulation**: Click the "Run Simulation" button. The C++ backend will run the scheduling logic for the selected algorithm with the defined processes.
4. **View Results**: The simulation generates a timeline plot (Gantt chart) showing which process was running at each time unit. This plot is displayed on the web page.

---

## Getting Started

### Prerequisites
- C++ compiler (e.g., `g++`) and `cmake`.
- Python3 and `pip` for the web server and plotting.

### Steps to Run the Simulation
1. Clone the repository:
   ```bash
   git clone https://github.com/devanshgarg024/CPU_scheduler.git
   cd CPU_scheduler
   ```
2. Set up the Python environment and install dependencies:
   ```bash
   python -m venv /myvenv # create virtual env if not created, use python3 if python not working
   source myvenv/bin/activate
   pip install -r requirements.txt
   ```
3. Build the C++ backend:
   ```bash
   cd build # make build dir in root folder if it is not there
   cmake ..
   make
   ```
4. Run the web server:
   ```bash
   cd .. 
   python server.py
   ```
5. Open your web browser and go to `http://127.0.0.1:5000` to use the simulator.

---

## Simulation Examples

The following images show example outputs for the **Completely Fair Scheduler (CFS)** with different workloads.

### CFS with I/O-Bound Processes
In this simulation, all processes are I/O-bound. We can observe that tasks wait for their I/O time and their `vruntime` is penalized accordingly. Higher priority I/O tasks, despite being penalized, get scheduled after their I/O wait.

!image

### CFS with CPU-Bound Processes
In this simulation with CPU-bound tasks, Process 1 finishes first because it has the highest priority (and thus the highest weight). Its `vruntime` increases slowest, causing it to be scheduled more frequently.


   _dissecting linux schedulers & implementing our toy cfs_scheduler simulation:- Link_
