This program tests the group strategy that guarantees at least one prisoner guesses their number correctly!

compile: g++ -std=c++17 -O2 -Wall 100prisoners.cpp -o sim
usage:
  ./sim                 -> N=10, trials=1
  ./sim N               -> custom N, trials=1
  ./sim N TRIALS        -> custom N and trials