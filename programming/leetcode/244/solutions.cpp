class WordDistance {
public:
    WordDistance(vector<string>& words) {
        for(int i=0;i<words.size();i++)
            wordMap[words[i]].push_back(i);
    }
    int shortest(string word1, string word2) {
        int  i=0, j=0, dist = INT_MAX;
        while(i < wordMap[word1].size() && j <wordMap[word2].size()) { 
            dist = min(dist, abs(wordMap[word1][i] - wordMap[word2][j]));
            wordMap[word1][i]<wordMap[word2][j]?i++:j++;
        }
        return dist;
    }
private:
    unordered_map<string, vector<int>> wordMap;
};

// Your WordDistance object will be instantiated and called as such:
// WordDistance wordDistance(words);
// wordDistance.shortest("word1", "word2");
// wordDistance.shortest("anotherWord1", "anotherWord2");
