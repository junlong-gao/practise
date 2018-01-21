class Solution {
    using ll = long long;
    ll soFar;
    ll delta;
    ll numN;
    
    void genPalin(const string &n, string &prefix) {
      if (2 * prefix.length() >= n.length()) {
        string tmp1 = prefix, tmp2 = prefix;
        if (2 * prefix.length() > n.length()) {
          tmp1.pop_back();
        } 
        reverse(tmp2.begin(), tmp2.end());
        ll in = stoll((tmp1 + tmp2).c_str());
        
        ll newDelta = abs(in - numN);
        if ( newDelta > 0 && (newDelta < delta || (newDelta == delta && in < soFar))) {
              soFar = in;
              delta = newDelta;
            }
        return;
      }
      
      int next = prefix.length();
      int val = int(n[next] - '0');
      if (val < 9) {
        prefix += char(val + 1 + '0');
        genPalin(n, prefix);
        prefix.pop_back();
      }
      
      prefix += char(val + '0');
      genPalin(n, prefix);
      prefix.pop_back();
      
      if (val > 0) {
        prefix += char(val - 1 + '0');
        genPalin(n, prefix);
        prefix.pop_back();
      }
    }
public:
    string nearestPalindromic(string n) {
      numN = stoll(n.c_str());
      delta = numeric_limits<ll>::max();
      if (n.length() == 1) { // : )
        for (int i = 0; i < 9; ++i) {
          if (abs(i - numN) < delta && abs(i - numN) > 0) {
            delta = abs(i - numN);
            soFar = i;
          }
        }
        return to_string(soFar);
      }
      
      ll nine = stoll(string(n.length() - 1, '9').c_str());
      delta = abs(numN - nine);
      soFar = nine;

      ll one = stoll(("1" + string(n.length() - 1, '0') + "1").c_str());
      if (delta > abs(numN - one) && abs(numN -one) > 0) {
        soFar = one;
        delta = abs(numN - one);
      }
      
      
      string tmp ;
      if (n.length() > 2) {
        tmp = n.substr(0, 1);
      }
      genPalin(n, tmp);
      return to_string(soFar);
    }
};
