# 42_push_swap
🧮 push_swap – Sorting integers with minimal operations using two stacks, crafted at 42. ⚙️ Features custom algorithms to optimize sorting with limited stack-based instructions.
# 🔄 Push_swap - Sort with Limited Moves

> 🎯 **Sort a stack of integers** using only two stacks and a limited set of operations!

## 📖 What is Push_swap?

**Push_swap** is a 42 School project where you sort numbers using:
- 📚 **Two stacks** (Stack A and Stack B)
- 🎮 **11 operations** only
- 🏆 **Minimum moves** possible

This teaches you:
- 📊 **Sorting algorithms** - Different approaches to ordering data
- 🧠 **Algorithm optimization** - Finding the cheapest moves
- 📚 **Stack data structure** - LIFO (Last In, First Out)
- 🎯 **Complexity analysis** - Big O notation

---

## 🎮 The Operations

### Swap Operations
| Operation | Description | Visual |
|-----------|-------------|--------|
| `sa` | Swap first 2 elements of stack A | `[2,1,3] → [1,2,3]` |
| `sb` | Swap first 2 elements of stack B | Same for B |
| `ss` | `sa` and `sb` at the same time | Both stacks |

### Push Operations
| Operation | Description | Visual |
|-----------|-------------|--------|
| `pa` | Push top of B to top of A | `B→A` |
| `pb` | Push top of A to top of B | `A→B` |

### Rotate Operations (shift up)
| Operation | Description | Visual |
|-----------|-------------|--------|
| `ra` | Rotate A up (first becomes last) | `[1,2,3] → [2,3,1]` |
| `rb` | Rotate B up | Same for B |
| `rr` | `ra` and `rb` at the same time | Both stacks |

### Reverse Rotate Operations (shift down)
| Operation | Description | Visual |
|-----------|-------------|--------|
| `rra` | Rotate A down (last becomes first) | `[1,2,3] → [3,1,2]` |
| `rrb` | Rotate B down | Same for B |
| `rrr` | `rra` and `rrb` at the same time | Both stacks |

---

## 📊 Visual Example

```
Initial:        After pb:       After pb:       After sa:
Stack A: 3      Stack A: 3      Stack A: 3      Stack A: 1
         1               1                               3
         2               2       Stack B: 2     Stack B: 2
                                          1              1
Stack B: -      Stack B: -
```

---

## 📁 Project Structure

```
push_swap/
├── 📄 push_swap.h       # Header with prototypes & struct
├── 📄 main.c            # Entry point
├── 📄 initialization.c  # Stack creation & indexing
├── 📄 input_check.c     # Validate input arguments
├── 📄 input_check_utils.c
├── 📄 stack.c           # Stack utility functions
├── 📄 swap.c            # sa, sb, ss operations
├── 📄 push.c            # pa, pb operations
├── 📄 rotate.c          # ra, rb, rr operations
├── 📄 reverse_rotate.c  # rra, rrb, rrr operations
├── 📄 sort_tiny.c       # Sort 3 or fewer elements
├── 📄 sort.c            # Main sorting algorithm
├── 📄 position.c        # Calculate target positions
├── 📄 cost.c            # Calculate move costs
├── 📄 do_move.c         # Execute the cheapest move
├── 📄 utils.c           # Helper functions
├── 📄 Makefile
└── 📂 libft/            # Your libft library
```

---

## 🧠 The Algorithm (Turk Algorithm)

### Step 1: Index the Numbers
Convert values to indices (smallest = 1, largest = n):
```
Values:  [42, 5, 89, 1, 23]
Indices: [ 3, 2,  5, 1,  4]
```

### Step 2: Push to Stack B (Keep 3 in A)
Push elements to B, keeping only 3 in A:
```
Stack A: [3, 2, 5]    →    Stack A: [5]
                           Stack B: [3, 2, 1, 4]
```

### Step 3: Sort the 3 Elements in A
Use `tiny_sort` for ≤3 elements (max 2 moves).

### Step 4: Push Back with Minimum Cost
For each element in B:
1. Calculate **cost** to move it to correct position in A
2. Find the **cheapest** element to move
3. Execute the move

### Step 5: Final Rotation
Rotate A until smallest element is on top.

---

## 💰 Cost Calculation

```
Stack A:  [1, 5, 8, 12]     Stack B: [3, 7, 10]
Position:  0  1  2   3               0  1   2

To move 7 from B to A (between 5 and 8):
- Cost in B: 1 (one rb to get 7 to top)
- Cost in A: 2 (two ra to position after 5)
- Total cost: 1 + 2 = 3 moves

Optimization: Use rr/rrr when both need same direction!
```

---

## 🛠️ Compilation

```bash
# Build
make

# Clean object files
make clean

# Full clean
make fclean

# Rebuild
make re
```

---

## 🚀 Usage

```bash
# Sort numbers
./push_swap 4 67 3 87 23

# Output (list of operations):
pb
pb
ra
pa
pa
ra
```

### Test with Checker
```bash
# Generate operations and verify
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_linux $ARG
OK  ← Success!

# Count operations
ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l
6
```

---

## 🏆 Performance Goals

| Stack Size | Max Operations | Your Target |
|------------|----------------|-------------|
| 3 | 2-3 | ≤3 ✅ |
| 5 | 12 | ≤12 ✅ |
| 100 | 700 | ≤700 for 5 points |
| 100 | 900 | ≤900 for 4 points |
| 500 | 5500 | ≤5500 for 5 points |
| 500 | 7000 | ≤7000 for 4 points |

---

## 📊 The Stack Structure

```c
typedef struct s_stack
{
    int             value;      // Actual number
    int             index;      // Sorted position (1 to n)
    int             pos;        // Current position in stack
    int             target_pos; // Where it should go in A
    int             cost_a;     // Moves needed in A
    int             cost_b;     // Moves needed in B
    struct s_stack  *next;      // Next node
}   t_stack;
```

---

## 🔢 Sorting 3 Elements (tiny_sort)

Only 6 possible arrangements! Handle each:

```
Case 1: [1,2,3] → Already sorted! (0 moves)
Case 2: [1,3,2] → sa, ra (2 moves)
Case 3: [2,1,3] → sa (1 move)
Case 4: [2,3,1] → rra (1 move)
Case 5: [3,1,2] → ra (1 move)
Case 6: [3,2,1] → sa, rra (2 moves)
```

---

## 🧪 Testing

```bash
# Generate random numbers (Linux)
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' '); ./push_swap $ARG | wc -l

# Test multiple times
for i in {1..10}; do
    ARG=$(shuf -i 1-500 -n 500 | tr '\n' ' ')
    COUNT=$(./push_swap $ARG | wc -l)
    echo "Test $i: $COUNT operations"
done

# Verify correctness
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' ')
./push_swap $ARG | ./checker_linux $ARG
```

---

## ✅ Testing Checklist

- [ ] Already sorted: `./push_swap 1 2 3 4 5`
- [ ] Reverse sorted: `./push_swap 5 4 3 2 1`
- [ ] Two elements: `./push_swap 2 1`
- [ ] Three elements: `./push_swap 3 1 2`
- [ ] Five elements: `./push_swap 5 3 1 4 2`
- [ ] Duplicates (error): `./push_swap 1 2 2 3`
- [ ] Non-numbers (error): `./push_swap 1 2 abc 3`
- [ ] Integer overflow: `./push_swap 2147483648`
- [ ] Empty input: `./push_swap`
- [ ] 100 random numbers
- [ ] 500 random numbers

---

## ⚠️ Edge Cases & Errors

Print `Error\n` to stderr for:
- ❌ Duplicate numbers
- ❌ Non-integer arguments
- ❌ Numbers > INT_MAX or < INT_MIN
- ❌ Non-numeric characters

```bash
./push_swap 1 2 2        # Error (duplicate)
./push_swap 1 abc 3      # Error (not a number)
./push_swap 99999999999  # Error (overflow)
```

---

## 🔍 Debugging Tips

```bash
# Visualize the sorting (online tools)
# Search: "push_swap visualizer"

# Print operations step by step
./push_swap 5 3 1 4 2 | head -20

# Check for memory leaks
valgrind --leak-check=full ./push_swap $(shuf -i 1-100 -n 100 | tr '\n' ' ')

# Verify all tests pass
ARG="3 1 2"; ./push_swap $ARG | ./checker_linux $ARG
```

---

## 📚 Key Concepts

### 1. Why Index Instead of Value?
Using indices simplifies comparison:
```
Values:  [999, 1, 500]  →  Hard to compare
Indices: [  3, 1,   2]  →  Easy! Just 1 < 2 < 3
```

### 2. Cost Optimization
```
Positive cost = rotate (ra, rb)
Negative cost = reverse rotate (rra, rrb)

If both costs same sign → use rr or rrr (saves moves!)
```

### 3. Target Position
Where should element go in Stack A?
→ Just above the closest smaller indexed element!

---

## 👤 Author

**malbreik** - 42 Abu Dhabi Student

---

## ⭐ Pro Tips

1. 🎯 **Handle small cases first** - 2, 3, 5 elements
2. 📊 **Visualize** - Draw stacks on paper
3. 💰 **Optimize costs** - Use rr/rrr when possible
4. 🧪 **Test extensively** - Random numbers, edge cases
5. 📈 **Benchmark** - Track your operation counts
6. 🔢 **Use indices** - Much simpler than raw values

---

*Made with ❤️ at 42 School*
