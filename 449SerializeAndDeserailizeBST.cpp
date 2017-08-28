/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s("");
        if(!root){return s;}
        s += (to_string(root->val) + " ");
        if(root->left){s += serialize(root->left);}
        if(root->right){s += serialize(root->right);}
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        root = 0;             
        string curr("");
        for(string::iterator it = data.begin(); it != data.end(); ++it){
            if((*it) == ' '){
                int v = atoi(curr.c_str());
                if(!root){
                    root = new TreeNode(v);
                    root->left = 0; root->right = 0;
                }else{
                    bst_insert(root, v);
                }
                curr = "";
                continue;
            }
            curr += (*it);
        }  
        return root;
    }
    
private:
    TreeNode * root;
    
    void bst_insert(TreeNode* root, int v){
        //cout<<"v "<<v<<endl;
        if(v < (root->val)){
            if((root->left)){bst_insert(root->left, v);}
            else{
                TreeNode * l = new TreeNode(v); l->left = 0; l->right = 0;
                root->left = l;
            }
        } else if (v > (root->val)){
            if((root->right)){bst_insert(root->right, v);}
            else{
                TreeNode * r = new TreeNode(v); r->left = 0; r->right = 0;
                root->right = r;
            }
        }
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));