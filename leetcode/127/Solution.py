import collections
import string
class Solution(object):
    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: Set[str]
        :rtype: int
        """
        d = {}
        alpha = list(string.ascii_lowercase)
        Q = collections.deque()
        d[beginWord] = 1
        Q.append(beginWord)
        if beginWord in wordList:
            wordList.remove(beginWord)
        while Q:
            top = Q.popleft()
            for i in range(0, len(top)):
                for c in alpha:
                    next = top[0:i] + c + top[i+1:len(top)]
                    if next == endWord:
                        return d[top] + 1
                    if next in wordList:
                        wordList.remove(next)
                        Q.append(next)
                        d[next] = d[top] + 1
        return 0


if __name__ == "__main__":
    wordList = {"hot","dog"}
    beginWord = "hot"
    endWord = "dog"
    s = Solution()
    rst = s.ladderLength(beginWord,endWord,wordList)
    print rst
