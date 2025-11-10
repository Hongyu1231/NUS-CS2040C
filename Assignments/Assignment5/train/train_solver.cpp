#include <iostream>
#include <vector>
#include <string> // 需要包含 string 头文件

// 我们必须包含项目的所有依赖项
#include "graph.h"
#include "shortest_path.h"

// 来自 A4 的堆将由 Coursemology 包含，
// 但对于本地测试，你必须包含它。
#include "heap.hpp" 

// 包含 stdexcept 以便能够抛出 runtime_error (如果 shortestPath 中有验证)
#include <stdexcept> 

using std::cout;
using std::endl;
using std::vector;
using std::string; // 需要显式声明使用 std::string
using std::to_string; // 需要包含 string 头文件并使用 to_string

/**
 * @brief 这是任务 2 的主要求解器。
 * 它将调用你在 shortest_path.cpp 中编写的 shortestPath 函数。
 */
int main() {
    // 10 个顶点，A-J
    Graph g(10); 
    
    // 从整数索引 (0-9) 映射回字母 (A-J)
    char int_to_letter[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

 // --- 为学生 ID 自动生成的 C++ 代码：A0311920U ---
// 将此代码复制并粘贴到 train_solver.cpp 的 main() 函数中


    char source_letter = 'A';
    char dest_letter = 'G';
    int source = 0;
    int dest = 6;

    // --- 定义图的边 ---
    g.addEdge(0, 1, 74); // A -> B
    g.addEdge(1, 5, 146); // B -> F
    g.addEdge(1, 8, 91); // B -> I
    g.addEdge(1, 9, 85); // B -> J
    g.addEdge(2, 0, 128); // C -> A
    g.addEdge(2, 1, 172); // C -> B
    g.addEdge(2, 8, 133); // C -> I
    g.addEdge(3, 1, 94); // D -> B
    g.addEdge(3, 5, 25); // D -> F
    g.addEdge(3, 6, 173); // D -> G
    g.addEdge(3, 9, 121); // D -> J
    g.addEdge(4, 0, 16); // E -> A
    g.addEdge(4, 6, 119); // E -> G
    g.addEdge(4, 8, 149); // E -> I
    g.addEdge(5, 1, 198); // F -> B
    g.addEdge(5, 2, 180); // F -> C
    g.addEdge(5, 4, 152); // F -> E
    g.addEdge(6, 1, 141); // G -> B
    g.addEdge(6, 3, 198); // G -> D
    g.addEdge(6, 7, 50); // G -> H
    g.addEdge(7, 0, 189); // H -> A
    g.addEdge(7, 1, 169); // H -> B
    g.addEdge(7, 3, 50); // H -> D
    g.addEdge(8, 0, 199); // I -> A
    g.addEdge(8, 4, 126); // I -> E

    // --- 自动生成的代码结束 ---

    // --- 运行求解器 ---
    // 检查 source 和 dest 是否已有效设置 (即 Python 脚本成功运行并粘贴了代码)
    if (source == -1 || dest == -1) {
        cout << "错误:source 或 dest 未从 Python 脚本正确设置。" << endl;
        cout << "请确保已运行 Python 脚本并将输出粘贴到此文件中。" << endl;
        return 1; // 表示错误退出
    }
    
    cout << "正在查找从 " << source_letter 
         << " (" << source << ") 到 " << dest_letter 
         << " (" << dest << ") 的最短路径" << endl;

    Path p = shortestPath(g, source, dest);

    // --- 打印结果 ---
    cout << "\n--- 你的解答 ---" << endl;
    
    // 1. 打印学生 ID (用于 Coursemology)
    // !!! 重要提示：将这里更改为你的学生 ID !!!
    cout << "student id = \"A0311920U\"" << endl; 
    
    // 2. 打印路径
    cout << "path = [";
    const vector<int>& path_vec = p.path();
    // 使用 size_t 以避免有符号/无符号比较警告
    for (size_t i = 0; i < path_vec.size(); ++i) { 
        // 检查索引是否有效
        if (path_vec[i] >= 0 && path_vec[i] < 10) {
             cout << "'" << int_to_letter[path_vec[i]] << "'";
        } else {
             cout << "'?'"; // 如果索引无效，打印问号
        }
       
        if (i != path_vec.size() - 1) { 
            cout << ", ";
        }
    }
    cout << "]" << endl;

    // 3. 打印长度
    cout << "length = " << p.total_distance() << endl;

    return 0; // 表示成功退出
}

