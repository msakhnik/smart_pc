bin_PROGRAMS = test

test_SOURCES = ../src/HandDetector.cpp ../src/HandDetector.h \ test.cpp

test_CXXFLAGS = @OPENCV_CFLAGS@ -Wall
test_LDFLAGS = -lgtest_main -lgtest -pthread
test_LDADD = @OPENCV_LIBS@