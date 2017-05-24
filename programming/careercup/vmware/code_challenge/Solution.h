//
// Created by Junlong Gao on 8/24/16.
//

#ifndef PRACTISE_SOLUTION_H_H
#define PRACTISE_SOLUTION_H_H

#include "catch.hpp"
#include <cmath>
#include <iostream>

namespace {
    struct LinkedListNode{
        int val;
        LinkedListNode *next;
    };
    using namespace std;
    class Point2D{
    protected:
        long x, y;
    public:
        Point2D(int _x, int _y):x(_x), y(_y){;}
        double dist2D(Point2D p){
            return sqrt(x*p.x + y*p.y);
        }
        void printDistance(double d){
            cout << "2D distance = " << ceil(d) << endl;
        }
    };
    class Point3D : public Point2D {
    protected:
        long z;
    public:
        Point3D(int _x, int _y, int _z):Point2D(_x, _y), z(_z){
        }
        double dist3D(Point3D p){
            return sqrt(x*p.x + y*p.y + z*p.z);
        }
        void printDistance(double d){
            cout << "3D distance = " << ceil(d) << endl;
        }
    };
    class Solution{
    public:
        int sample_solution(int x){
            return x + 1;
        }
        string mergeStrings(string a, string b){
            int i =0, j = 0;
            string rst;
            bool flip = true;
            while(i < a.length() && j < b.length()){
                rst += flip? a[i] : b[j];
                flip?i++:j++;
                flip = !flip;
            }
            while(i < a.length()){
                rst += a[i++];
            }
            while(j < b.length()){
                rst += b[j++];
            }
            return rst;
        }
        int balancedSum(vector<int> arr){
            vector<int> s;
            int sum = 0;
            for(int i = 0; i < arr.size(); ++i){
                sum += arr[i];
                s.push_back(sum);
            }
            if(sum == 0) return 0;
            for(int i = 1; i < arr.size(); ++i){
                if(s[i-1] == sum - arr[i] - s[i-1]){
                    return i;
                }
            }
            return -1;
        }
        LinkedListNode* removeNodes(LinkedListNode* list, int x){
            if(list == nullptr) return list;
            LinkedListNode* rst = removeNodes(list->next, x);
            if(list->val > x){
                list->next = nullptr;
                delete list;
                return rst;
            }else{
                list->next = rst;
                return list;
            }
        }

    };

    TEST_CASE("testing vmware"){
        Solution testObj;
        SECTION("sample solution"){
            REQUIRE(testObj.sample_solution(1)==2);
        }
        SECTION("p1"){
            REQUIRE(testObj.mergeStrings("abc", "def") == "adbecf");
        }
        SECTION("p2"){
            REQUIRE(testObj.balancedSum({1,-2,1}) == 0);
            REQUIRE(testObj.balancedSum({1}) == -1);
            REQUIRE(testObj.balancedSum({1,2,3,3}) == 2);
        }
        SECTION("p4"){
            //concurrent lock
        }
    }
}
#endif //PRACTISE_SOLUTION_H_H
