//
// Created by Junlong Gao on 11/15/16.
//

#include "catch.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <queue>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <assert.h>

using namespace std;

class ArrayTree{
public:
    void removeSubTree(vector<int>& tree, int toDelete){
        unordered_map<int, vector<int>> graph;
	for(int i = 0; i < tree.size(); ++i){
		if(tree[i] != -1 && tree[i]!=i) graph[tree[i]].push_back(i);
	}
	deque<int> q;
	q.push_back(toDelete);
	tree[toDelete] = -1;
	while(!q.empty()){
		int top = q.front(); q.pop_front();
		const vector<int>& children = graph[top];
		for(int i = 0; i < children.size(); ++i){
			q.push_back(children[i]);
			tree[children[i]] = -1;
		}
	}
    }
};

/*
TEST_CASE("ArrayTree"){
	ArrayTree obj;
	vector<int> tree = {4,4,1,0,4};
	vector<int> expected = {-1, 4, 1, -1, 4};
	obj.removeSubTree(tree, 0);
	for(int i = 0; i < expected.size(); ++i){
		REQUIRE(tree[i] == expected[i]);
	}
	expected = {-1, -1, -1, -1, -1};
	obj.removeSubTree(tree, 4);
	for(int i = 0; i < expected.size(); ++i){
		REQUIRE(tree[i] == expected[i]);
	}
}
*/

class Stream{
	vector<double> data;
public:
	Stream(const vector<double> &data_):data(data_){;}
	double getNext(){
		double ret = data.back();
		data.pop_back();
		return ret;
	}
	bool hasNext(){
		return !data.empty();
	}

};

class RWBuffer{
	bool full;
	vector<double> data;
	condition_variable cv;
	mutex lock;
public:
	RWBuffer():full(false){;}
	/*
	 * atomically put a value in the back
	 * block until success
	 */
	void put(double value, bool hasNext){
		lock.lock();
		full = !hasNext;
		data.push_back(value);
		cv.notify_all();
		lock.unlock();
	}

	/*
	 * write a value at index idx in the buffer
	 * to the rst
	 * return -1 if the buffer is full but idx
	 * exceeds the size
	 * otherwise block
	 *
	 * once return, 2 cases:
	 * successfully read at idx into rst
	 * or the idx exceeds the size of the final
	 * buffer size
	 */
	int get(int idx, double& rst){
		unique_lock<mutex> lock_(lock);
		while(idx >= data.size() && !full){
			cv.wait(lock_);
		}
		if(full && idx >= data.size()){
			return -1;
		}
		rst = data[idx];
		return 0;
	}

};

class StreamProcessor{
	Stream& s1, s2;
	RWBuffer buffer;
	mutex lock;
	vector<pair<double, double>> rst;
	int s1_size;
public:
	StreamProcessor(Stream& s1_, Stream& s2_):
		s1(s1_), s2(s2_){
		;
	}

	void start(){
		vector<thread> ths;
		ths.emplace_back([&](){read_s1();});
		ths.emplace_back([&](){read_s2();});
		for(auto& th:ths){
			th.join();
		}
	}

	void read_s1(){
		while(s1.hasNext()){
			double toPut = s1.getNext();
			buffer.put(toPut, s1.hasNext());
		}
	}

	void read_s2(){
		vector<thread> workers;
		while(s2.hasNext()){
			workers.emplace_back([&](double val){
				int curRead = 0;
				while(true){
					double ret;
					if(buffer.get(curRead++, ret) < 0) return;
					testWrite(ret, val);
				}
			}, s2.getNext());
		}
		for(auto& th: workers){
			th.join();
		}
	}

	void testWrite(double a, double b){
		lock.lock();
		if(abs(a - b) < 0.1){
			rst.emplace_back(a, b);
			cout << a << " " << b << endl;
		}
		lock.unlock();
	}
};

/*
TEST_CASE("stream"){
	Stream s1{{1,1,1,1}}, s2{{1,1,1,1}};
	StreamProcessor sp{s1, s2};
	sp.start();
	REQUIRE(1);
}*/

/*
 * The efficient data structure for
 * storing long string
 */
class Rope{
    struct Node{
        Node* left, *right, *parent;
        int weight;
        string data;
        Node():left(nullptr), right(nullptr), parent(nullptr), weight(0){;}
        ~Node(){
            delete left;
            delete right;
        }
    };
    Node* _root;
    int size;
    /*
     * return the node at index i
     */
    char index(Node* root, int i){
        assert(root);
        Node* walker = root;
        while(true){
            if(i >= walker->weight){
                i -= walker->weight;
                walker = walker->right;
                continue;
            }
            if(walker->data.empty()){
                walker = walker->left;
            }else{
                return walker->data[i];
            }
        }
    }

    /*
     * concatnate two ropes l and r
     * return the other one if any of them is nullptr
     * return nullptr if both of them are
     */
    Node* concat(Node* l, Node* r){
        if(l == nullptr) return r;
        if(r == nullptr) return l;
        int count = 0;
        Node* walker = l;
        while(walker){
            count += walker->weight;
            walker = walker->right;
        }
        Node* ret = new Node;
        ret->left = l; ret->right = r; ret->weight = count;
        l->parent = r->parent = ret;
        return ret;
    }

    /*
     * Split the node into two at index i,
     * such that one node become string 0... i - 1,
     * the other becomes i ... n-1,
     */
    void split(Node* root, int idx, Node** l, Node** r){
        if(root == nullptr){
            assert(idx == 0);
            (*l) = (*r) = nullptr;
            return;
        }
        if(root->data.size() > 0){
            //this is a leaf
            if(idx == 0){
                (*l)  = nullptr;
                (*r) = new Node;
                (*r)->data = root->data;
                (*r)->weight = root->data.size();
                (*r) -> parent = nullptr;
                root->left=root->right=nullptr;
                delete root;
                return;
            }
            if(idx == root->data.size()){
                (*l) = new Node;
                (*l)->data = root->data;
                (*l)->weight = root->data.size();
                (*r) = nullptr;
                (*l)-> parent = nullptr;
                root->left=root->right=nullptr;
                delete root;
                return;
            }
            (*l) = new Node; (*r) = new Node;
            (*l) ->data = root->data.substr(0, idx);
            (*r) ->data = root->data.substr(idx);
            (*l) -> weight = idx; (*r) -> weight = root->data.size() - idx;
            root->left=root->right=nullptr;
            delete root;
            return;
        }
        //not a leaf:
        // find the subtree
        Node *right, *left;
        if(idx >= root->weight){
            split(root->right, idx - root->weight, &left, &right);
            *l = concat(root->left, left);
            *r = right;
        }else{
            split(root->left, idx, &left, &right);
            *l = left;
            *r = concat(right, root->right);
        }
        if(*l) (*l)->parent = nullptr;
        if(*r) (*r)->parent = nullptr;
        root->left = root->right = nullptr;
        delete root;
    }

public:
    Rope(const char* str){
        this->_root = new Node;
        _root->data = string(str);
        _root->weight = _root->data.length();
        _root->left = _root->right = nullptr;
        size = _root->data.size();
    }

    char operator[](int idx){
        return index(_root, idx);
    }

    /* insert at idx, replace the string with
     * S[0...idx - 1]
     * s
     * S[idx ... n - 1]
     * any of them can be empty
     * assert on out of index
     */
    void insert(int idx, string&& s){
        assert(idx >=0 && idx < size);
        Node* left, *right;
        split(_root, idx, &left, &right);
        cout << "insert 1" << endl;
        print_tree(left);
        cout << "insert 2" << endl;
        print_tree(right);
        Node* t = new Node;
        t->data = s;
        t->weight = s.size();
        t->left = t->right = nullptr;
        left = concat(left, t);
        _root = concat(left, right);
        size += s.size();
    }

    void insert(int idx, const char* s){
        insert(idx, std::move(string(s)));
    }

    /*
     * remove char at i... i + j -1
     * give S[0... i - 1]
     * S[i + j ... n - 1]
     * assert on range
     */
    string remove(int i, int j){
        assert( i >=0 && i + j - 1 < size);
        Node* left, *tmp, *mid, *right;
        split(_root, i, &left, &tmp);
        print_tree(left);
        print_tree(tmp);


        split(tmp, j, &mid, &right);
        print_tree(mid);
        print_tree(right);

        _root = concat(left, right);
        cout << dump() << endl;
        size -= j;

    }

    string dump(){
        return _dump(_root);
    }

    string _dump(Node* root, int level){
        if(root == nullptr) return "";
        string rst;
        string indent = "";
        for(int i = 0; i < level; ++i){
            if(i%4 == 0) indent += "|";
            else indent += " ";
        }
        rst += " " + to_string(root->weight);

        if(root->left){
            rst += "\n" + indent + "|->";
            rst += _dump(root->left, level+4);
        }
        if(root->right){
            rst += "\n" + indent + "|->";
            rst += _dump(root->right, level+4);
        }
        if(!root->left && !root->right){
            rst += " "  + root->data;
        }
        return rst;
    }

    string _dump(Node* root){
        if(root==nullptr) return "";
        string rst;
        vector<Node*> s;
        Node* walker = root;
        while(walker){
            s.push_back(walker);
            walker = walker->left;
        }
        while(!s.empty()){
            auto top = s.back(); s.pop_back();
            if(top->right){
                top = top->right;
                while(top){
                    s.push_back(top);
                    top = top->left;
                }
            }else if(top->data.size()){
                rst += top->data;
            }
        }
        return rst;
    }

    void print_tree(Node* root){
        cout << "printing tree: "<<endl << _dump(root, 0) << endl;
    }

    void print_tree(){
        print_tree(_root);
    }

    int length() const{
        return size;
    }
};

TEST_CASE("smoke"){
    Rope obj("Hello world!");
    string expected = "Hello world!";
    REQUIRE(expected == obj.dump());
    REQUIRE(expected.size() == obj.length());

    obj.insert(11, ", from rope");
    obj.print_tree();
    expected = "Hello world, from rope!";
    REQUIRE( expected == obj.dump());
    REQUIRE( expected.size() == obj.length());

    obj.insert(13, "by Junlong ");
    obj.print_tree();
    REQUIRE("Hello world, by Junlong from rope!" == obj.dump());

    obj.insert(0, "Hello, hello, ");
    obj.print_tree();
    REQUIRE("Hello, hello, Hello world, by Junlong from rope!" == obj.dump());

    obj.insert(7, "hello, ");
    obj.print_tree();
    REQUIRE("Hello, hello, hello, Hello world, by Junlong from rope!" == obj.dump());

    obj.remove(21, 13);
    obj.print_tree();
    REQUIRE("Hello, hello, hello, by Junlong from rope!" == obj.dump());

    SECTION("continous from front"){
        int size = obj.length();
        expected = "Hello, hello, hello, by Junlong from rope!";
        for(int i = 0; i < size; ++i){
            obj.remove(0, 1);
            obj.print_tree();
            expected = expected.substr(1);
            REQUIRE(expected == obj.dump());
        }
    }
    SECTION("continous from back"){
        int size = obj.length();
        expected = "Hello, hello, hello, by Junlong from rope!";
        for(int i = 0; i < size; ++i){
            obj.remove(obj.length() - 1, 1);
            obj.print_tree();
            expected.pop_back();
            REQUIRE(expected == obj.dump());
        }
    }
    SECTION("random"){
        srand(time(0));
        int size = obj.length();
        expected = "Hello, hello, hello, by Junlong from rope!";
        for(int i = 0; i < size; ++i){
            int idx = rand()%obj.length();
            obj.remove(idx, 1);
            obj.print_tree();
            expected = expected.substr(0, idx) + expected.substr(idx+1);
            REQUIRE(expected == obj.dump());
        }
    }
    SECTION("seg delete"){
        expected = "Hello, hello, by Junlong from rope!";
        obj.remove(5, 7);
        REQUIRE(expected == obj.dump());
        obj.remove(0, obj.length());
        REQUIRE("" == obj.dump());
    }
    SECTION("index"){
        expected = "Hello, hello, hello, by Junlong from rope!";
        cout << expected.size() << endl;
        for(int i = 0; i < obj.length(); ++i){
            cout << i << endl;
            obj.print_tree();
            REQUIRE(obj[i] == expected[i]);
        }
    }
}

/*
class TextEditor{

};

class Command{
public:
    virtual void redo() = 0;
    virtual void undo() = 0;
    virtual ~Command() = 0;
};

class Insert : Command{
    Rope& r;
    const string& to_insert;
    const int idx;
    int length;
public:
    Insert(Rope& r_, int idx_, const string& to_insert_):
            r(r_), idx(idx_), to_insert(to_insert_){
        length = to_insert.size();
    }
    void redo(){
        r.insert(idx, to_insert);
    }
    void undo(){
        r.remove(idx, length);
    }
    ~Insert(){
        ;
    }
};


class Delete : Command{
    Rope& r;
    Insert* dual;
    string deleted;
    int idx, length;
public:
    Delete(Rope& r_, int idx_, int length_):
            r(r_), idx(idx_), length(length_){
        dual = nullptr;
    }
    void redo(){
        if(dual == nullptr){
            deleted = r.remove(idx, length);
            dual = new Insert(r, idx, deleted);
        }else{
            r.remove(idx, length);
        }
    }
    void undo(){
        r.remove(idx, length);
    }
    ~Delete(){
        ;
    }
};
*/
