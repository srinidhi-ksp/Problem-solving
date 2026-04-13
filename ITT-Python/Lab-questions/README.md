# Lab Questions - Problem Solutions

This folder contains solutions to the following problem statements:

## 1. Hit and Near Hits (`calculate_hit_and_near_hits.py`)

**Problem Description:**
You think of a code and your friend tries to guess the code by attempting it. The code is a string consisting of digits and your friend guesses the code. You need to find the number of hits and near hits.

- **Hit**: A particular digit is present in the code and is guessed correctly in the correct position.
- **Near Hit**: A particular digit which is guessed is present in the code but guessed in the wrong position.

*Note: A digit in the code can be considered for only one hit or near hit.*

**Output Format:** Print the number of hits and near hits in the format "XHyN" (e.g., "1H2N" means 1 hit and 2 near hits).

**Example:**
- Code: 1709
- Guess: 1807
- Output: 2H1N

---

## 2. Car and Bike Problem (`cars_and_bike.py`)

**Problem Description:**
Ravi opened a company which manufactures cars and bikes.
- Each car requires 4 tyres
- Each bike requires 2 tyres
- Ravi has a total of N tyres (N is even)

He wants to manufacture the maximum number of cars from these tyres and then manufacture bikes from the remaining tyres. Ravi's friend wants to purchase a bike. If Ravi's company has manufactured even a single bike, then Ravi's friend will be able to purchase it.

**Task:** Determine whether Ravi's friend will be able to purchase the bike or not.

**Input Format:**
- First line: Integer T (number of test cases)
- Each test case: Integer N (number of tyres)

**Output Format:** For each test case, output "YES" or "NO" (case insensitive).

**Constraints:**
- 1 ≤ T ≤ 100
- 2 < N ≤ 1000
- N is even

**Example:**
- Input: 8 → Output: NO
- Input: 6 → Output: YES

---

## 3. Coin Game Problem (`coin-game.py`)

**Problem Description:**
Suresh and Sundar were playing a game with coins. The player with more coins is winning. If both have the same number of coins, then Suresh is winning.

- Initially: Suresh has A coins, Sundar has B coins
- Raja gives C coins to the player who is not winning currently
- Then Suresh gives D coins to the player who is not winning currently

**Task:** Find the final winner of the game.

**Input Format:**
- First line: Integer T (number of test cases)
- Each test case: Four space-separated integers A, B, C, and D

**Output Format:** For each test case, output "N" if Suresh is the final winner, or "S" if Sundar is the final winner.

**Constraints:**
- 1 ≤ T ≤ 1000
- 0 ≤ A, B, C, D ≤ 10^6

**Example:**
```
Input:
3
2 3 4 5
3 3 3 2
3 1 2

Output:
S
N
S
```

---

## How to Run

Each Python file can be executed independently:
```bash
python calculate_hit_and_near_hits.py
python cars_and_bike.py
python coin-game.py
```