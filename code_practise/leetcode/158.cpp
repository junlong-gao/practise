// Forward declaration of the read4 API.
int read4(char *buf);
/*
   read(buf, n)
   |<----->|<------->|<---->|
       A        B        C
   A: bounce buffer (size <= 4), copy from bounce buffer
   B: aligned read
   C: unaligned read (size <= 4), copy into bounce buffer
*/
class Solution {
    char bounce[4];
    int head=0, tail=0;
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int ret = 0;
        while (n && tail > head) {
            *buf = bounce[head % 4];
            buf++; ret++; n--; head++;
        }
        
        int size = 0;
        while ((n >= 4) && (size = read4(buf))) {
            n -= size; buf += size; ret += size;
        }
        
        if (n) {
            assert(tail == head);
            tail += read4(bounce);
            while (n && tail > head) {
               *buf = bounce[head % 4];
                buf++; ret++; n--; head++;
            }
        }
        
        return ret;
    }
};
