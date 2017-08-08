/**
    Given a line segement formed by two randomly drawn points p1, p2, it has a slope s
    From p1, extend to an arbitrary p3, if slope s' == s, p1, p2, p3 are in the same colinear set
    
    Algorithm:
    For a point pi:
        Calculate all slopes pipj, i != j
        Mergesort all slopes
        For all slopes, count the number of each distinct values, track the max
        
    Runtime: O(n^2 logn)

**/
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    
    // Subroutine: get slope from two points
    long double slope(Point& p1, Point& p2){
        long double s;
        if(p2.x - p1.x == 0) s = std::numeric_limits<double>::infinity();
        else s = static_cast<long double>(p2.y - p1.y)/(p2.x-p1.x);
        return s;
    }
    
    // Subroutine: mergesort
    // T must be comparable with operator< overwritten
    template <typename T>
    vector<T> merge(vector<T>& A1, vector<T>& A2){
        vector<T> M;
        while(!A1.empty() && !A2.empty()){
            T a1 = A1.at(0); T a2 = A2.at(0);
            if(a1 < a2) {M.push_back(a1); A1.erase(A1.begin());}
            else {M.push_back(a2); A2.erase(A2.begin());}
        }
        if(!A1.empty()){M.insert(M.end(), A1.begin(), A1.end());}
        else{M.insert(M.end(), A2.begin(), A2.end());}
        return M;
    }
    
    template <typename T>
    vector<T> mergesort(vector<T>& A){
        if(A.size() == 1) {return A;}
        vector<T> head(A.begin(), A.begin() + A.size()/2);
        vector<T> tail(A.begin() + A.size()/2, A.end());
        vector<T> A1 = mergesort(head);
        vector<T> A2 = mergesort(tail);
        return merge(A1, A2);
    }
    
    // Main algo
    int maxPoints(vector<Point>& points) {        
        if(points.size() == 0) return 0;
        if(points.size() == 1) return 1;
        if(points.size() == 2) return 2;
        int max = 2;
        while(!points.empty()){
            Point p1 = points.at(0); points.erase(points.begin()); 
            vector<long double> S, S_sorted;
            int same = 0;
            for(vector<Point>::iterator it= points.begin(); it != points.end(); ++it){
                Point p2 = *it;
                if(p1.x == p2.x && p1.y == p2.y){same++;}
                else{S.push_back(slope(p1, p2));}
            } 
            if(same + 1 > max){max = same + 1;}
            if(S.empty()){break;}
            S_sorted = mergesort(S);
            int count = 1; 
            for(vector<long double>::iterator it = S_sorted.begin()+1; it != S_sorted.end(); ++it){
                if(*it == *(it-1)){count++;}
                else{
                    if(count + same + 1 > max){max = count + same + 1;}
                    count = 1;
                }
            }
            if(count + same + 1 > max){max = count + same + 1;}
        }
        return max;
    }
};