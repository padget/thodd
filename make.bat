g++ "-IF:\\project\\thodd\\include" -ftime-report -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\test\\meta_test.o" "test\\meta_test.cpp" 
g++ -o "debug\\meta_test.exe" "debug\\test\\meta_test.o"
debug\\meta_test.exe 

g++ "-IF:\\project\\thodd\\include" -ftime-report -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\test\\tuple_test.o" "test\\tuple_test.cpp" 
g++ -o "debug\\tuple_test.exe" "debug\\test\\tuple_test.o"
debug\\tuple_test.exe 

g++ "-IF:\\project\\thodd\\include" -ftime-report -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\test\\container_test.o" "test\\container_test.cpp" 
g++ -o "debug\\container_test.exe" "debug\\test\\container_test.o"
debug\\container_test.exe

g++ "-IF:\\project\\thodd\\include" -ftime-report -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\test\\lang_test.o" "test\\lang_test.cpp" 
g++ -o "debug\\lang_test.exe" "debug\\test\\lang_test.o"
debug\\lang_test.exe 

echo off

rem g++ "-IF:\\project\\thodd\\include" "-IF:\\project\\thodd\\src" -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\src\\main.o" "src\\main.cpp" 
rem g++ -o "debug\\thodd.exe" "debug\\src\\main.o"