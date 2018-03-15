alias lc="leetcode"

function lct() {
   lc test $1.cpp -t "$(sed -n '/TESTS/,$p' $1.cpp | sed '1d;$d')";
}

function lctl() {
   lc test $1.cpp --local -t "$(sed -n '/TESTS/,$p' $1.cpp | sed '1d;$d')" ;
}

function lcs() {
   rm -f $1.*.cpp;
   lc show $1 -g -l cpp -x | less -r;
   mv $1.*.cpp $1.cpp;
   echo "\n\n/*\nTESTS\n\n*/" >> $1.cpp
   git add $1.cpp
}

function lcg() {
	leetcode submit $1.cpp
}

function lcget() {
   leetcode show -q Dh -x | less -r
}

function lcp() {
   lc stat -t algorithms
}
