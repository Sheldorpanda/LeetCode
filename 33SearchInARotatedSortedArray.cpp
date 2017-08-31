class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(!nums.size()){return -1;}
        return binary_search(nums, target, 0, nums.size()-1);
    }

private:
    int binary_search(vector<int>& nums, int target, int min, int max){
        if(min >= max){
            if(target == nums[min]){return min;}
            else{return -1;}
        }
        if(nums[max] < nums[min]){
            int mid = (max+min)/2;
            if(nums[mid] == target){return mid;}
            int test = binary_search(nums, target, mid+1, max);
            if(test != -1){
                return test;
            } else {
                return binary_search(nums, target, min, mid-1);
            }
        }
        // Normal binary search
        int mid = (max + min)/2;
        if(nums[mid] > target) {return binary_search(nums, target, min, mid - 1);}
        else if(nums[mid] < target) {return binary_search(nums, target, mid + 1, max);}
        else{return mid;}
    }

};