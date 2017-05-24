#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

class Solution {
public:
    class Graph{
    public:
        bool G[26][26];
        int unvisited[26];
        bool inG[26];
        string solutions;
        Graph(){
            for (auto i = 0; i<26; i++) {
                inG[i]=false;
                unvisited[i]=0;
                solutions="";
                for (auto j = 0 ; j < 26; j++) {
                    G[i][j]= false;
                }
            }
        }
    };
    
    string alienOrder(vector<string>& words) {
        for(auto i = 0; i< (int)words.size(); i++){
            if (words[i].length()==0) {
                words.erase(words.begin()+i);
            }
        }
        
        if (words.size()==0) {
            return "";
        }
        if (words.size()==1) {
            // a safe guard
            words.push_back(words.back());
        }
        unsigned long length=0;
        for(auto i = 0; i< (int)words.size(); i++){
           // reverse(words[i].begin(), words[i].end());
            if (words[i].length()>length) {
                length = words[i].length();
            }
        }
        
        if (length==0) {
            return "";
        }
        
        Graph graph;
        bool noedge=true;
        for(auto i = 0; i < (int)words.size()-1;i++){
            for(auto j = 0; j < length; j++){
                if (j<words[i].length()&&j<words[i+1].length()) {
                    if (j==0||words[i][j-1]==words[i+1][j-1]) {
                        if (words[i][j]!=words[i+1][j]) {
                            noedge=false;
                            graph.G[words[i][j]-'a'][words[i+1][j]-'a']=true;
                        }
                    }
                }
                if (j<words[i].length()){
                    graph.inG[words[i][j]-'a']=true;
                }
                if (j<words[i+1].length()) {
                    graph.inG[words[i+1][j]-'a']=true;
                }
            }
        }
        
        string rst="";
        if (noedge) {
            for (auto i = 0; i<26; i++) {
                if (graph.inG[i]) {
                    string t(1,'a'+i);
                    rst = rst + t;
                }
            }
            return rst;
        }
        for (auto i = 0; i < 26; i++) {
            if (graph.inG[i]) {
                if(DFS(graph, i)==false){
                    return "";
                }
            }
        }
        reverse(graph.solutions.begin(), graph.solutions.end());
      return graph.solutions;
    }
    
    bool DFS(Graph& graph, int u){
        if (graph.unvisited[u]==-1) {
            return false;
        }
        if (graph.unvisited[u]==1) {
            return true;
        }
        
        graph.unvisited[u]=-1;
        for (auto i = 0; i<26; i++) {
            if (graph.inG[i]&&graph.G[u][i]) {
                if(DFS(graph, i)==false){
                    return false;
                }
            }
            
        }
        
        graph.unvisited[u]=1;
        string t(1,u+'a');
        graph.solutions +=t;
        
        return true;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution mysolution;
    vector<string> words;
    
    /*
    words.push_back("wrt");
    words.push_back("wrf");
    words.push_back("er");
    words.push_back("ett");
    words.push_back("rftt");
    */
    
    /*
    words.push_back("a");
    words.push_back("b");
    words.push_back("a");
     //loop
    */
    
    /*
    words.push_back("ab");
    words.push_back("adc");
    */
    
    /*
    words.push_back("ze");
    words.push_back("yf");
    words.push_back("xd");
    words.push_back("wd");
    words.push_back("vd");
    words.push_back("ua");
    words.push_back("tt");
    words.push_back("sz");
    words.push_back("rd");
    words.push_back("qd");
    words.push_back("pz");
    words.push_back("op");
    words.push_back("nw");
    words.push_back("mt");
    words.push_back("ln");
    words.push_back("ko");
    words.push_back("jm");
    words.push_back("il");
    words.push_back("ho");
    words.push_back("gk");
    words.push_back("fa");
    words.push_back("ed");
    words.push_back("dg");
    words.push_back("ct");
    words.push_back("bb");
    words.push_back("ba");
    */
    
    /*
    words.push_back("bsusz");
    words.push_back("rhn");
    words.push_back("gfbrwec");
    words.push_back("kuw");
    words.push_back("qvpxbexnhx");
    words.push_back("gnp");
    words.push_back("laxutz");
    words.push_back("qzxccww");
    //loop
    */
    
    /*
    words.push_back("ndwkkqrba");
    words.push_back("qmewabzvqa");
    words.push_back("boau");
    words.push_back("ixxzpijax");
    words.push_back("sdsszrbi");
    words.push_back("hvqdad");
    words.push_back("opbippqgz");
    words.push_back("ft");
    words.push_back("w");
    */
    
    
    words.push_back("dvpzu");
    words.push_back("bq");
    words.push_back("lwp");
    words.push_back("akiljwjdu");
    words.push_back("vnkauhh");
    words.push_back("ogjgdsfk");
    words.push_back("tnkmxnj");
    words.push_back("uvwa");
    words.push_back("zfe");
    words.push_back("dvgghw");
    words.push_back("yeyruhev");
    words.push_back("xymbbvo");
    words.push_back("m");
    words.push_back("n");
     //loop
    
    
    
    cout<<mysolution.alienOrder(words);
    
    return 0;
}
