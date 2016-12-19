// 461 Hamming Distance
// Easy
// Run time: 3 ms

# include <iostream>
using namespace std;

class Solution{
public:
  int hammingDistance(int x, int y){
    int mask = 1;
    int d = 0;
    for(int i = 0; i < 31; i++){
      d += (((mask << i) & x) != ((mask << i) & y));
    }
    return d;
  }
};
