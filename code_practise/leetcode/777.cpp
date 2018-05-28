/*
if 1. removing all X will result the same
2. "XL" -> "LX" all L must be not left to the corresponding left
3. "RX" -> "XR" all R must be not right to the corresponding right.
*/
class Solution {
public:
    bool canTransform(string start, string end) {
            if (start.size() != end.size()) return false;
	int i = 0; int j = 0;
	while (true) {
		while (i < start.size() && start[i] == 'X') { i++; }
		while (j < end.size() && end[j] == 'X')   { j++; }
		if (i != start.size() && j != end.size()) {
			if (start[i] != end[j]) 	    { return false; }
			if (start[i] == 'L' && i < j)  { return false; }
			if (start[i] == 'R' && i > j)  { return false; }
			i++; j++;
			continue;
		}

		if (i == start.size() && j == end.size()) { break; }

		return false;
	}
	return true;
    }
};

/*
XL
LX

RX
XR

LX
XL

"RXXLRXRXL"
"XRLXXRRLX"

"XRR"
"XXR"

*/
