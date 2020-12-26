#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <limits>
#include "catch.hpp"
#include "printer.h"

namespace lee282{
   using namespace std;
   class Solution{
      vector<string> rst;
      long size, target;

   public:
      vector<string> addOperators(string num, int target) {
         size = num.length();
         this->target = target;
         dfs(num, "", 0, 0, 0);
         return rst;
      }
      void dfs(string& num, string sofar, long pos, long factor, long val){
         if(pos == size){
            if(val == target){
               rst.push_back(sofar);
            }
            return;
         }
         for(long i = pos; i < size; ++i){
            if(num[pos] == '0' && i != pos) break; //cannot form this number
            string tmp = num.substr(pos, i - pos + 1);
            long tmp_val = atol(tmp.c_str()); //atoi vs atol
            if(pos == 0){
               dfs(num, tmp, i + 1, tmp_val, tmp_val);
            }else{
               dfs(num, sofar + "+" + tmp, i + 1, tmp_val, val + tmp_val);
               dfs(num, sofar + "-" + tmp, i + 1, -tmp_val, val - tmp_val);
               dfs(num, sofar + "*" + tmp, i + 1, factor*tmp_val, val - factor + factor*tmp_val);
            }
         }
      }
   };


   TEST_CASE("smoke 282"){
      Solution testObj;
      SECTION("sample 0"){
         auto tmp = testObj.addOperators("2147483648", -2147483648);
         LOG(INFO) << sequential::printer(tmp, [](const string& t){
            return t;
         });
         unordered_set<string> rst(tmp.begin(), tmp.end());
         REQUIRE(rst.size() == 0);
      }
      SECTION("sample 1"){
         auto tmp = testObj.addOperators("123", 6);
         LOG(INFO) << sequential::printer(tmp, [](const string& t){
            return t;
         });
         unordered_set<string> rst(tmp.begin(), tmp.end());
         REQUIRE(rst.find("1+2+3")!=rst.end());
         REQUIRE(rst.find("1*2*3")!=rst.end());
      }
      SECTION("sample 2"){
         auto tmp = testObj.addOperators("232", 8);
         LOG(INFO) << sequential::printer(tmp, [](const string& t){
            return t;
         });
         unordered_set<string> rst(tmp.begin(), tmp.end());
         REQUIRE(rst.size() == 2);
         REQUIRE(rst.find("2*3+2")!=rst.end());
         REQUIRE(rst.find("2+3*2")!=rst.end());
      }
      SECTION("sample 3"){
         auto tmp = testObj.addOperators("105", 5);
         LOG(INFO) << sequential::printer(tmp, [](const string& t){
            return t;
         });
         unordered_set<string> rst(tmp.begin(), tmp.end());
         REQUIRE(rst.size() == 2);
         REQUIRE(rst.find("1*0+5")!=rst.end());
         REQUIRE(rst.find("10-5")!=rst.end());
      }
      SECTION("sample 4"){
         auto tmp = testObj.addOperators("3456237490", 9191);
         LOG(INFO) << sequential::printer(tmp, [](const string& t){
            return t;
         });
         unordered_set<string> rst(tmp.begin(), tmp.end());
         REQUIRE(rst.empty());
      }
      SECTION("sample 5"){
         auto tmp = testObj.addOperators("00", 0);
         LOG(INFO) << sequential::printer(tmp, [](const string& t){
            return t;
         });
         unordered_set<string> rst(tmp.begin(), tmp.end());
         REQUIRE(rst.size() == 3);
         REQUIRE(rst.find("0+0")!=rst.end());
         REQUIRE(rst.find("0-0")!=rst.end());
         REQUIRE(rst.find("0*0")!=rst.end());
      }
   }
}
