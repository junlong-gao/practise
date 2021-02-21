/*
11112
999998

21111
899999
0111111
*/
class Solution {
public:
    string addStrings(string num1, string num2) {
        	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	string ret;
	int i = 0; int j = 0; int carry = 0; int d = 10;
	auto add = [&](char l, char r) {
int next = carry + l - '0' + r - '0';
		ret.push_back(next % d + '0');
		carry = next / d;
	};

	while (i < num1.size() && j < num2.size()) {
		add(num1[i], num2[j]);
		i++; j++;
	}

	while (i < num1.size()) {
		add(num1[i], '0');
		i++;
	}

	while (j < num2.size()) {
		add('0', num2[j]);
		j++;
	}

	if (carry != 0) { // XXX
		add('0', '0');
	}

	reverse(ret.begin(), ret.end());
	return ret;
    }
};

/*
compile error:
lambda def followed by comma

wa:
if the final carry is not 0, add that carry back to the leading digit.
*/
