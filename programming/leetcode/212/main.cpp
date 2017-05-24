#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#ifndef DEBUG
#define DEBUG 0
#endif
#define FILENAME "test.txt"

using namespace std;
using grid = vector<vector<char>>;
class Solution {
public:
    class Trie{
    public:
        Trie* next[26];
        bool word;
        Trie(){
            fill(next, next+26, nullptr);
            word = false;
        }
        void addWord(const string& word){
            Trie* u = this;
            for(int i = 0; i < (int)word.length(); ++i){
                if(u->next[word[i] - 'a'] == nullptr)
                    u->next[word[i] - 'a']= new Trie();
                u = u->next[word[i] - 'a'];
            }
            u->word = true;
        }
        ~Trie(){
            for(auto ele: next){
                delete ele;
            }
        }
    };
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};
    vector<string> rst;
    string so_far; int cnt, n, m;

    bool checkValid(int x, int y){
        if(x <0 || x >= n) return false;
        if(y<0 || y >= m) return false;
        return true;
    }

    void dfs(Trie* walker, grid& board, int x, int y){
        if(walker->word){
            walker->word = false;
            rst.push_back(so_far);
            cnt--;
        }
        for(int i = 0; i < 4; ++i){
            int nx = x +dx[i]; int ny = y + dy[i];
            //extend nodes:
            if(!checkValid(nx,ny) || board[nx][ny]=='X') continue;
            Trie* next = walker->next[board[nx][ny] - 'a'];
            if(next){
                char t = 'X';
                so_far.push_back(board[nx][ny]); swap(t, board[nx][ny]);
                dfs(next, board, nx, ny);
                so_far.pop_back(); swap(t, board[nx][ny]);
            }
        }
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        n = board.size(); m = board[0].size(); cnt = 0;
        auto root = new Trie;
        for(auto& ele : words){ cnt ++; root->addWord(ele); }

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(cnt == 0) break;
                auto next = root->next[board[i][j] - 'a'];
                if(next){
                    char t = 'X';
                    so_far.push_back(board[i][j]); swap(t, board[i][j]);
                    dfs(next, board, i, j); 
                    so_far.pop_back(); swap(t, board[i][j]);
                }
            }
            if(cnt== 0) break;
        }
        return rst;
    }
};

int main(){
    std::ifstream in(FILENAME);
    if(DEBUG){
        std::cin.rdbuf(in.rdbuf());
    }
    Solution s;
    grid test1= {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };
    vector<string> words1 = {"oath", "pea", "eat", "rain"};
    vector<string> test_temp =  { "bbaaba","bbabaa","bbbbbb","aaabaa","abaabb" };
    
    vector<string> words2 = {"abbbababaa"};
    grid test2(6, vector<char>(6));
    for(int i = 0; i < (int)test_temp.size(); ++i){
        for(int j = 0; j < (int)test_temp[i].length(); ++j ){
            test2[i][j] = test_temp[i][j];
        }
    }
    grid test3 = {{'a','a'}};
    vector<string> words3 = {"aaa"};

    test_temp = {"ab","cd"};
    grid test4(2, vector<char>(2));
    for(int i = 0; i < (int)test_temp.size(); ++i){
        for(int j = 0; j < (int)test_temp[i].length(); ++j ){
            test4[i][j] = test_temp[i][j];
        }
    }
    vector<string> words4 = {"ab","cb","ad","bd","ac","ca","da","bc","db","adcb","dabc","abb","acb"};

    
    
    vector<string> rst(s.findWords(test2, words2));
    
    for(auto& ele : rst){

        cout << ele << " " ;
    }
    return 0;
    
}
