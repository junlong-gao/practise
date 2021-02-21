class Solution {
   bool is_pali(string& str){
      int i = 0, j = str.length() - 1;
      while(i < j){
            if(str[i] != str[j]) return false;
            ++i; --j;
      }
      return true;
   }
public:
   vector<vector<int>> palindromePairs(vector<string>& words) {
      unordered_map<int, unordered_set<int>> rst;
      unordered_map<string, int> revIdxOf;
      for(int i = 0; i < words.size(); ++i){
         string word = words[i];
         reverse(word.begin(), word.end());
         revIdxOf[word] = i;
      }
      for(int i = 0; i < words.size(); ++i){
         for(int j = 0; j <= words[i].size(); ++j){
            string s1 = words[i].substr(0, j);
            string s2 = words[i].substr(j);
            if(revIdxOf.find(s2)!=revIdxOf.end() && revIdxOf[s2] != i && is_pali(s1)){
               rst[revIdxOf[s2]].insert(i);
            }
            if(revIdxOf.find(s1)!=revIdxOf.end() && revIdxOf[s1] != i && is_pali(s2)){
               rst[i].insert(revIdxOf[s1]);
            }
         }
      }

      vector<vector<int>> ret;
      for(auto& pr : rst){
         for(auto idx: pr.second){
            ret.push_back({pr.first, idx});
         }
      }
      return ret;
   }
};