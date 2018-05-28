/*
union find
*/

struct UF {
  int n_;
  vector<int> p_;
  vector<int> d_;

  UF(int n) : n_(n), d_(vector<int>(n, 1)) {
    for (int i = 0; i < n; ++i) {
      p_.emplace_back(i);
    }
  }

  int find(int x) {
    int y = p_[x];
    if (y == x) return x;
    return p_[x] = find(y);
  }

  void link(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (d_[px] > d_[py]) {
      p_[py] = px;
    } else {
      p_[px] = py;
      if (d_[px] == d_[py]) {
        d_[py]++;
      }
    }
  }
};

class Solution {
 public:
  bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2,
                              vector<pair<string, string>> pairs) {
    if (words1.size() != words2.size()) return false;
    unordered_map<string, int> stringToIdx;
    int id = 0;
    for (const auto& pr : pairs) {
      if (stringToIdx.count(pr.first) == 0) {
        stringToIdx[pr.first] = id++;
      }

      if (stringToIdx.count(pr.second) == 0) {
        stringToIdx[pr.second] = id++;
      }
    }
    UF uf(id);

    for (const auto& pr : pairs) {
      uf.link(stringToIdx[pr.first], stringToIdx[pr.second]);
    }

    for (int i = 0; i < words1.size(); ++i) {
      // check words1[i] and words2[i] are similar:
      if (words1[i] == words2[i]) continue;
      // if they are not equal, they must be in the same class.
      if (stringToIdx.count(words1[i]) == 0) return false;
      if (stringToIdx.count(words2[i]) == 0) return false;
      if (uf.find(stringToIdx[words1[i]]) != uf.find(stringToIdx[words2[i]])) {
        return false;
      }
    }

    return true;
  }
};

/*
The size is wrong
not considering words not in set
not considering words equal and not in set

mitigation:
use pesudo code first, to explain idea and use as a guide line
don’t jump to impl too fast, communicate and write down high level attack plan.
*/
