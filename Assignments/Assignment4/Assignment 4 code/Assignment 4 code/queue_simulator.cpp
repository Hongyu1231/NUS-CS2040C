#include "queue_simulator.h"
#include "heap.hpp"

vector<Customer> QueueSimulator::simulateQueue(
    const vector<Customer>& customers) {
    // TODO: Implement this function.
    vector<Customer> result = customers;
    if (!result.size()) {
        return result;
    }
    else {
        if (_num_servers == 1 && !_priority_order) {
            int t = 0;
            for (auto& c : result) {
                c.set_compare_by_processing_time(false);
                if (c.arrival_time() > t) {
                    t = c.arrival_time();
                }
                c.set_service_time(t);
                t += c.processing_time();
            }
            return result;
        }
        else if (_num_servers == 1 && _priority_order) {
            int t = result[0].arrival_time();
            int idx = 0;
            int Size = result.size();
            int served = 0;
            Heap<Customer> heap;
            vector<Customer> final;
            final.reserve(Size);
            while (served < Size)
            {
                while (idx < Size && result[idx].arrival_time() <= t) {
                    result[idx].set_compare_by_processing_time(true);
                    heap.insert(result[idx]);
                    idx++;
                }
                
                if (heap.empty()) {
                    if (idx < Size) {
                        t = result[idx].arrival_time();
                        continue;
                    } else {
                        break; 
                    }
                }

                Customer c = heap.extractMax();

                int index = -1;
                for (int i = 0; i < Size; i++) {
                    if (result[i].service_time() == -1 && result[i].arrival_time() == c.arrival_time() && result[i].processing_time() == c.processing_time()) {
                        index = i;
                        if (index != -1) {
                            result[index].set_service_time(t);
                            t += c.processing_time();
                            served++;
                            final.push_back(result[index]);
                        }
                        break;
                    }
                }
            }
        return final;
        }
        else if (_num_servers > 1 && !_priority_order)
        {
            int t = result[0].arrival_time();
            vector<int> servers_time(_num_servers, t);
            for (auto &c : result)
            {
                c.set_compare_by_processing_time(false);
                bool wait = true;
                for (int i = 0; i < _num_servers; i++)
                {
                    if (servers_time[i] <= c.arrival_time()) {
                        wait = false;
                        c.set_service_time(c.arrival_time());
                        servers_time[i] = c.arrival_time() + c.processing_time();
                        break;
                    }
                }
                if (wait) {
                    int shortest_time = servers_time[0];
                    int fastest_server = 0;
                    for (int i = 1; i < _num_servers; i++)
                    {
                        if (servers_time[i] < shortest_time) {
                            shortest_time = servers_time[i];
                            fastest_server = i;
                        }
                    }
                    c.set_service_time(shortest_time);
                    servers_time[fastest_server] += c.processing_time();
                }
            }
            return result;
        } else if (_num_servers > 1 && _priority_order) {
            vector<int> servers_time(_num_servers, result[0].arrival_time());
            int idx = 0;
            int Size = result.size();
            int served = 0;
            vector<Customer> final;
            final.reserve(Size);
            Heap<Customer> heap;
            while (served < Size)
            {
                int shortest_time = servers_time[0];
                int fastest_server = 0;
                for (int i = 1; i < _num_servers; i++)
                {
                    if (servers_time[i] < shortest_time) {
                        shortest_time = servers_time[i];
                        fastest_server = i;
                    }
                }
                while (idx < Size && result[idx].arrival_time() <= shortest_time) {
                    result[idx].set_compare_by_processing_time(true);
                    heap.insert(result[idx]);
                    idx++;
                }

                if (heap.empty()) {
                    if (idx < Size) {
                        servers_time[fastest_server] = result[idx].arrival_time();
                        continue;
                    } else {
                        break; 
                    }
                }
                Customer c = heap.extractMax();

                int index = -1;
                for (int i = 0; i < Size; i++) {
                    if (result[i].service_time() == -1 && result[i].arrival_time() == c.arrival_time() && result[i].processing_time() == c.processing_time()) {
                        index = i;
                        if (index != -1) {
                            result[index].set_service_time(shortest_time);
                            servers_time[fastest_server] += c.processing_time();
                            served++;
                            final.push_back(result[index]);
                        }
                        break;
                    }
                }
            }
        return final;
        }
    }
    }

