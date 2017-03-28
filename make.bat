g++ "-IF:\\project\\thodd\\include" -ftime-report -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\test\\tuple_test.o" "test\\tuple_test.cpp" 
g++ -o "debug\\tuple_test.exe" "debug\\test\\tuple_test.o"
debug\\tuple_test.exe 
