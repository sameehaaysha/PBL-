# Deadlock Simulator –  Integration

# My Role

I was responsible for integrating the different modules of the Deadlock Simulator and connecting the core functionality with the GTK-based graphical user interface.

## My Contributions

- Integrated the **Process Management, Resource Management, Deadlock Handling, and GUI** modules.
- Developed and connected the **main GUI and action buttons** for the simulator.
- Implemented user input for **processes, resources, allocation, and maximum resource requirements**.
- Integrated the **Need Matrix** calculation using:
  `Need = Maximum - Allocation`
- Connected the GUI with the **Banker's Algorithm** for system safety checking.
- Integrated **Resource Request, Deadlock Detection, Recovery, RAG, and System Status** features.
- Added input validation and status messages for user actions.
- Tested the interaction between modules and worked on debugging integration and GUI issues.
- Coordinated the integration of the team members' modules into the final project.

## Files Worked On

- `main.c`
- `Makefile`
- `common.h`
- Integration with `process.c`,gui.c' and `deadlock.c`

## Technologies Used

- C
- GTK 3
- GCC
- Linux / WSL
- Git & GitHub

## Summary

My main responsibility was to bring the individual modules together into one complete Deadlock Simulator, providing a user-friendly GUI for managing processes and resources, checking system safety, handling resource requests, and analyzing deadlocks.