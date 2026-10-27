# Page Replacement Simulator 

## 1. My Role

 My main role was to integrate the team members' code and connect the page replacement algorithms with the graphical user interface.

## 2. My Responsibilities

* Developed and maintained `main.c` to coordinate the simulator's operations.
* Integrated the FIFO, LRU, and Optimal page replacement algorithms developed by team members.
* Connected the algorithm functions with the GUI.
* Handled user inputs, including the page reference string, number of frames, and algorithm selection.
* Displayed simulation results, including page hits, page faults, and hit and fault ratios.
* Implemented the **Compare All** option to compare the performance of the three algorithms.
* Tested the program and worked on resolving compilation and integration errors.

## 3. Files Handled

* **`main.c`** — Coordinates the algorithms and processes simulation results.
* **`gui.c`** — Implements the graphical user interface.
* **`gui.h`** — Contains GUI declarations.
* **`common.h`** — Defines shared data structures, constants, and algorithm types.
* **`Makefile`** — Automates compilation of the project.

## 4. Technologies Used

* C Programming Language
* GTK+ 3 for the graphical user interface
* GCC compiler
* Makefile for building the project
* Git and GitHub for version control and team collaboration

## 5. How to Run

Open the terminal in the project directory and execute:

```bash
make
./page_replacement
```

## 6. Project Outcome

The simulator provides a graphical interface for testing FIFO, LRU, and Optimal page replacement algorithms. It displays the simulation steps and calculates page hits, page faults, and their respective ratios, helping users understand and compare the algorithms.
