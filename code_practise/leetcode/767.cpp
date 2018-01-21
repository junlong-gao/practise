// Take 1: naive
class Solution {
public:
    string reorganizeString(string S) {
      string t = "";
      for (int i = 0; i < S.size(); ++i) {

        for (int j = 0; j + 1 < t.size(); ++j) {
          if (t[j] == t[j+1] && S[i] != t[j]) {
            t.insert(j + 1, S.substr(i, 1));
            break;
          } 
        }
        if (t.size() == i + 1)  continue;
        
        for (int j = 0; j + 1 < t.size(); ++j) {
          if (S[i] != t[j+1] && S[i] != t[j]) {
            t.insert(j + 1, S.substr(i, 1));
            break;
          } 
        }
        if (t.size() == i + 1)  continue;
        
      
          if (S[i] != t[0]) {
            t.insert(0, S.substr(i, 1));
          } else if (S[i] != t.back()) {
            t.push_back(S[i]);
          } else {
            t.push_back(S[i]);
          }
        
      }
      for (int i = 1; i < S.size(); ++i) {
        if (t[i] == t[i-1]) return "";
      }
      return t;
    }
};

// Take 2: greedy
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
// repetition happens when the last element has count >= 2 or repeat against the last of the current
// constructed ret string.

  string reorganizeString(string S) {
    unordered_map<char, int> counts;
    for (auto c : S) {
      counts[c] ++;
    }
    auto comp = [](pair<char, int> &l, pair<char, int> &r) {
      if (l.second != r.second) {
        return l.second < r.second;
      }
      return l.first < r.first;
    };
    priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(comp)> q(counts.begin(), counts.end(), comp);
    string ret;
    while(q.size() >= 2){
      auto f = q.top(); q.pop();
      auto s = q.top(); q.pop();
      ret.push_back(f.first); f.second--;
      ret.push_back(s.first); s.second--;
      if (f.second > 0) q.push(f);
      if (s.second > 0) q.push(s);
    }
    if (!q.empty()) {
      auto t = q.top(); q.pop();
      if (t.second >= 2 || (!ret.empty() && ret.back() == t.first))  return "";
      ret.push_back(t.first);
    }
    return ret;
  }
  
int main() {
  
  {
  Solution s;
  cout << s.reorganizeString("cxmwmmm") << endl;; // mxmwmcm
}
{
  Solution s;
  cout << s.reorganizeString("baaba") << endl;; // ababa
}
{
  Solution s;
  cout << s.reorganizeString("aaa") << endl;; //
}
{
  Solution s;
  cout << s.reorganizeString("aab") << endl;; // aba
}
{
  Solution s;
  cout << s.reorganizeString("aabc") << endl;; // abac
}
{
  Solution s;
  cout << s.reorganizeString("aaac") << endl;; //
}
{
  Solution s;
  cout << s.reorganizeString("aaba") << endl;; //
}
{
  Solution s;
  cout << s.reorganizeString("aabac") << endl;; //abaca
}
{
  Solution s;
  cout << s.reorganizeString("aaabc") << endl;; //
}
}
