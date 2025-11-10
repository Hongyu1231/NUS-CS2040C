cpp queue_simulator_test.cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include "queue_simulator.h" // 假设此头定义 Customer 和 QueueSimulator

using namespace std;

// Generate n customers: arrival times increment by random 0..2, processing times: short (1) or long (10)
static vector<Customer> generate_customers(int n, unsigned seed) {
    vector<Customer> v;
    v.reserve(n);
    srand(seed);
    int t = 0;
    for (int i = 0; i < n; ++i) {
        t += rand() % 3; // interarrival 0..2
        int p = (rand() % 100 < 25) ? 10 : 1; // 25% long jobs
        v.emplace_back(t, p);
    }
    return v;
}

static double average_wait(const vector<Customer>& served) {
    if (served.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& c : served) sum += c.waiting_time();
    return sum / served.size();
}

static void run_one_setting(int num_servers, bool priority, int trials, int n_customers) {
    double total_avg = 0.0;
    for (int t = 0; t < trials; ++t) {
        auto customers = generate_customers(n_customers, 12345 + t);
        // Adjust constructor line below if your QueueSimulator constructor differs.
        QueueSimulator sim(num_servers, priority);
        auto served = sim.simulateQueue(customers);
        total_avg += average_wait(served);
    }
    cout << (priority ? "PRIORITY" : "FIFO   ")
         << " | servers=" << num_servers
         << " | trials=" << trials
         << " | avg wait=" << (total_avg / trials)
         << " minutes\n";
}

int main() {
    const int trials = 30;
    const int n_customers = 200;

    cout << "Queue simulator quick experiments\n";

    // Single-server comparisons
    run_one_setting(1, false, trials, n_customers); // FIFO, 1 server
    run_one_setting(1, true,  trials, n_customers); // Priority, 1 server

    // Multi-server shared-queue comparisons (3 servers)
    run_one_setting(3, false, trials, n_customers); // FIFO, 3 servers
    run_one_setting(3, true,  trials, n_customers); // Priority, 3 servers

    // Larger server pool
    run_one_setting(8, false, trials, n_customers);
    run_one_setting(8, true,  trials, n_customers);

    return 0;
}