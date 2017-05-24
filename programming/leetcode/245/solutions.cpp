class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        unordered_map<string, vector<int>> mapped;
        for(int i = 0; i < (int)words.size(); ++i){
            mapped[words[i]].push_back(i);
        }
        auto& idx1 = mapped[word1];
        auto& idx2 = mapped[word2];
        int cur_min = 100000000;
        if(word1 == word2){
            for(int j = 0; j + 1 < idx1.size(); ++j){
                cur_min = min(cur_min, abs(idx1[j] - idx1[j+1]));
            }
        }else{
            int i = 0, j = 0;
            while( i < idx1.size() && j < idx2.size()){
                cur_min = min(cur_min, abs(idx2[j] - idx1[i]));
                if(idx1[i] < idx2[j]) i++;
                else j++;
            }
        }
        return cur_min;
    }
};
