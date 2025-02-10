# **Optimal Path Decider**  

## **Overview**  
This project implements three different strategies to solve the **Travelling Salesman Problem (TSP)**, a well-known combinatorial optimization problem. The goal is to find the **minimum-cost path** that visits each city exactly once and returns to the starting city.  

### **Implemented Strategies:**  
1. **Brute Force (`b`)** - Generates all possible permutations and selects the one with the lowest cost (**O(n!)** complexity).  
2. **Dynamic Programming (`d`)** - Uses **bitmasking and memoization** to improve efficiency compared to brute force (**O(n² * 2ⁿ)** complexity).  
3. **Greedy Algorithm (`g`)** - Selects the nearest unvisited city at each step (**O(n²)** complexity).  

Each strategy balances **performance and solution accuracy**, as analyzed in this project.  

---

## **Project Structure**  

```
📂 optimal-path-decider/
│── 📂 include/                # Header files
│   ├── graph.hpp              # Graph class (TSP logic)
│   ├── vertex.hpp             # Vertex representation
│   ├── edge.hpp               # Edge representation
│   ├── solution.hpp           # Solution execution
│
│── 📂 src/                    # Source code
│   ├── main.cpp               # Main execution file
│   ├── graph.cpp              # Graph implementation
│   ├── vertex.cpp             # Vertex implementation
│   ├── edge.cpp               # Edge implementation
│   ├── solution.cpp           # Solution implementation
│
│── 📂 testcases/               # Test case files
│   ├── 📂 inputs/              # Input graphs
│   ├── 📂 outputs/             # Expected outputs
│
│── 📜 README.md                # Project documentation
│── 📜 Makefile                  # Compilation script
```

---

## **Installation & Compilation**  

### **Requirements:**  
- **C++17 or later**  

### **Compile the Project:**  
To build the executable, run:  
```bash
make
```
This will generate a binary file named `tp3`.  

### **Run the Solver:**  
```bash
./tp3 < testcases/inputs/testCase01.txt
```
This executes the program using the input graph from `testCase01.txt`.  

---

## **Input & Output Format**  

### **Input File Format:**  
1. The **first line** contains a single character:  
   - `'b'` → Brute Force  
   - `'d'` → Dynamic Programming  
   - `'g'` → Greedy Algorithm  
2. The **second line** contains two integers:  
   - `V` → Number of vertices (cities)  
   - `E` → Number of edges (roads)  
3. The **next `E` lines** define the roads in the format:  
   ```
   city1 city2 cost
   ```
   Example input file:
   ```
   d
   4 6
   Cyberia Augmented 252
   Cyberia Quasar 120
   Cyberia Elysium 19
   Augmented Quasar 117
   Augmented Elysium 27
   Quasar Elysium 122
   ```

### **Output Format:**  
The program prints:  
1. **The minimum cost of the best path** (integer).  
2. **The sequence of cities in the order they should be visited.**

Example output:
```
283
Cyberia Elysium Augmented Quasar
```

---

## **Results & Observations**  

| **Strategy**           | **Time Complexity** | **Memory Usage** | **Solution Quality** |
|------------------------|--------------------|-----------------|------------------|
| **Brute Force**        | **O(n!)**          | **O(1)**        | **Optimal**      |
| **Dynamic Programming**| **O(n² * 2ⁿ)**     | **O(n * 2ⁿ)**   | **Optimal**      |
| **Greedy Algorithm**   | **O(n²)**          | **O(n)**        | **Approximate**  |

🔹 **Brute Force** becomes **unusable for n > 10** due to exponential growth.  
🔹 **Dynamic Programming** improves execution but is limited by **O(n² * 2ⁿ) complexity**.  
🔹 **Greedy Algorithm** scales well but does **not always** find the optimal path.  
