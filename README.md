# 100 Prisoners — Group Strategy Simulator

I am tryharding this readme
This program simulates the classic “100 prisoners” (hat/number guessing) group strategy that **guarantees at least one prisoner guesses their number correctly**. It lets you vary the group size `N` and the number of Monte Carlo trials.

---

## Build

```bash
g++ -std=c++17 -O2 -Wall 100prisoners.cpp -o sim
```

---

## Usage

```bash
./sim                # N=10, trials=1
./sim N              # custom N, trials=1
./sim N TRIALS       # custom N and trials
```

- `N` (optional): number of prisoners (default: `10`)
- `TRIALS` (optional): number of simulations to run (default: `1`)

---

## Examples

```bash
# Default: N=10, trials=1
./sim

# Custom N with default trials=1
./sim 25

# Custom N and number of trials
./sim 100 100000
```
