#include <iostream>
#include <cassert>
#include "BST.hpp"
#include <vector>

// ================================================================
// Helper: Check BST property
template <typename T>
bool isBST(const Node<T>* node, const T* min = nullptr, const T* max = nullptr) {
    if (!node) return true;
    if (min && node->element <= *min) return false;
    if (max && node->element >= *max) return false;
    return isBST(node->left, min, &node->element) &&
        isBST(node->right, &node->element, max);
}

// ================================================================
// Helper: Validate AVL balance & height consistency recursively
template <typename T>
int validateAVL(const Node<T>* node, bool& ok, std::ostream* diag = nullptr) {
    if (!node) return -1;

    int lh = validateAVL(node->left, ok, diag);
    int rh = validateAVL(node->right, ok, diag);

    // Balance factor check
    int bf = lh - rh;
    if (bf < -1 || bf > 1) {
        ok = false;
        if (diag) {
            *diag << "[AVL ERROR] Node " << my_to_string(node->element)
                << " has imbalance (lh=" << lh << ", rh=" << rh << ")\n";
        }
    }

    // Height consistency check
    int expectedHeight = std::max(lh, rh) + 1;
    if (node->height != expectedHeight) {
        ok = false;
        if (diag) {
            *diag << "[AVL ERROR] Node " << my_to_string(node->element)
                << " has incorrect height (stored=" << node->height
                << ", expected=" << expectedHeight << ")\n";
        }
    }

    return expectedHeight;
}

template <typename T>
bool isAVLValid(Tree<T>& tree, std::ostream* diag = nullptr) {
    bool ok = true;
    validateAVL(tree.root(), ok, diag);
    return ok;
}

// ================================================================
// Test 1: Basic insert, size, contains, min/max, traversal
void basicTests() {
    Tree<int> t;
    assert(t.empty());
    assert(t.size() == 0);
    assert(t.height() == -1);

    // Insert values
    t.insert(10);
    t.insert(5);
    t.insert(20);
    t.insert(15);
    t.insert(25);

    assert(!t.empty());
    assert(t.size() == 5);
    assert(t.contains(10));
    assert(!t.contains(999));

    // Extremes
    assert(t.min() == 5);
    assert(t.max() == 25);

    // Traversals
    std::cout << "In-order:    " << t.in_order() << "\n";
    std::cout << "Pre-order:   " << t.pre_order() << "\n";
    std::cout << "Post-order:  " << t.post_order() << "\n";

    assert(t.in_order() == "5 10 15 20 25");

    // Successor tests
    assert(t.successor(5) == 10);
    assert(t.successor(10) == 15);
    assert(t.successor(15) == 20);
    assert(t.successor(20) == 25);

    try {
        t.successor(25);
        assert(false && "Expected out_of_range for max element");
    }
    catch (const std::out_of_range&) {
        std::cout << "Successor correctly threw for max element.\n";
    }

    // BST & AVL checks
    assert(isBST(t.root()));
    assert(isAVLValid(t, &std::cerr));

    std::cout << "✅ Basic tests passed.\n";
}

// ================================================================
// Test 2: Copy constructor & assignment operator
void copyAndAssignmentTests() {
    Tree<int> a;
    for (int v : {10, 5, 20, 15, 25}) a.insert(v);

    Tree<int> b = a; // copy constructor
    assert(b.in_order() == a.in_order());
    assert(b.size() == a.size());

    // Modify original
    a.insert(30);
    assert(a.size() == 6);
    assert(b.size() == 5); // deep copy confirmed

    Tree<int> c;
    c = a; // assignment operator
    assert(c.in_order() == a.in_order());

    // AVL checks
    assert(isAVLValid(a, &std::cerr));
    assert(isAVLValid(b, &std::cerr));
    assert(isAVLValid(c, &std::cerr));

    std::cout << "✅ Copy & assignment tests passed.\n";
}

// ================================================================
// Test 3: Complex AVL rebalancing scenarios
void avlRotationTests() {
    Tree<int> t;

    // Insert elements causing rotations
    std::vector<int> values = { 30, 20, 10, 25, 40, 50, 22 };
    for (int v : values) {
        t.insert(v);
        assert(isAVLValid(t, &std::cerr));
    }

    std::cout << "\nTree after complex inserts:\n";
    std::cout << t.to_string(true) << "\n";

    // Final validations
    assert(isBST(t.root()));
    assert(isAVLValid(t, &std::cerr));

    std::cout << "✅ AVL rotation tests passed.\n";
}

// ================================================================
// Test 4: Edge cases (empty tree, single node)
void edgeCaseTests() {
    Tree<int> t;
    try {
        t.min();
        assert(false && "Expected exception on empty min()");
    }
    catch (const std::runtime_error&) {}

    try {
        t.max();
        assert(false && "Expected exception on empty max()");
    }
    catch (const std::runtime_error&) {}

    try {
        t.successor(42);
        assert(false && "Expected exception on empty successor()");
    }
    catch (const std::runtime_error&) {}

    t.insert(100);
    assert(t.min() == 100);
    assert(t.max() == 100);
    assert(t.size() == 1);
    assert(t.height() == 0);

    std::cout << "✅ Edge case tests passed.\n";
}

// ================================================================
int main() {
    std::cout << "🚀 Starting Tree tests...\n\n";

    basicTests();
    copyAndAssignmentTests();
    avlRotationTests();
    edgeCaseTests();

    std::cout << "\n🎉 All tests passed successfully!\n";
    return 0;
}
