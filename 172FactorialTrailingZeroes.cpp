class Solution {
public:
    int trailingZeroes(int n) {
        int count = 0;
        int exp = 1;
        int five_exp = 5;
        double log_five_n = log_b(5, (double)n);
        while(exp <= log_five_n){
            //cout<<five_exp<<endl;
            count += n / five_exp;
            five_exp = pow(5, ++exp);
        }
        return count;
    }

private:
    double log_b(double base, double x){
        return log(x)/log(base);
    }
};