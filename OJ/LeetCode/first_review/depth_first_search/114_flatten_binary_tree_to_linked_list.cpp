#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../tree_node.hpp"
using namespace std;

class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root) return;
        if (root->left) flatten(root->left);
        if (root->right) flatten(root->right);

        TreeNode* tmp = root->right;
        root->right = root->left;
        root->left = nullptr;

        while (root->right) root = root->right;

        root->right = tmp;
    }
};

int main() {
    return 0;
}
