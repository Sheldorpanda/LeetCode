/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        traverse(root);
        it = t_list.begin();
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return it != t_list.end();
    }

    /** @return the next smallest number */
    int next() {
        int v = *it;
        it++;
        return(v);
        
    }
private:
    vector<int> t_list;
    vector<int>::iterator it;
 
    void traverse(TreeNode *root){
        if(!root){return;}
        if(root->left) traverse(root->left);
        t_list.push_back(root->val);
        if(root->right)traverse(root->right);
        return;
    }
  
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */