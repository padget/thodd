g++ "-IF:\\project\\thodd\\src" -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\src\\main.o" "src\\main.cpp" 
g++ -o "debug\\thodd.exe" "debug\\src\\main.o"