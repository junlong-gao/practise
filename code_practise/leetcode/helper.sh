alias lc="leetcode"

function lct() {
   lc cache -d
   lc test $1.cpp -t "$(sed -n '/TESTS/,$p' $1.cpp | sed '1d;$d')";
}

function lctl() {
   lc cache -d
   lc test $1.cpp --local -t "$(sed -n '/TESTS/,$p' $1.cpp | sed '1d;$d')" ;
}

function lcs() {
   lc cache -d
   rm -f $1.*.cpp;
   lc show $1 -g -l cpp -x | less -r;
   mv $1.*.cpp $1.cpp;
   echo "\n\n/*\nTESTS\n\n*/" >> $1.cpp
   git add $1.cpp
}


function lcget() {
   lc cache -d
   leetcode list -q Dh
}

function lcp() {
   lc cache -d
   lc stat -t algorithms
}

function lcdump() {
   lc cache -d
   lcp > README.txt
   lc stat -g > README.txt
}

function lcg() {
   lc cache -d
   leetcode submit $1.cpp
   lcdump
}
