
g++ "-I%1/include" -fconcepts  -lstdc++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++1z -o "%1/debug/%2.o" "%1/%2.cpp" 

g++ -o "%1/debug/%2.exe" "%1/debug/%2.o"

%1/debug/%2.exe 