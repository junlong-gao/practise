/*
It is a trie, see 440.
*/
class Solution {
    void search(int prefix, int n, vector<int> *output) {
        for (int lastDigit = 0; lastDigit <= 9; ++lastDigit) {
            if (lastDigit == 0 && prefix == 0) {
                continue;
            }
            
            int nextNode = prefix * 10 + lastDigit;
            if (nextNode > n) {
                break;
            }
            output->push_back(nextNode);
            search(nextNode, n, output);
        }
    }
public:
    vector<int> lexicalOrder(int n) {
        vector<int> ret;
        search(0, n, &ret);
        return ret;
    }
};