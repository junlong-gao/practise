/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

class Solution {
    deque<char> buf;
    void refill() {
        assert(buf.empty());
        char in[4];
        int n = read4(in);
        for (int j = 0; j < n; ++j) {
            buf.push_back(in[j]);
        }
    }
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buffer, int n) {
        int re = 0;
        while (n) {
            if (buf.empty()) refill();
            if (buf.empty()) return re;
            *buffer = buf.front();
            buf.pop_front();
            re++;n--;buffer++;
        }
        return re;
    }
};
