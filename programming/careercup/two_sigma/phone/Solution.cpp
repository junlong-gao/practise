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
#include <assert.h>

using namespace std;
class MedianFinder {
    priority_queue<int, vector<int>, std::greater<int>> upper;
    priority_queue<int, vector<int>, std::less<int>> lower;

    template<typename T1, typename T2>
    void balance(T1& larger, T2& smaller){
        while(!larger.empty() && larger.size() - smaller.size() >= 2){
            auto top = larger.top(); larger.pop();
			cout << top << endl;
            smaller.push(top);
        }
    }
public:

    // Adds a number into the data structure.
    void addNum(int num) {
		cout << "adding " << num << endl;
        if(lower.empty() || num <= lower.top()){
			lower.push(num);
			cout << "lower: " << lower.top() << endl;
        }else{
            upper.push(num);
			cout << "upper: " << upper.top() << endl;
        }
        if((int)(lower.size() -upper.size()) >= 2){
			cout << "lower size " << lower.size() << endl;
			cout << "upper size " << upper.size() << endl;
            balance(lower, upper);
        }
        if((int)(lower.size() - upper.size()) <= -2){
            balance(upper, lower);
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        if(upper.size() != lower.size()){
            return upper.size() > lower.size() ? (double)upper.top()
                                            :(double)lower.top();
        }
        return (double)(upper.top() + lower.top())/2.0;
    }
};

TEST_CASE("median finder smoke"){
	MedianFinder obj;
	obj.addNum(1);
	REQUIRE(obj.findMedian() == 1);
	obj.addNum(2);
	REQUIRE(obj.findMedian() == 1.5);
	obj.addNum(3);
	REQUIRE(obj.findMedian() == 2);
	obj.addNum(0);
	REQUIRE(obj.findMedian() == 1.5);
}

class InfixEval {
    int eval(char op, int oprand1, int oprand2){
        switch(op){
            case '+':{
                return oprand1 + oprand2;
            }
            case '-':{
                return oprand1 - oprand2;
            }
            case '*':{
                return oprand1 * oprand2;
            }
            case '/':{
                return oprand1 / oprand2;
            }
            default:{
                break;
            }
        }
        assert(0);
    }
    int level(char op){
        if(op == '*' || op == '/') return 1;
        if(op == '+' || op == '-') return 0;
        assert(0);
    }
    void reduce(vector<int>& NumStack, vector<char>& OpStack){
        assert(NumStack.size() >= 2);
        assert(OpStack.size() >= 1);
        int oprand2 = NumStack.back(); NumStack.pop_back();
        int oprand1 = NumStack.back(); NumStack.pop_back();
        NumStack.push_back(eval(OpStack.back(), oprand1, oprand2));
        OpStack.pop_back();
    }
public:
    /*
     * For each token:
     *   1. If it is a number, push into NumStack
     *   2. else if it is an operator, push into OpStack, reduce it as necessary
     *   3. else if it is a left parentheis, push
     *   4. else it is right, eval the top two of the NumStack with the top of OpStack and push back in.
     */
    /*
     * reduce: given OpStack, NumStack and new operator, determine whether we can perform the top of
     * OpStack first before push
     *   1. if incomming is the same class or lower and the top is not left parenthsis: pop two and the op, eval and push back
     *   2. if incomming is higher: push back the op
     */
    int eval(vector<string> tokens){
        vector<int> NumStack;
        vector<char> OpStack;
        for(int i = 0; i < tokens.size(); ++i){
            if(tokens[i].size() == 1 && (tokens[i][0] < '0'|| tokens[i][0]>'9')){
               if(tokens[i][0] == '('){
                   OpStack.push_back('(');
                   continue;
               }
               if(tokens[i][0] == ')'){
                   if(OpStack.back() != '('){
                       reduce(NumStack, OpStack);
                   }
                   assert(OpStack.size() >= 1 && OpStack.back() == '(');
                   OpStack.pop_back();
                   continue;
               }
               //operators
               if(OpStack.empty() || OpStack.back() == '('){
                   OpStack.push_back(tokens[i][0]);
                   continue;
               }

               if(level(OpStack.back()) >= level(tokens[i][0])){
                   reduce(NumStack, OpStack);
               }
               OpStack.push_back(tokens[i][0]);
            }else{
               NumStack.push_back(atoi(tokens[i].c_str()));
            }
        }
        while(!OpStack.empty()){
            reduce(NumStack, OpStack);
        }
        return NumStack.back();
    }
};

TEST_CASE("eval"){
    InfixEval obj;
    REQUIRE(obj.eval({"1", "+", "2"}) == 3);
    REQUIRE(obj.eval({"(", "1", ")"}) == 1);
    REQUIRE(obj.eval({"(", "1", "*", "(", "-2", "-", "-1", ")", ")"}) == -1);
    REQUIRE(obj.eval({"(", "1", "+", "3", ")", "*", "(", "-2", "-", "-1", ")", "*", "1"}) == -4);
    REQUIRE(obj.eval({"1","+", "(", "1", "+", "3", ")", "*", "(", "-2", "-", "-1", ")", "*", "2"}) == -7);
}

class BiasedDice{
    /*
     * let p0, p1 .. p_n be the ratio of x_i's weight.
     * let P_k be the cumulative distribution \sum_{i = 0}^kp_k, P_{n+1} = 1
     * we define Z be a uniform rand on [0, 1]
     * X be a rand var with the following mapping f:
     * f(Z) = x_k where k is the index such that P_k < P_{k+1} this can be thought as
     * a partition over the sample space of Z
     * then P(X = x_k) = p_k
     *
     * internally maintain P_k's
     * fast look up ?
     *
     *  native implementation:
     *  maintain a map of face->index
     *  index->point mass
     *  to set just change weight literally
     *  to get, gen a number between 0 and total, find first accumulated sum > total
     *
     * 1. work only in the index domain and partial sum of weight.
     * 2. a data structure allow for fast query of the range
     */
    int total_weight;
    vector<int> index_to_face;
    unordered_map<int, unsigned int> face_to_index;
    vector<int> weights;
    vector<int> cdf_cache;
    bool cache_valid;

public:
    BiasedDice():total_weight(0), cache_valid(true){
        srand(time(0));
    }
    void print_state(){
        cout << "----" << endl;
        cout << "current index and face: " << endl;
        for(int i = 0; i< index_to_face.size(); ++i){
            cout << i << ": " << index_to_face[i] << " has weight: " << weights[i] << endl;
        }
        cout << "total weight is " << total_weight<< endl;
        cout << "cache is ";
        if(cache_valid){
            cout << "valid. the cdf is: "<< endl;
            assert(cdf_cache.size() == weights.size());
            assert(weights.size() == index_to_face.size());
            for(int i = 0; i < cdf_cache.size(); ++i){
                cout << i << ": " << cdf_cache[i] << endl;
            }
            return;
        }
        cout << "not valid." << endl;
        cout << "----" << endl;
    }
    /*
     * return an element randomly, the distribution is proprotional to
     * the weights
     */
    int getRandom(){
        if(cache_valid){
            unsigned int val = rand() % (total_weight+1);
            auto it = lower_bound(cdf_cache.begin(), cdf_cache.end(), val);
            return index_to_face[(int)(it - cdf_cache.begin())];
        }

        int count = 0;
        cdf_cache.clear();
        for(int i = 0; i < weights.size(); ++i){
            count += weights[i];
            cdf_cache.push_back(count);
        }
        cache_valid= true;
        return getRandom();
    }
    /*
     * set the weight of an element, each element is an integer
     * O(1)
     */
    void setFaceWeight(int face, unsigned int weight){
        if(face_to_index.find(face) == face_to_index.end()){
            cout << "inserting " << face << " " << weight << endl;
            cache_valid= false;
            index_to_face.push_back(face);
            face_to_index[face] = index_to_face.size() - 1;
            weights.push_back(weight);
            total_weight += (weight);
            assert(index_to_face.size() == weights.size());
        }else if((weight - weights[face_to_index[face]])){
            cache_valid= false;
            total_weight += (weight - weights[face_to_index[face]]);
            weights[face_to_index[face]] += weight;
        }
    }
};
TEST_CASE("biased dice"){
    BiasedDice obj;
    obj.setFaceWeight(7, 1);
    obj.setFaceWeight(8, 2);
    obj.setFaceWeight(9, 0);
    obj.print_state();
    cout <<" generated: " << obj.getRandom() << endl;
    obj.print_state();
    obj.setFaceWeight(9, 0);
    obj.print_state();
    cout <<" generated: " << obj.getRandom() << endl;
    obj.setFaceWeight(9, 1);
    obj.print_state();
    cout <<" generated: " << obj.getRandom() << endl;
    obj.print_state();
    REQUIRE(1==1);
}

class ReservoirSampling{
public:
    ReservoirSampling(){
        srand(time(0));
    }
    template<typename T>
    vector<int> Sampling(T&& stream, int&& k){
        assert(k <= stream.size());
        vector<int> samples(stream.begin(), stream.begin() + k);
        for(int i = k; i < stream.size(); ++i){
           int j = rand()%(i + 1);
            if(j < k){
                samples[j] = stream[i];
            }
        }
        return samples;
    }
};

TEST_CASE("reservior"){
    ReservoirSampling obj;
    vector<int> test = {1,2,3,4,5,6,7};
    for(int i = 0; i < 10; i++){
        auto rst = obj.Sampling(test, 3);
        cout << "reservior sampling:"<< endl;
        for(auto& ele : rst){
            cout << ele << " ";
        }
        cout << endl;
    }
    REQUIRE(1);
}