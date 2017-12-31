#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
    int my_abs(int a){
        return a>0? a:-a;
    }
    const int INF = 10000000;
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        unordered_map<string,vector<int>> mapped;
        for(int i = 0; i < (int)words.size(); ++i){
            mapped[words[i]].push_back(i);
        }
        int cur_diff = INF;
        if(mapped[word2].size() < mapped[word1].size())
            swap(word1, word2);
        auto& first = mapped[word1];
        auto& second = mapped[word2];

        for(int i = 0; i < (int)first.size(); i++){
            int a = INF, b = INF;
            auto it = upper_bound(second.begin(), second.end(), first[i]);
            if(it!=second.end()) a = my_abs(*it - first[i]);
            if(it!=second.begin()) b = my_abs(*(--it) - first[i]);
            cur_diff = min(cur_diff,min(a,b));
        }
        return cur_diff;
    }
};

int main(){
    Solution s;
    vector<string> words = {"a", "c", "b", "c", "d", "a"};
    string word1 = "a", word2 = "b";
    cout << s.shortestDistance(words, word1, word2);
    return 0;
}
