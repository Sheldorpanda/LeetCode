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
    int findBottomLeftValue(TreeNode* root) {
        vector<int> result = bfs(root, 0);
        return result[0];
    }
    
private:
    vector<int> bfs(TreeNode* root, int dist){ // 0: val, 1: dist
        vector<int> result, l, r;
        if(!root){return result;}
        if(root->left){l = bfs(root->left, dist+1);}
        if(root->right){r = bfs(root->right, dist+1);}
        
        int max_val, max_d;
        if(!l.empty() && !r.empty()){
            if(l[1] >= r[1]){
                max_val = l[0]; max_d = l[1];
            }else{
                max_val = r[0]; max_d = r[1];
            }
        }else if(!l.empty()){
            max_val = l[0]; max_d = l[1];
        }else if(!r.empty()){
            max_val = r[0]; max_d = r[1];
        }else{
            max_val = root->val; max_d = dist;
        }
        
        result.push_back(max_val); result.push_back(max_d);
        return result;
    }
};