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
    vector<int> findFrequentTreeSum(TreeNode* root) {
        traverse(root);
        std::sort(sums.begin(), sums.end());
        return count_max();
    }
private:   
    vector<int> sums;
    
    void traverse(TreeNode* root){
        if(!root){return;}
        if(root->left){traverse(root->left); (root->val) += (root->left->val);}
        if(root->right){traverse(root->right); (root->val) += (root->right->val);}
        sums.push_back(root->val);
    }
    
    vector<int> count_max(){
        if(sums.size() <= 1){return sums;}
        vector<int> max;
        int freq = 1; int max_freq = 1; int prev = sums[0];
        for(vector<int>::iterator it = sums.begin()+1; it < sums.end(); ++it){
            int curr = *it;
            if(curr != prev){
                if(freq < max_freq){
                    ;
                }else if(freq == max_freq){
                    max.push_back(prev);
                }else{
                    max_freq = freq;
                    max.clear();
                    max.push_back(prev);
                }
                freq = 1;
            }else{
                freq++;
            }
            prev = curr;
        }
        if(freq == max_freq){
            max.push_back(prev);
        }else if(freq > max_freq){
            max.clear();
            max.push_back(prev);
        }
        return max;
    }
};