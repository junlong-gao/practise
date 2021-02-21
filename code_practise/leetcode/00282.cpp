class Solution {
    using ll = long long;
    void search(string sofar, ll tot, ll prev, ll idx, const string &num, ll target, vector<string> *output) {
        if (idx == num.size()) {
            if (tot == target) {
                output->push_back(sofar);
            }
            return;
        }

        ll oprand = 0;
        for (int nIdx = idx; nIdx < num.size(); ++nIdx) {
            oprand = oprand * 10 + (num[nIdx] - '0');

            if (idx == 0) {
                search(to_string(oprand), oprand, oprand, nIdx + 1, num, target, output);
            } else {
                search(sofar+"+"+to_string(oprand), tot + oprand, oprand, nIdx + 1, num, target, output);
                search(sofar+"-"+to_string(oprand), tot - oprand, -oprand, nIdx + 1, num, target, output);
                search(sofar+"*"+to_string(oprand), tot - prev + prev * oprand, prev * oprand, nIdx + 1, num, target, output);
            }

            if (num[idx] == '0') {
                break;
            }
        }
    }
public:
    vector<string> addOperators(string num, int target) {
        vector<string> output;
        search("", 0, 0, 0, num, target, &output);
        return output;
    }
};