/*
if 1. removing all X will result the same
2. "XL" -> "LX" all L must be not left to the corresponding left
3. "RX" -> "XR" all R must be not right to the corresponding right.
*/
class Solution {
public:
    bool canTransform(string start, string end) {
        if (start.length() != end.length()) return false;
        int i = 0;
        int j = 0;

        while (i < start.size()) {
            while (i < start.size() && start[i] == 'X') {i++;}
            if (i == start.size()) break;

            while (j < end.size() && end[j] == 'X') {j++;}
            if (j == end.size()) return false;

            if (start[i] != end[j]) return false;
            if (start[i] == 'L' && i < j) return false;
            if (start[i] == 'R' && i > j) return false;

            i++;j++;
        }
        while(j < end.size()) {
            if (end[j] != 'X') return false;
            j++;
        }

        return true;
    }
};