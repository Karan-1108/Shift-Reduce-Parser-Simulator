# SLR(1) Parser Simulator & Compiler Workbench

A full-stack web application designed for interactive compiler analysis. It simulates **Shift-Reduce SLR(1) Parsing**, generates **Three-Address Code (TAC)**, extracts **Symbol Tables**, and runs **Performance Benchmarks** comparing bottom-up SLR(1) parsing with top-down Recursive Descent parsing.

---

## 🚀 Features

- **Interactive SLR(1) Parsing Engine**: Real-time parsing of complex arithmetic expressions.
- **Step-by-Step Parser Trace**: Visual trace table detailing Parser State Stack, Input Buffer, and Action Taken (Shift, Reduce, Accept) with color-coded steps.
- **Symbol Table Generation**: Identifies variables, tracks data types, and records occurrence order.
- **Three-Address Code (TAC)**: Computes intermediate representations using auto-generated temporary variables (`t1`, `t2`, etc.).
- **Performance Benchmarking**: Evaluates and compares SLR(1) bottom-up execution times against Recursive Descent top-down execution times and peak call stack depth.

---

## 🛠️ Tech Stack & Architecture

- **Core Engine (C++)**: Native C++ tokenization, SLR(1) parsing tables, shift-reduce state machine, TAC generation, symbol extraction, and recursive descent call-stack profiling.
- **Backend (Node.js & Express)**: Acts as an API bridge, executing compiled C++ binaries and serving structured JSON REST endpoints.
- **Frontend (Angular)**: Modern web interface built with modular Angular components for interactive data tables, real-time code displays, and benchmark cards.

---

## 📂 Project Structure

```text
Shift-Reduce-Parser-Simulator/
├── core/                    # C++ Parsing Engine
│   ├── include/             # C++ Header files (.hpp)
│   ├── src/                 # C++ Source implementations (.cpp)
│   │   ├── main.cpp
│   │   ├── lexer.cpp
│   │   ├── slr_parser.cpp
│   │   ├── rd_parser.cpp
│   │   ├── symbol_table.cpp
│   │   └── tac_generator.cpp
│   └── CMakeLists.txt
├── server.js                # Express Backend API Bridge
├── package.json             # Backend dependencies
├── .gitignore               # Git ignored files
├── README.md                # Project documentation
└── frontend/                # Angular Frontend Application
    ├── src/
    │   ├── app/
    │   │   ├── app.ts       # Root Component
    │   │   ├── app.html     # Layout Template
    │   │   ├── services/    # HttpClient Service (parser.ts)
    │   │   └── components/  # UI Components
    │   │       ├── control-panel/
    │   │       ├── trace-table/
    │   │       ├── symbol-table/
    │   │       ├── tac-view/
    │   │       └── benchmark/
    │   └── main.ts
    └── package.json
```

---

## 💻 Getting Started

### Prerequisites

Ensure you have the following installed on your machine:
- [Git](https://git-scm.com/)
- [Node.js](https://nodejs.org/) (v18 or higher)
- [C++ Compiler](https://gcc.gnu.org/) (`g++` supporting C++17 or higher)
- [Angular CLI](https://angular.io/cli) (`npm install -g @angular/cli`)

---

### How to Download & Run Locally

#### 1. Clone the Repository
Open your terminal or Command Prompt and clone the repository to your local machine:

```bash
git clone [https://github.com/Karan-1108/Shift-Reduce-Parser-Simulator.git](https://github.com/Karan-1108/Shift-Reduce-Parser-Simulator.git)
cd Shift-Reduce-Parser-Simulator
```

*(Alternatively, click the green **Code** button on GitHub and select **Download ZIP**, then extract the folder).*

#### 2. Compile the C++ Core Engine
From the project root directory, compile all C++ source files located in `core/src/`:

```bash
g++ -std=c++17 core/src/*.cpp -Icore/include -o parser_engine
```

#### 3. Start the Express Backend Server
Install the backend Node.js dependencies and start the server:

```bash
npm install
node server.js
```
The backend server will start listening at `http://localhost:3000`.

#### 4. Launch the Angular Frontend
Open a **new terminal window**, navigate to the `frontend` folder, install dependencies, and start Angular:

```bash
cd frontend
npm install
ng serve --open
```
The application will automatically launch in your default browser at `http://localhost:4200`.

---

## 📊 Example Usage

1. Open the simulator UI at `http://localhost:4200`.
2. Enter an arithmetic expression into the input field:
   ```text
   a + b * c
   ```
3. Click **Parse Expression**.

### Generated Output Preview

- **Symbol Table**:
  | Identifier | Data Type | Occurrence Order |
  |------------|-----------|------------------|
  | `a`        | numeric   | 1                |
  | `b`        | numeric   | 2                |
  | `c`        | numeric   | 3                |

- **Three-Address Code (TAC)**:
  ```text
  t1 = b * c
  t2 = a + t1
  ```

- **SLR(1) Parsing Trace**: Detailed state transitions tracking state stack changes, input buffer consumption, and actions (`Shift 5`, `Reduce F -> id`, ..., `Accept`).
- **Benchmark Metrics**: Compares SLR(1) execution time against Recursive Descent call stack depth (e.g., peak stack depth of 5).
