/*
counting
*/

class Solution {
public:
    int findNthDigit(int n) {
        n--;
	int i = 1; long long d = 9;
	while (n >= i * d) {
		n -= i * d;
		i ++; d = d * 10;
	}
	int s = d / 9 + n / i;
	return to_string(s)[n%i] - '0';
    }
};

/*
1 2 3 4 5
n = 3:
s = 1 + 2 / 1 = 3;
return 3

1 2 3 4 5 6 7 8 9 10 11
n = 11:
n = 10
i = 2; d = 90; n = 10 - 9 = 1;
s = 90 / 9 + 1 / 2 = 10
return "10"[1] = 0
*/
