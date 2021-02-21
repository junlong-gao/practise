class StringIterator {
    using ull = unsigned long long;
    int cursor;
    vector<pair<char, ull>> parsed;
public:
    StringIterator(string compressedString) {
        cursor = 0;
        int i = 0;
        while (i < compressedString.size()) {
            pair<char, ull> t;
            t.first = compressedString[i];
            i++;
            int pos = i;
            while (i < compressedString.size() && isdigit(compressedString[i])) {
                i++;
            }
            
            t.second = stoull(compressedString.substr(pos, i - pos));
            if (t.second != 0) {
                parsed.push_back(t);
            }
        }
    }
    
    char next() {
        if (!hasNext()) return ' ';
        char ret = parsed[cursor].first;
        parsed[cursor].second--;
        if (parsed[cursor].second == 0) cursor++;
        return ret;
    }
    
    bool hasNext() {
        return cursor < parsed.size();
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator obj = new StringIterator(compressedString);
 * char param_1 = obj.next();
 * bool param_2 = obj.hasNext();
 */
