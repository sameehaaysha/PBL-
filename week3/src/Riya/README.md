# Interactive Deadlock Simulation System – GUI Module

## 1. Overview

This module implements the Graphical User Interface (GUI) for the Interactive Deadlock Simulation System using C and GTK 3.

The purpose of this module is to provide a user-friendly interface through which users can interact with the deadlock simulation, access system operations, and view status messages.

## 2. My Contribution

My contribution focuses on designing and implementing the GUI module.

The main responsibilities include:

- Developing the graphical interface using GTK 3.
- Designing the main application window and dashboard.
- Creating buttons for the different deadlock simulation operations.
- Organizing the interface to make system operations easy to access.
- Displaying status messages to provide feedback to users.
- Implementing a resource allocation graph display entry point.
- Preparing test code to check GUI functionality.

## 3. Technologies Used

- **Programming Language:** C
- **GUI Framework:** GTK 3
- **Development Environment:** VS Code
- **Operating Environment:** Ubuntu / WSL
- **Testing:** C test program
- **Version Control:** Git and GitHub

## 4. GUI Features

The interface provides buttons for the following operations:

1. Create Processes
2. Create Resources
3. Enter Allocation Matrix
4. Enter Maximum Matrix
5. Display Need Matrix
6. Display Resource Allocation Graph
7. Request Resources
8. Run Banker's Algorithm
9. Detect Deadlock
10. Recover from Deadlock
11. Display System Status
12. Exit the Application

The interface also includes a dashboard layout, visual styling, and a status area for displaying messages.

**Note:** The buttons currently provide interface entry points. Operations must be connected to the corresponding system functions for full integration with the deadlock simulation algorithms.

## 5. File Structure

```text
Riya/
├── gui.c
├── gui.h
├── test/
│   └── test_gui.c
└── README.mdP