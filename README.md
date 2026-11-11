# LabLoop – Laboratory Resource Booking & Maintenance Management System

LabLoop is a modular, console-based laboratory management application built with **C++17** and **Object-Oriented Programming (OOP)**. It brings equipment inventory, booking operations, and maintenance tracking into one system.

## Overview

Managing laboratory equipment manually can lead to scheduling conflicts, poor equipment tracking, and delays in maintenance. LabLoop provides a centralized workflow in which students can book equipment and report damage, lab assistants can manage repairs, and administrators can manage the equipment inventory.

## Features

### Student
- View laboratory equipment.
- Book equipment for a selected date and time.
- View personal booking records.
- Cancel their own bookings.
- Report damaged equipment.

### Lab Assistant
- View equipment inventory.
- View all bookings.
- View maintenance records.
- Start repair workflows.
- Resolve maintenance requests.

### Administrator
- Add equipment to the inventory.
- View all equipment.
- View all bookings.
- View maintenance records.

### System capabilities
- Booking conflict detection, including support for back-to-back time slots.
- Date and time validation.
- Booking cancellation with booking-owner verification.
- Equipment availability and maintenance status tracking.
- Maintenance workflow with reported, in-progress, and resolved states.
- Persistent storage using text files.
- Input validation and handling of malformed or duplicate saved records.
- Booking and maintenance ID persistence across application restarts.

## Tech Stack

| Technology | Usage |
| --- | --- |
| C++17 | Core application |
| Object-Oriented Programming | Modular class-based design |
| STL | Vectors, sorting, and unordered sets |
| File handling | Persistent text-file storage |
| g++ | Compilation |

## OOP Concepts Demonstrated

- **Encapsulation:** Class data is kept private and accessed through public methods.
- **Abstraction:** The abstract `User` base class defines a common interface.
- **Inheritance:** `Student`, `LabAssistant`, and `Admin` derive from `User`.
- **Polymorphism:** Virtual functions and overridden dashboard methods provide role-specific behavior.
- **Operator overloading:** The `Booking` class overloads `operator<` for chronological sorting.
- **Composition and delegation:** Manager classes coordinate booking, equipment, maintenance, and persistence operations.

## Project Structure

```text
LabLoop/
├── include/
│   ├── User.h
│   ├── Equipment.h
│   ├── Booking.h
│   ├── BookingManager.h
│   ├── MaintenanceRecord.h
│   ├── MaintenanceManager.h
│   ├── LabManager.h
│   ├── FileManager.h
│   └── Menu.h
├── src/
│   ├── main.cpp
│   ├── User.cpp
│   ├── Equipment.cpp
│   ├── Booking.cpp
│   ├── BookingManager.cpp
│   ├── MaintenanceRecord.cpp
│   ├── MaintenanceManager.cpp
│   ├── LabManager.cpp
│   ├── FileManager.cpp
│   └── Menu.cpp
├── equipment.txt
├── bookings.txt
├── maintenance.txt
└── README.md
```

## Getting Started

### Prerequisites

- A C++ compiler with C++17 support.
- g++ (MinGW is suitable on Windows).
- A terminal or command prompt.

### Compile

Run this command from the project root:

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/User.cpp src/Equipment.cpp src/Booking.cpp src/BookingManager.cpp src/MaintenanceRecord.cpp src/MaintenanceManager.cpp src/LabManager.cpp src/FileManager.cpp src/Menu.cpp -o LabLoop
```

### Run

**Windows PowerShell:**

```powershell
.\LabLoop.exe
```

**Linux/macOS:**

```bash
./LabLoop
```

## Data Persistence

The application stores data in three text files:

- `equipment.txt` – equipment details and current status.
- `bookings.txt` – booking details, time slots, and booking status.
- `maintenance.txt` – damage reports and maintenance status.

Existing data is loaded when the application starts and saved when it exits. Run the executable from the project root so the text files are read and written in the expected location.

## Application Workflow

1. Launch LabLoop.
2. Select Student, Lab Assistant, or Admin from the role menu.
3. Enter the requested user details.
4. Use the corresponding dashboard to perform available operations.
5. Exit the application; data is saved on exit.

> **Note:** The current login flow simulates role selection. It does not implement password-based authentication or secure user authorization.

## Current Scope and Future Improvements

The core console application is implemented. Possible future extensions include:

- Database integration using SQLite or MySQL.
- Credential-based authentication and stronger authorization.
- A graphical or web-based interface.
- Automated unit and integration tests.
- Concurrent booking support for multiple users.

## Project Context

Built as an individual C++ OOP project to practise modular application design, object-oriented programming, validation, booking logic, and file-based persistence.
