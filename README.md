# Passenger Transportation Management System

**Assigned topic:** Transportation and Passenger Management  
**Students:** Valensario & Tupas  
**Section:** BSIT A-1

A menu-driven C++ console program for managing passenger bookings across five Bacolod routes.

## Features
- Add, view, search, update, and delete passenger bookings
- Calculate each booking's total fare
- Display passenger totals and revenue for each route

## Arrays
- 1D arrays: passenger names, destinations, passenger counts, and fares.
- 2D array: `stats[ROUTES][2]`; column 0 stores passenger totals and column 1 stores route revenue.

## Compile and run
GCC:
```bash
g++ main.cpp -o passenger_system
./passenger_system
```
Windows:
```bash
g++ main.cpp -o passenger_system.exe
passenger_system.exe
```

Records are stored in memory and are cleared when the program exits. Enter numeric values at numeric prompts.
