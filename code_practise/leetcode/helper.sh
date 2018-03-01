alias lc="leetcode"

function lct() {
   lc test $1.cpp -t "$(sed -n '/TESTS/,$p' $1.cpp | sed '1d;$d')";
}

function lcs() {
   rm -f $1.*.cpp;
   lc show $1 -g;
   mv $1.*.cpp $1.cpp;
   echo "\n\n/*\nTESTS\n\n*/" >> $1.cpp
}

