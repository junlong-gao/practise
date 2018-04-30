# in where the cpp file lives: compile 279.cpp, then run
function compile {
   docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp gcc g++ -o main $1 --std=c++11
}

function run {
   docker run -it --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp gcc ./main
}