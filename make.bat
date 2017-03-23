g++ "-IF:\\project\\thodd\\include" -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\test\\core_test.o" "test\\core_test.cpp" 
g++ -o "debug\\core_test.exe" "debug\\test\\core_test.o"
debug\\core_test.exe 


REM g++ "-IF:\\project\\thodd\\include" -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\test\\meta_test.o" "test\\meta_test.cpp" 
REM g++ -o "debug\\meta_test.exe" "debug\\test\\meta_test.o"
REM debug\\meta_test.exe 





g++ "-IF:\\project\\thodd\\include" -ftime-report -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\test\\functional_test.o" "test\\functional_test.cpp" 
g++ -o "debug\\functional_test.exe" "debug\\test\\functional_test.o"
debug\\functional_test.exe

echo off

REM g++ "-IF:\\project\\thodd\\include" -ftime-report -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\test\\tuple_test.o" "test\\tuple_test.cpp" 
REM g++ -o "debug\\tuple_test.exe" "debug\\test\\tuple_test.o"
REM debug\\tuple_test.exe 

REM g++ "-IF:\\project\\thodd\\include" -ftime-report -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\test\\container_test.o" "test\\container_test.cpp" 
REM g++ -o "debug\\container_test.exe" "debug\\test\\container_test.o"
REM debug\\container_test.exe

REM g++ "-IF:\\project\\thodd\\include" -ftime-report -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\test\\lang_test.o" "test\\lang_test.cpp" 
REM g++ -o "debug\\lang_test.exe" "debug\\test\\lang_test.o"
REM debug\\lang_test.exe 


rem g++ "-IF:\\project\\thodd\\include" "-IF:\\project\\thodd\\src" -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -o "debug\\src\\main.o" "src\\main.cpp" 
rem g++ -o "debug\\thodd.exe" "debug\\src\\main.o"