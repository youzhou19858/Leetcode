#include "cppCommonHeaders.hpp"

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
  template <bool traverseFromLeft = true>
  inline TreeNode*& getKid(TreeNode* node) {
    if constexpr (traverseFromLeft) {
      return node->left;
    } else {
      return node->right;
    }
  }
  template <bool traverseFromLeft = true>
  vector<int> dfs(vector<pair<TreeNode*, bool>> tree) {
    vector<int> bdry{}, leaves{};
    while (tree.size()) {
      TreeNode*& kid = getKid<traverseFromLeft>(tree.back().first);
      for (; kid; kid = getKid<traverseFromLeft>(tree.back().first)) {
        if (tree.back().second) {
          bdry.push_back(tree.back().first->val);
        }
        tree.emplace_back(kid, tree.back().second);
        kid = nullptr;
      }
      if (TreeNode*& kid = getKid<!traverseFromLeft>(tree.back().first); kid) {
        if (tree.back().second) {
          bdry.push_back(tree.back().first->val);
        }
        tree.emplace_back(kid, tree.back().second);
        kid = nullptr;
      } else {
        leaves.push_back(tree.back().first->val);
        tree.pop_back();
        while (tree.size() && !getKid<!traverseFromLeft>(tree.back().first)) {
          tree.pop_back();
        }
        if (tree.empty()) {
          break;
        }
        TreeNode*& nonBdryKid = getKid<!traverseFromLeft>(tree.back().first);
        tree.emplace_back(nonBdryKid, false);
        nonBdryKid = nullptr;
      }
    }
    copy(leaves.begin(), leaves.end(), back_inserter(bdry));
    if constexpr (traverseFromLeft) {
      return bdry;
    } else {
      return {bdry.rbegin(), bdry.rend()};
    }
  }

 public:
  vector<int> boundaryOfBinaryTree(TreeNode* root) {
    vector<int> ret{root->val};
    if (root->left) {
      auto l = dfs({{root->left, true}});
      copy(l.begin(), l.end(), back_inserter(ret));
    }
    if (root->right) {
      auto r = dfs<false>({{root->right, true}});
      copy(r.begin(), r.end(), back_inserter(ret));
    }
    return ret;
  }
};