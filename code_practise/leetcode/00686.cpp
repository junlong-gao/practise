class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        string t;
        int count = 0;
	    while (t.length() < B.length()) {
            t += A;
            count ++;
        }
        /*
        let k be the first interger >= 1 such that
        B in kA but not in (k - 1) A
        then, if B is not in kA and (k + 1)A, then B is not in any jA, for j >= k
        proof:
        if B is in some jA, j > (k+1), then from hyposis we see B must cover a range of
        A, of either k of them or k + 1 of them.
        contradiction.
        */ 
        // k
        if (t.find(B) != std::string::npos) {
            return count;
        }
        // k + 1
        t += A;
        return t.find(B) != std::string::npos ? count + 1 : -1;
    }

};
