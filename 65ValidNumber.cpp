/** 
    See more: https://www.tutorialspoint.com/cplusplus/cpp_constants_literals.htm
    We aproach this literal problem by regular expression without using the <regex> library
    A valid numerical can be integer or floating point.
    Int: 
        Dec: [+||-]^(0,1) [0-9]+ [u||l||ul||lu]^(0, 1)
        Oct: [+||-]^(0,1) 0 [0-7]+ [u||l||ul||lu]^(0, 1), subclass of Dec for regex
        Hex: [+||-]^(0,1) 0x [0-f]+ [u||l||ul||lu]^(0, 1)
        The u, l, ul and lu suffix are not applied in this problem
    Float:
        [+||-]^(0,1) [0.9]* . [0.9]+ [e[Dec - suffix]]^(0,1)
        [+||-]^(0,1) [0.9]+ . [0.9]* [e[Dec - suffix]]^(0,1)
    Before verifying the string, the spaces in the beginn and the end must be removed
    Runtime: Theta(n), extra space cost: Theta(1)
**/


class Solution {
public:
    bool isNumber(string s) {
        // Remove spaces
        int first_non_sp = 0; int last_non_sp = s.length() - 1;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == ' '){first_non_sp++; continue;} else {break;}
        }
        
        if(first_non_sp == s.length()){return 0;} // Special case: all spaces
        
        for(int i = s.length() - 1; i >= 0; i--){
            if(s[i] == ' '){last_non_sp--; continue;} else {break;}
        }
        
        int len = last_non_sp - first_non_sp + 1;
        s = s.substr(first_non_sp, len);         
        
        // Plus, minus sign
        if(s[0] == '+' || s[0] == '-'){s = s.substr(1);}
        if(s == "." || s == "e" || s == ""){return 0;} // Special cases: single dot, e, plus, minus
        
        // Hex
        if(s.substr(0, 2) == "0x"){
            for(int i = 2; i < len; i++){
                char c = s[i];
                if(c < '0' || c > 'f') return 0;
            }
            return 1;
        }
        
        // Dec, oct, float
        bool dot = 0;
        bool e = 0;
        bool num_prev_dot = 0;
        for(int i = 0; i < s.length(); i++){
            char c = s[i];
            if(c < '0' || c > '9'){
                // Case 1: '.'
                if(c == '.'){
                    if(i != 0){num_prev_dot = 1;}
                    dot = 1; s = s.substr(i+1); break;}
                // Case 2: 'e'
                else if(c == 'e'){
                    if(i == 0){return 0;}                
                    e = 1; s = s.substr(i+1); break;}
                // Case 3: other chars
                else {return 0;}
            }
        }
        
        if(dot){
            for(int i = 0; i < s.length(); i++){
                char c = s[i];
                // Case 1: 'e'
                if(c < '0' || c > '9'){
                    if(c == 'e'){
                        if(i == 0 && !num_prev_dot){return 0;}  
                        e = 1; s = s.substr(i+1); break;}
                    // Case 2: other chars
                    else {return 0;}
                }
            }
        }
        
        if(e){
            if(s[0] == '+' || s[0] == '-'){s = s.substr(1);}
            if(s == ""){return 0;} // Special cases: nothing after 'e', 'e+' or 'e-'
            for(int i = 0; i < s.length(); i++){
                char c = s[i];
                if(c < '0' || c > '9'){return 0;}
            }
        }
        
        return 1;
        
    }
};