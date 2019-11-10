class Solution {

public:
    bool canConvert(string str1, string str2) {
      vector<char> t(256, 0);
      unordered_map<char, char> rev;
      bool submerge = false;
      for (int i = 0; i < str1.size(); ++i) {
        if (t[str1[i]] != 0 && t[str1[i]] != str2[i]) {
          return false;
        }
        t[str1[i]] = str2[i];
        if (rev.count(str2[i]) && rev[str2[i]] != str1[i]) {
          submerge = true;
        }
        rev[str2[i]] = str1[i];
      }
      
      if (submerge) {
        return true;
      } 
      
      bool hasTemp = false;
      for (char i = 'a'; i <= 'z'; ++i) {
        if (t[i] == 0) {
          hasTemp = true;
        }
      }
      
      if (hasTemp) {
        return true;
      }
      
      for (char i = 'a'; i <= 'z'; ++i) {
        char cur = t[i];
        unordered_set<char> seen;
        while (cur != 0) {
          if (seen.count(cur)) return false;
          seen.insert(cur);
          if (cur == t[cur]) {
            break; // fix point.
          }
          cur = t[cur];
        }
      }
      
      return true;
    }
};
