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
    int pathSum(TreeNode* root, int sum) {
        build(root, sum);
        return count;
    }
private:
    struct TreeNodeWithSum{
        TreeNode* n;
        vector<int> sums;
    };
    
    int count = 0;
    
    TreeNodeWithSum* build(TreeNode* root, int sum){
        if(!root){return 0;}
        int v = root->val;
        vector<int> l_sums, r_sums;
        if(root->left){
            TreeNodeWithSum* l = build(root->left, sum);
            l_sums = l->sums;
        }
        if(root->right){
            TreeNodeWithSum* r = build(root->right, sum);
            r_sums = r->sums;
        }
        TreeNodeWithSum* rws = new TreeNodeWithSum(); rws->n = root;
        (rws->sums).push_back(v);
        if(v == sum){count++;}
        for(int i = 0; i < l_sums.size(); i++){
            int vl = l_sums[i]+v;
            (rws->sums).push_back(vl);
            if(vl == sum){count++;}
        }
        for(int i = 0; i < r_sums.size(); i++){
            int vr = r_sums[i]+v;
            (rws->sums).push_back(vr);
            if(vr == sum){count++;}
        }
        return rws;
    }
};