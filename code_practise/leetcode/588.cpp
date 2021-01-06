class FileSystem {
    struct inode {
       bool isDir;
       map<string, int> dirent;
       string content; 
    };
    unordered_map<int, inode> fs {
        {2, {true, {}, {}}},
    };
    int root = 2;
    int nextObjId = 3;
    vector<string> split(string s) {
        int i = 1;
        vector<string> ret{""};
        while (i < s.size()) {
            int j = i;
            while (j < s.size() && s[j] != '/') {j++;}
            ret.push_back(s.substr(i, j - i));
            i = j + 1;
        }
        return ret;
    }
    int walk(string &path) {
        auto comp = split(path);
        int cur = root;
        int i = 1;
        while (i < comp.size()) {
            inode &s = fs[cur];
            if (!s.isDir) return 0;
            if (s.dirent.count(comp[i]) == 0) {
                return 0;
            }
            cur = s.dirent[comp[i]];
            i++;
        }
        return cur;
    }
    int mkfile(string path) {
        auto comp = split(path);
        int cur = root;
        int i = 1;
        while (i < comp.size()) {
            inode &s = fs[cur];
            if (!s.isDir) return 0;
            if (s.dirent.count(comp[i]) == 0) {
                inode t;
                s.dirent[comp[i]] = nextObjId;
                if (i == comp.size() - 1) {
                    t.isDir = false;
                } else {
                    t.isDir = true;
                }
                fs[s.dirent[comp[i]]] = t;
                nextObjId++;
            }
            cur = s.dirent[comp[i]];
            i++;
        }
        return cur;
    }
public:
    FileSystem() {
        
    }
    
    vector<string> ls(string path) {
        int i = walk(path);
        assert(i);
        if (fs[i].isDir) {
            vector<string> ret;
            for (auto &e:fs[i].dirent) {
                ret.push_back(e.first);
            }
            return ret;        
        } else {
            return {split(path).back()};
        }        
    }
    
    void mkdir(string path) {
        vector<string> comp = split(path);
        int cur = root;
        int i = 1;
        while (i < comp.size()) {
            inode &s = fs[cur];
            if (!s.isDir) return;
            if (s.dirent.count(comp[i]) == 0) {
                inode t;
                s.dirent[comp[i]] = nextObjId;
                t.isDir = true;
                fs[s.dirent[comp[i]]] = t;
                nextObjId++;
            }
            cur = s.dirent[comp[i]];
            i++;
        }
    }
    
    void addContentToFile(string filePath, string content) {
        int i = mkfile(filePath);
        fs[i].content += content;
    }
    
    string readContentFromFile(string filePath) {
        int i = walk(filePath);
        assert(i);
        assert(!fs[i].isDir);
        return fs[i].content;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */
