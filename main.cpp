#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <string>
#include <algorithm>

using std::shared_ptr;

struct TreeNode {
    int val;
    shared_ptr<TreeNode> left, right;
    TreeNode(int aval)
        : val(aval), left(nullptr), right(nullptr) {}

    bool isLeaf(){return left == nullptr && right == nullptr;}
    void print() {
        if (left != nullptr || right != nullptr) {
            std::cout << "val = " << val
                      << "\t left = "
                      << (left != nullptr ? std::to_string(left->val) : "null")
                      << "\n\t right = "
                      << (right != nullptr ? std::to_string(right->val) : "null")
                      << std::endl;
        }
        else {
            std::cout << "val = " << val << std::endl;
        }
    }
};

using pNode = shared_ptr<TreeNode>;
void printTree(const pNode & root) {
    std::queue<pNode> qu;
    qu.push(root);
    while (!qu.empty()) {
        qu.front()->print();
        if (qu.front()->left != nullptr)
            qu.push(qu.front()->left);
        if (qu.front()->right != nullptr)
            qu.push(qu.front()->right);
        qu.pop();
    }
}

using std::vector;

class solution {
  public:
    vector<vector<int>> findLeaves(pNode & root) {
        vector<vector<int>> result;
        vector<int> leaves;
        while (root != nullptr) {
            // std::cout << "before" << std::endl;
            // printTree(root);
            leaves = findLeavesUpdateTree(root);
            result.push_back(leaves);
            // std::cout << "after" << std::endl;
            // printTree(root);
        }
        // result.push_back(vector<int>{root->val});
        return result;
    }

    vector<int> findLeavesUpdateTree(pNode & root) {
        vector<int> leaves;
        std::queue<pNode> qu;
        if (root->isLeaf()) {
            leaves.push_back(root->val);
            root = nullptr;
        }
        else {
            qu.push(root);
            while (!qu.empty()) {
                auto curr = qu.front();
                qu.pop();
                if (curr->left != nullptr) {
                    if (curr->left->isLeaf()) {
                        leaves.push_back(curr->left->val);
                        curr->left = nullptr;
                    }
                    else
                        qu.push(curr->left);
                }
                if (curr->right != nullptr) {
                    if (curr->right->isLeaf()) {
                        leaves.push_back(curr->right->val);
                        curr->right = nullptr;
                    }
                    else
                        qu.push(curr->right);
                }
            }
        }
        return leaves;
    }
};


int main() {
    shared_ptr<TreeNode> root;
    root = std::make_shared<TreeNode>(1);
    root->left = std::make_shared<TreeNode>(2);
    root->right = std::make_shared<TreeNode>(3);
    root->left->left = std::make_shared<TreeNode>(4);
    root->left->right = std::make_shared<TreeNode>(5);

    // printTree(root);

    solution soln;
    auto vecs = soln.findLeaves(root);
    for (auto & vec : vecs) {
        std::cout << "[";
        std::for_each(vec.begin(), vec.end()-1, [](auto & i){std::cout << i << " ";});
        std::cout << vec.back();
        std::cout << "]";
    }
    std::cout << std::endl;
}
