//
// Created by Junlong Gao on 8/7/16.
//

#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "Solution.h"
#include <string>
using namespace std;

int main(int argc, char* const argv[]){
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	// Values are always std::string
	defaultConf.set(el::Level::Info, 
	el::ConfigurationType::Format, "%datetime:%level\n\tat:<%func>\n%msg");
	el::Loggers::reconfigureLogger("default", defaultConf);
    

    return Catch::Session().run( argc, argv );
}

TEST_CASE("214 smoke"){
    lee214::Solution testObj;
    SECTION("simple"){
        string s = "ab";
        string tmp = s;
        reverse(tmp.begin(), tmp.end());
        REQUIRE(testObj.kmp(s + "#" + tmp) == 1);
    }
    SECTION("sample 1"){
        string s = "aacecaaa";
        string tmp = s;
        reverse(tmp.begin(), tmp.end());
        REQUIRE(testObj.kmp(s + "#" +tmp) == 7);
        REQUIRE(testObj.shortestPalindrome(s) == "aaacecaaa");
    }
    SECTION("sample 2"){
        string s = "abcd";
        string tmp = s;
        reverse(tmp.begin(), tmp.end());
        REQUIRE(testObj.kmp(s + "#" +tmp) == 1);
        REQUIRE(testObj.shortestPalindrome(s) == "dcbabcd");
    }
    SECTION("corner empty"){
        string s = "";
        string tmp = s;
        reverse(tmp.begin(), tmp.end());
        REQUIRE(testObj.kmp(s + "#" +tmp) == 0);
        REQUIRE(testObj.shortestPalindrome(s) == "");
    }
    SECTION("corner"){
        string s = "a";
        string tmp = s;
        reverse(tmp.begin(), tmp.end());
        REQUIRE(testObj.kmp(s + "#" +tmp) == 1);
        REQUIRE(testObj.shortestPalindrome(s) == "a");
    }
}