
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
    deque<char> internalBuf;
    char next(bool &success) {
        if (internalBuf.empty()) {
            char t[4];
            int c = read4(t);
            for (int i = 0; i < c; ++i) {
                internalBuf.push_back(t[i]);
            }
        }
        
        if (internalBuf.empty()) {
            success = false;
            return 0;
        }
        
        success = true;
        char ret = internalBuf.front();
        internalBuf.pop_front();
        return ret;
    }
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int soFar = 0;
        while (soFar < n) {
            bool succ = false;
            char ret = next(succ);
            if (succ) {
                buf[soFar] = ret;
                soFar ++;
            } else {
                return soFar;
            }
        }
        return soFar;
    }
};
