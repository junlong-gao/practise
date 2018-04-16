/*
> lcg 588
  ✔ Accepted
  ✔ 63/63 cases passed (16 ms)
  ✔ Your runtime beats 26.83 % of cpp submissions
*/

/*
 * [588] Design In-Memory File System
 *
 * https://leetcode.com/problems/design-in-memory-file-system/description/
 *
 * algorithms
 * Hard (36.03%)
 * Total Accepted:    2.6K
 * Total Submissions: 7.2K
 * Testcase Example:  '["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]\n[[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]'
 *
 * Design an in-memory file system to simulate the following functions:
 *
 * ls: Given a path in string format. If it is a file path, return a list that
 * only contains this file's name. If it is a directory path, return the list
 * of file and directory names in this directory. Your output (file and
 * directory names together) should in lexicographic order.
 *
 * mkdir: Given a directory path that does not exist, you should make a new
 * directory according to the path. If the middle directories in the path don't
 * exist either, you should create them as well. This function has void return
 * type.
 *
 * addContentToFile: Given a file path and file content in string format. If
 * the file doesn't exist, you need to create that file containing given
 * content. If the file already exists, you need to append given content to
 * original content. This function has void return type.
 *
 * readContentFromFile: Given a file path, return its content in string
 * format.
 *
 * Example:
 *
 * Input:
 * ["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
 * [[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]
 * Output:
 * [null,[],null,null,["a"],"hello"]
 * Explanation:
 *
 *
 *
 *
 * Note:
 *
 * You can assume all file or directory paths are absolute paths which begin
 * with / and do not end with / except that the path is just "/".
 * You can assume that all operations will be passed valid parameters and users
 * will not attempt to retrieve file content or list a directory or file that
 * does not exist.
 * You can assume that all directory names and file names only contain
 * lower-case letters, and same names won't exist in the same directory.
 *
 *
 */
class FileSystem {
   struct inode {
      bool isFile;
      unordered_map<string, int> dirents;
      string content;
   };

   unordered_map<int, inode> inodes;
   int gid = 0;
public:
    FileSystem() {
       inodes[0].isFile = false;
       inodes[0].dirents[""] = 0;
    }

    template<typename F>
    void treeWalk(int cur, const string &relative, F &&f) {
       assert(!relative.empty());
       assert(relative.front() == '/');

       int i = 1;
       while (i < relative.size()) {
          if (relative[i] == '/') break;
          i++;
       }

       string pathname = relative.substr(1, i - 1);
       if (i == relative.size()) {
          f(cur, pathname);
       } else {
          inode & curInode = inodes[cur];
          assert(!curInode.isFile);

          // create the new dir
          if (curInode.dirents.count(pathname) == 0) {
             gid++;
             inodes[gid].isFile = false;
             curInode.dirents[pathname] = gid;
          }

          treeWalk(curInode.dirents[pathname],relative.substr(i), f);
       }
    };

    vector<string> ls(string path) {
       vector<string> ret;
       treeWalk(0, path, [&](int id, string pathname){
          //cout << pathname << " " << id << endl;
          int cid = inodes[id].dirents[pathname];
          if (inodes[cid].isFile) {
            ret.push_back(pathname);
          } else {
            for (const auto & name : inodes[cid].dirents) {
               if (name.first.empty()) continue;
               ret.push_back(name.first);
            }
          }
       });

       sort(ret.begin(), ret.end());
       return ret;
    }

    void mkdir(string path) {
       assert(path != "/");
       treeWalk(0, path + "/", [&](int id, string pathname){
          return;
       });
    }

    void addContentToFile(string filePath, string content) {
       treeWalk(0, filePath, [&](int id, string pathname){
          assert(!inodes[id].isFile);
          if (inodes[id].dirents.count(pathname) == 0) {
             gid++;
             inodes[gid].isFile = true;
             inodes[id].dirents[pathname] = gid;
          }

          inodes[inodes[id].dirents[pathname]].content += content;
       });
    }

    string readContentFromFile(string filePath) {
       string ret;
       treeWalk(0, filePath, [&](int id, string pathname){
          assert(!inodes[id].isFile);
          assert(inodes[id].dirents.count(pathname) == 1);
          ret = inodes[inodes[id].dirents[pathname]].content;
       });
       return ret;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem obj = new FileSystem();
 * vector<string> param_1 = obj.ls(path);
 * obj.mkdir(path);
 * obj.addContentToFile(filePath,content);
 * string param_4 = obj.readContentFromFile(filePath);
 */

/*
*/

/*
TESTS
["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
[[],["/"],["/a/b/c/d/f/g"],["/a/b/e","hello"],["/"],["/a/b/e"]]
["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile", "ls", "ls", "ls", "ls"]
[[],["/"],["/a/b/c/d/f/g"],["/a/b/e","hello"],["/"],["/a/b/e"], ["/a/b/c/d"], ["/a/b/c/d/f"], ["/a/b/c"], ["/a/b"]]
["FileSystem","mkdir","ls","ls","mkdir","ls","ls","addContentToFile","ls","ls","ls"]
[[],["/goowmfn"],["/goowmfn"],["/"],["/z"],["/"],["/"],["/goowmfn/c","shetopcy"],["/z"],["/goowmfn/c"],["/goowmfn"]]
["FileSystem","mkdir","ls","ls","mkdir","ls","ls","addContentToFile","ls","ls"]
[[],["/goowmfn"],["/goowmfn"],["/"],["/z"],["/"],["/"],["/goowmfn/c","shetopcy"],["/z"],["/goowmfn/c"]]
*/
