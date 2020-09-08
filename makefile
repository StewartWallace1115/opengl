release:
	g++ -o bin/main.exe main.cpp opengl_ults.cpp glad/include/glad/glad.c -lglfw -lGL -lX11 -lpthread -lXrandr  -ldl

releaseShader:
	g++ -o main.exe main.cpp opengl_ults.cppshader.cpp  glad/include/glad/glad.c -lglfw -lGL -lX11 -lpthread -lXrandr  -ldl

test:  
	g++ -o bin/main_test.exe main_test.cpp opengl_ults.cpp Unity/src/unity.h Unity/src/unity.c glad/include/glad/glad.c -lglfw -lGL -lX11 -lpthread -lXrandr  -ldl

testheadless:  
	g++ -o main_test_headless main_test_headless.cpp opengl_ults.cpp Unity/src/unity.h Unity/src/unity.c glad/include/glad/glad.c -lglfw -lGL -lX11 -lpthread -lXrandr  -ldl

run:   
	make release && ./bin/main.exe
    
runshader:   
	make releaseShader && ./bin/main.exe

testrun:    
	make test && ./bin/main_test.exe

testrunheadless:    
	make testheadless && ./main_test_headless