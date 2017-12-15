Suppose we abstract our file system by a string in the following manners:

The string 
```
"dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" 
```
represents:
```
dir
    subdir1
    subdir2
        file.ext
```
a directory dir contains an empty sub-directories subdir1 and a sub-directory subdir2 containing a file file.ext.

The string
 ```
 "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
  ```
  represents:

```
dir
    subdir1
        file1.ext
        subsubdir1
    subdir2
        subsubdir2
            file2.ext
```
a directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.extand an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

We are interested in finding the longest(number of characters) absolute path to a file within our file system. That is, for example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its length is 30.

Given a string representing the file system in the above format, return the length of the longest absolute path to file in the abstracted file system. Simply put, that is the length of a valid path that ends with a file, and a file contains . and an extension.

Time complexity required: O(n) where n is the size of the input string.

Notice that a/aa/aaa/file1.txt is not the path you want, if there is aaaaaaaaaaaaaaaaaaaaa/sth.png.