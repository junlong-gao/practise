// Only take the most frequent 2 char sofar and append them to the result;
// it is important to show that this construction cannot introduce adjacent repetition
// let X Y be current top 2, Z is the 3rd. when their is a count tie, use char X Y Z order to break tie
//  X Y is appended, after dec count of X Y,
//     if X.count > Y.count
//         then if Z.count  > X.count , we get next Z X after X Y
//              if X.count > Z.count >= Y.count, we get either X Z or X Y after X Y
//              if X.count > Y.count > Z.count, we get X Y after X Y.
//     else
//         then if Z.count > (X.count = Y.count), we get Z X after X Y
//              if Z.count = X.count = Y.count we get Z X or X Z or Z X or X Y (char order)
//              if Z.count < (X.count = Y.count) we get X Y
// In any case, it is impossible to have Y after X Y
// when the queue has only 1 element, we append it to ret and check repetition.
class Solution {
    struct ent_t {
        int count;
        char c;
    };
public:
    string reorganizeString(string S) {
        auto cmp = [](const ent_t &l, const ent_t &r) {
           return l.count < r.count;  
        };
        priority_queue<ent_t, vector<ent_t>, decltype(cmp)> q(cmp);
        unordered_map<char, int> refcount;
        for (auto c : S) {
            refcount[c]++;
        }
        for (auto pr : refcount) {
            q.push(ent_t{pr.second, pr.first});
        }
        
        int count = 0;
        string ret;
        char last = 0;
        while (q.size()) {
            auto top = q.top();
            q.pop();
            if (ret.size() && ret.back() == top.c) {
                return "";
            }
            ret.push_back(top.c);
            top.count--;
            if (q.empty()) {
                if (top.count == 0) {
                    break;
                } else {
                    return "";
                }
            }
            auto secTop = q.top();
            q.pop();
            assert(secTop.c != top.c);
            ret.push_back(secTop.c);
            secTop.count--;
            if (top.count > 0) {
                q.push(top);
            }
            if (secTop.count > 0) {
                q.push(secTop);
            }
        }
        
        return ret;
    }
};
