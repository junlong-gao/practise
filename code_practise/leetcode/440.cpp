class Solution {
  using ll = long long;
public:
		
  int findKthNumber(int n, int k) {
     return helper(0, n, k);
  }
  
	// find the kth of this subtree rooted by traversaling path
	// of sofar, EXCLUDING the subtree root. k == 0 implies take the subtree root,
  // which implies there is nothing to be done as the caller already appended
  // the root in sofar, see below recursive call.
	ll helper(ll sofar, int n, int k) {
	  if (k == 0) {
	    return sofar;
	  }
	  ll skipCount = 0;
	  for (int digit = ((sofar == 0)? 1 : 0); digit <= 9; ++digit) {
	    int acc = skipCount + count(sofar * 10 + digit, n);
	    if (acc >= k) {
	      // pick this subtree(digit) and remove all previous skipped subtrees
	      // as well as the root of this subtree(digit), as the root(digit) is 
	      // already accounted into sofar <- sofar * 10 + digit
	      return helper(sofar * 10 + digit, n, k - skipCount - 1);
	    }
	    skipCount = acc;
	  }
	  assert(0);
	}
  
  // count the total number of the nodes in the subtree rooted by
  // traversaling a path of prefix, including the subtree root.
  // count level by level, at a level 0, there is only one node, with value
  // prefix, the next level has 10: lo = prefix*10 ~ hi = prefix*10 - 1, then the next
  // level... until we hit n < lo or n < hi && lo <=n, in the first case we know
  // there is no more level, in the second case there is no more next level, 
  // and this level's contribution is not the entire hi - lo + 1, rather is
  // n - lo + 1, as discussed the tree will be complete only except the last level,
  // which is truncated at a certain point from lo to hi.
  int count(ll prefix, ll n) {
    ll count = 0;
    ll level = 1;
    while(true) {
      ll lo = prefix * level;
      ll hi = lo + level - 1;
      if (n < lo) {
        break;
      }
      if (n < hi && lo <= n) {
        count += n - lo + 1;
      }
      if (n >= hi) {
        count += hi - lo + 1;
      }
      level *= 10;
    }
    return count;
  }

};


int main() {
	Solution s;
	int test = 13;
	
	for (int i = 1; i <= test; ++i) {
      cout << s.findKthNumber(test, i) << endl;
	}
	
	cout << "@@" << endl;
	test = 9;
	for (int i = 1; i <= test; ++i) {
      cout << s.findKthNumber(test, i) << endl;
	}
	
	cout << "@@" << endl;
	test = 999;
	for (int i = 1; i <= test; ++i) {
      cout << s.findKthNumber(test, i) << endl;
	}
	
	cout << "@@" << endl;
	test = 9999;
	for (int i = 1; i <= test; ++i) {
      cout << s.findKthNumber(test, i) << endl;
	}
	cout << "@@" << endl;
	


	test = 4897764;
	for (int i = 3510562; i <= 3510564; ++i) {
      cout << s.findKthNumber(test, i)  << endl;
	}
	// 4159503	
}
