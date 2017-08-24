/**
    We approach this problem by dynamic programming, with a multimap to memoize all (depth, index) pair
    The relationship of a child's (depth, index) and the parent is:
    (depth, index) of left child = (depth + 1, index * 2) of parent
    (depth, index) of right child = (depth + 1, index * 2 + 1) of parent
    First, pre-order walk thorough the tree (pre-order is to ensure small depths preceeds large depths in multimap),
    and memoize all (depth, index) by the relationship above
    Second, based on the multimap, whose values are ordered using min-heap given a key, find the width of each level and hence max width
    
    Runtime: first step: O(n), second step: O(n), total: O(n)
    Extra space cost: O(n) for memoization

/**
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void traverse(TreeNode* t, int depth, int ind){
        pos.insert(std::make_pair(depth, ind));
        if(t->left) traverse(t->left, depth+1, ind*2);
        if(t->right) traverse(t->right, depth+1, ind*2+1);
    }
      
    int widthOfBinaryTree(TreeNode* root) {
        // Create multimap
        pos.insert(std::make_pair(0, 0));
        if(root->left) traverse(root->left, 1, 0);
        if(root->right) traverse(root->right, 1, 1);
        
        // Find max width
        int max_width = 0;
        int begin_ind = 0;
        int prev_depth = 0;
        int prev_ind = 0;
        for(std::multimap<int, int>::iterator it = pos.begin(); it != pos.end(); ++it){
            int depth = it->first;
            int ind = it->second;
            if(depth != prev_depth){ // New depth reached
                int width = prev_ind - begin_ind + 1;
                if(width > max_width) max_width = width;
                begin_ind = ind;
            }
            prev_depth = depth;
            prev_ind = ind;
        } // Corner case: last depth
        int width = prev_ind - begin_ind + 1;
        if(width > max_width) max_width = width;
        
        return max_width;
        
    }
private:
    std::multimap<int, int> pos; // depth, index
};