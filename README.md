# CPU Scheduling Algorithm Simulator

## Overview

A CPU Scheduling Algorithm Simulator implemented in C++ to demonstrate how different scheduling algorithms work in an Operating System. It simulates both preemptive and non-preemptive scheduling strategies and compares their performance using waiting time and turnaround time.

## Features

- Supports multiple CPU scheduling algorithms
- Handles arrival time, burst time, and priority
- Calculates:
  - Waiting Time (WT)
  - Turnaround Time (TAT)
- Demonstrates real OS behavior using time-unit simulation

## Algorithms Implemented

### Non-Preemptive Algorithms
- First Come First Serve (FCFS)
- Shortest Job First (SJF)
- Priority Scheduling

### Preemptive Algorithms
- Shortest Remaining Time First (SRTF)
- Priority Scheduling (Preemptive)

### Time-Sharing Algorithm
- Round Robin Scheduling

## Operating System Concepts Covered

- CPU Scheduling
- Preemptive vs Non-Preemptive Scheduling
- Context Switching
- Process Arrival & Execution
- Starvation and Fairness
- Time Quantum (Round Robin)

## Technologies Used

- **Language:** C++
- **Concepts:**
  - Structures
  - Vectors, Queues
  - Sorting & Searching
  - OS Scheduling Logic
