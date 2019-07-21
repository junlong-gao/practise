// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
    class Iter {
        deque<char> buffer;
        void fill() {
            assert(buffer.empty());
            vector<char> buf(4, 0);
            int count = read4(buf.data());
            for (int i = 0; i < count; ++i) {
               buffer.push_back(buf[i]);
            }
        }
      public:
        Iter() { fill(); }
        
        bool Empty() { return buffer.empty(); }
        char Val() { return buffer.front(); }
        void Next() {
            buffer.pop_front();
            
            if (buffer.empty()) {
                fill();
            }
        }
    } iter;
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int ret = 0;
        while(n && !iter.Empty()) {
           *buf = iter.Val();
            iter.Next();
            ret++; n--; buf++;
        }
        return ret;
    }
};
