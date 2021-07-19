# The Cheapest Path
Implementation of the Shortest Path Faster Algorithm (SPFA) in C++.

### **Input**
- **n**: the number of crossroads (non-negative integer),
- **m**: the number of roads (non-negative integer),
- Next m lines of roads definitions, in the form: **v u d**, where:
    - **v** and **u** are the indices of crossroads that are connected with a given road (non-negative integers from range [0, n-1]),
    - **d** is the cost of the road (integer).
- **t**: the number of tests (non-negative integer),
- Next **t** lines of tests definitions, in the form: **a b**, where:
    - **a** is the index of a crossroad that is the starting point of the path to be found (non-negative integer from range [0, n-1]),
    - **b** is the index of a crossroad that is the destination of the path to be found (non-negative integer from range [0, n-1]).

### **Example**
**Input**  
5  
4  
0 1 1  
0 2 3  
1 2 0  
3 4 -1  
2  
0 2  
0 3  
**Output**  
1  
!
