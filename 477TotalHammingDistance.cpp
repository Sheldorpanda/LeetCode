// 477 Total Hamming Distance
// Medium
// Runtime: 123 ms

# include <iostream>
# include <vector>
using namespace std;

class Solution{
public:
  int totalHamming(vector<int>& nums) {
    int length = nums.size();
    int d = 0;
    for(int i = 0; i < 31; i++){
      int count = 0;
      for(int j = 0; j < length; j++){
	count += (nums.at(j) & (1 << i)) >> i;
      }
      d += count * (length - count);
    }
    return d;
  }
};
