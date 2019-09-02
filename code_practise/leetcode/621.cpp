class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        //cout << " --- " << endl;
        vector<int> pending(26, 0);
        for (auto t : tasks) {
            pending[t - 'A']++;
        }
        
        int m = 0;
        for (int i = 0; i < pending.size(); ++i) {
            m = max(pending[i], m);
        }
        
        int nm = 0;
        for (int i = 0; i < pending.size(); ++i) {
            if (pending[i] == m) {
                nm++;
            }
        }
        
        // the scheduling diagram is:
        int remaining = (n + 1 - nm) * (m - 1);
        /*
        case 1 (n = 3):
        A B C D
        A B F /
        A B / /
        A B
        
        case 2 (n = 3):
        A B C D E
        A B C F
        A B C G
        A B
        or (n = 0)
        A B C
        A B
        A B
        */
        //cout << remaining << endl;
        if (remaining >= (int)tasks.size() - nm * m) {
            return nm * m + remaining;
        } else {
            return tasks.size();
        }
    }
};
