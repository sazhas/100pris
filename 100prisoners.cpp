// ≽^•˕•^≼
// compile: g++ -std=c++17 -O2 -Wall 100prisoners.cpp -o sim
// Usage:
//   ./sim                 -> N=10, trials=1
//   ./sim N               -> custom N, trials=1
//   ./sim N TRIALS        -> custom N and trials

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;

struct Row {
    int label;            // 0..N-1
    int actual;           // 1..N
    long long seenSum;    // sum of others' actuals
    int seenMod;          // seenSum % N (0..N-1)
    int guessResid;       // (label - seenMod) mod N (0..N-1)
    int guess;            // 0 -> N, else guessResid
    bool correct;
};

int toResid(int num, int N) {
    // Map 1..N -> residues 1..N-1 and N -> 0
    return (num == N) ? 0 : (num % N);
}
int fromResid(int resid, int N) {
    // Map residue 0 back to N; others map to themselves
    return (resid == 0) ? N : resid;
}


// actual algorithm!
static vector<Row> run_once(mt19937 &rng, int N) {
    uniform_int_distribution<int> dist(1, N);

    // populating random numbers 1..N
    vector<int> a(N);
    for (int i = 0; i < N; ++i) a[i] = dist(rng);

    // precomputing raw total for SeenSum column
    long long totalRaw = 0;
    for (int v : a) totalRaw += v;

    vector<Row> rows;
    rows.reserve(N);

    for (int i = 0; i < N; ++i) {
        int L = i;
        long long seen = totalRaw - a[i];
        int S = static_cast<int>(seen % N); // seen mod N in 0..N-1

        // 0-indexed rule: guessResid = (L - S) mod N
        int gResid = (L - S) % N;

        // because c++ keeps the sign of the left operand
        if (gResid < 0) gResid += N;

        int g = fromResid(gResid, N);
        bool correct = (g == a[i]);

        rows.push_back({L, a[i], seen, S, gResid, g, correct});
    }

    return rows;
}





// formatting and output
int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 10;
    int trials = 1;

    if (argc >= 2) {
        N = max(2, stoi(argv[1]));
    }
    if (argc >= 3) {
        trials = max(1, stoi(argv[2]));
    }

    random_device rd;
    mt19937 rng(rd());

    int exactlyOneCount = 0;

    for (int t = 1; t <= trials; ++t) {
        auto rows = run_once(rng, N);

        // for convenience: show actuals and residues and total residue
        vector<int> residues(N);
        int totalResid = 0;
        for (int i = 0; i < N; ++i) {
            residues[i] = toResid(rows[i].actual, N);
            totalResid = (totalResid + residues[i]) % N;
        }

        cout << "=== Trial " << t << " (N=" << N << ") ===\n";
        cout << "Actual head numbers: ";
        for (int i = 0; i < N; ++i)
            cout << rows[i].actual << (i+1 < N ? ' ' : '\n');
        cout << "Residues (N->0):     ";
        for (int i = 0; i < N; ++i)
            cout << residues[i] << (i+1 < N ? ' ' : '\n');
        cout << "Total residue T mod " << N << " = " << totalResid << "\n\n";

        cout << left
             << setw(8)  << "Label"
             << setw(10) << "TrueVal"
             << setw(14) << "SeenSum"
             << setw(10) << "SeenMod"
             << setw(14) << "GuessResid"
             << setw(10) << "Guess"
             << "Correct?\n";

        int correctCount = 0;
        for (auto &r : rows) {
            cout << left
                 << setw(8)  << r.label
                 << setw(10) << r.actual
                 << setw(14) << r.seenSum
                 << setw(10) << r.seenMod
                 << setw(14) << r.guessResid
                 << setw(10) << r.guess
                 << (r.correct ? "YES" : "no") << "\n";
            if (r.correct) ++correctCount;
        }

        cout << "\nAt least one correct? "
             << (correctCount >= 1 ? "YES!! :D " : "NO but this answer will never be seen !")
             << "   (count = " << correctCount << ")\n";
        cout << string(60, '-') << "\n";

        if (correctCount == 1) ++exactlyOneCount;
    }

    if (trials > 1) {
        cout << "\nSummary over " << trials << " trials:\n";
        cout << "Trials with exactly one correct: "
             << exactlyOneCount << " / " << trials << "\n";
    }

    return 0;
}
