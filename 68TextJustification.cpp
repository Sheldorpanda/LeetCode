/**
    Greedily add words (each word plus one space in length) until the total length > maxWidth + 1 (abandon last space)
    Abandon the last word, the other words form a line
    Given a vector of k words that form a line:
        if k == 1, left justified
        else we need k-1 space areas, each with (L - sum(word length))/(k-1), find the most even way to distribute spaces
**/


class Solution {
public:
    string justifyOneLine(vector<string>& words, int maxWidth, int totalLength, bool lastLine){
        string s;
        const int k = words.size();
        if(k == 1 || lastLine){ // Left justify
            for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
                s += *it;
                s += " ";
            }
            s = s.substr(0, s.length() - 1);
            int len = s.length();
            for(int i = len; i < maxWidth; i++){s += " ";}
        } else { // Full justify, to find out the most even space distribution, need the ceiling and floor number of spaces
            int floor_sp = (maxWidth - totalLength)/(k-1);
            int ceiling_sp = floor_sp+1;
            int num_ceiling = 0; int num_sp = maxWidth - totalLength;
            if((maxWidth - totalLength)%(k-1)){
                for(int i = 0; i < k-1; i++){
                    if(i * ceiling_sp + (k - 1 - i) * floor_sp == num_sp){
                        num_ceiling = i;
                    }
                }
            }
            // Distribute ceiling spaces
            for(vector<string>::iterator it = words.begin(); it < words.begin() + num_ceiling; ++it){
                s += *it;
                for(int i = 0; i < ceiling_sp; i++){s += " ";}
            }
            // Distribute floor spaces
            for(vector<string>::iterator it = words.begin()+num_ceiling; it != words.end(); ++it){
                s += *it;
                for(int i = 0; i < floor_sp; i++){s += " ";}
            }
            s = s.substr(0, s.length() - floor_sp);
        }
        return s;
    } 
    
    // Main algo
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int length = 0; vector<string> line; vector<string> justified;
        for(vector<string>:: iterator it = words.begin(); it != words.end(); ++it){
            string word = *it;
            length += word.length();
            int min_length = length + line.size();
            if(min_length > maxWidth){ // Case 1: next greedy addition exceed max width
                length -= word.length();
                justified.push_back(justifyOneLine(line, maxWidth, length, 0));          
                length = 0; line.clear(); it--;
            } else if(min_length == maxWidth) { // Case 2: addition is equal to max width
                line.push_back(word);
                justified.push_back(justifyOneLine(line, maxWidth, length, 0));
                length = 0; line.clear();         
            }else{     // Case 3: addition still not meet max width
                line.push_back(word);
            }
        }
        if(line.size()){
            justified.push_back(justifyOneLine(line, maxWidth, length, 1));
        }
        return justified;
    }
};