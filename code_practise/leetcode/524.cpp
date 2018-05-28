/*
given string s and t, check t is a substring of s (by removing some char in s)
O(n)


fun isSub(s, t) -> true iff t is a substring of s O(n)

fun Solu(dict, s)
   filter dict into a vector of strings
   sort by cmp (l, r) -> if l.length != r.length return l.length > r.length
		           else return l < r
   for each l in strings
	if isSub(s, l) return return l;

   return "";
*/

class Solution {
    bool isSub(const string& s, const string& t)
    {
        if (t.length() > s.length())
            return false;
        int j = 0;
        for (int i = 0; i < t.length(); ++i) {
            while (j < s.length() && t[i] != s[j])
                j++;
            if (j == s.length())
                return false;
            j++;
        }
        return true;
    }

public:
    string findLongestWord(string s, vector<string>& d)
    {
        vector<string> bag;
        for (auto& ss : d) {
            if (ss.length() <= s.length()) {
                bag.emplace_back(std::move(ss));
            }
        }

        sort(bag.begin(), bag.end(), [](const string& l, const string& r) {
            if (l.length() != r.length())
                return l.length() > r.length();
            return l < r;
        });

        for (const auto& ss : bag) {
            if (isSub(s, ss))
                return ss;
        }

        return "";
    }
};

/*
s = "abpcplea", d = ["ale","apple","monkey","plea"]
abpcplea
apple
aplep

d = ["monkey", "apple", "plea", "ale"]

WA:
isSub: s = "abcde" t = "abcce" should increase cursor in s.
How to mitigate such error in coding?
*/
