class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> ref;
        int fmax = 0;
        for (int i = 0; i < tasks.size(); ++i) {
            ref[tasks[i]]++;
            fmax = max(fmax, ref[tasks[i]]);
        }
        int count = 0;
        for (auto &pr:ref) {
            if (pr.second == fmax) {
                count++;
            }
        }
        // Now here is the tricky part...
        /*
               A B
             - A B ...
             | ...
      fmax - 1 A B
             | ...
             - A B ...
                   |<- n + 1 - count ->|
        Any remaining tasks in tasks \ fmax * count can fit in the above region (fmax - 1) * (n + 1 - count).
        If they cannot fit in total, then there exists a schedule to run all tasks without idle.
        */
        if ((int)(tasks.size() - fmax * count) <= (int)((fmax - 1) * (n + 1 - count))) {
            return (fmax - 1) * (n + 1) + count;
        } else {
            return tasks.size();
        }
    }
};
