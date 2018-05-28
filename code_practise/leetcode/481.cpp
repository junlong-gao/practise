/*
linear time sim:

1 2 2
      +
1 2 2 1 1
         +
1 2 2 1 1 2
	+
1 2 2 1 1 2 1
               +
1 2 2 1 1 2 1 2 2
	       +
1 2 2 1 1 2 1 2 2 1
                     +
*/
class Solution {
public:
    int magicalString(int n) {
        	vector<int> seq {1, 2, 2};
	int next = 2;
        	static vector<int> ret { 1, 1, 1};
	if (n == 0) return 0;
	if (n <= 3) return ret[n-1];
	int count = 1;
	while (true) {
		int toPush = 1 + seq.back() % 2;
		if (seq[next] == 1) {
			seq.push_back(toPush);
			if (seq.back() == 1) count++;
			if (seq.size() == n) break;
		} else {
			seq.push_back(toPush);
			if (seq.back() == 1) count++;
			if (seq.size() == n) break;
			seq.push_back(toPush);
			if (seq.back() == 1) count++;
			if (seq.size() == n) break;
		}
		next++;
	}
	return count;
    }
};
/*
1 2 2 1 1 2 1 2 2 1
                  +
*/



