# SLR(1) Parser Simulator & Compiler Workbench

A full-stack web application for visual compiler analysis, built to simulate **Shift-Reduce SLR(1) Parsing**, generate **Three-Address Code (TAC)**, build **Symbol Tables**, and run **Performance Benchmarks** comparing SLR(1) bottom-up parsing against Recursive Descent top-down parsing.

---

## Features

- **Interactive Parsing Engine**: Parses arithmetic expressions in real time.
- **Step-by-Step SLR(1) Trace**: Detailed trace table displaying Parser State Stack, Input Buffer, and Action Taken (Shift, Reduce, Accept) with color coding.
- **Symbol Table Generation**: Extracts identifiers, maps data types, and tracks variable occurrence order.
- **Three-Address Code (TAC)**: Generates intermediate representations with temporary variables (`t1`, `t2`, etc.).
- **Parser Benchmarking**: Compares SLR(1) bottom-up execution time against Recursive Descent top-down parsing time and call-stack depth metrics.

---

## Architecture & Tech Stack

- **Core Engine (C++)**: Handles grammar tokenization, SLR(1) shift-reduce parsing routines, TAC generation, symbol extraction, and recursive descent execution profiling.
- **Backend (Node.js & Express)**: Acts as a bridge between the frontend and C++ engine, invoking native binaries and converting terminal stdout into structured JSON REST responses.
- **Frontend (Angular)**: Modern single-page application built with modular Angular components for real-time trace rendering and interactive data displays.

---

## Project Structure

```text
compiler-parser-simulator/
├── main.cpp                 # Native C++ SLR(1) & Recursive Descent Engine
├── server.js                 # Express Backend API Bridge
├── package.json              # Backend dependencies
├── .gitignore               # Ignored files list
└── frontend/                # Angular Frontend Application
    ├── src/
    │   ├── app/
    │   │   ├── app.ts       # Main Angular Component
    │   │   ├── app.html     # Layout Template
    │   │   ├── services/    # HttpClient Service (parser.ts)
    │   │   └── components/  # Modular UI Components
    │   │       ├── control-panel/
    │   │       ├── trace-table/
    │   │       ├── symbol-table/
    │   │       ├── tac-view/
    │   │       └── benchmark/
    │   └── main.ts
    └── package.json
