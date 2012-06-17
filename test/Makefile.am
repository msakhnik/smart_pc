bin_PROGRAMS = test

test_SOURCES = ../src/HandDetector.cpp ../src/HandDetector.h\
../src/AnnTrain.cpp ../src/AnnTrain.h\
../src/CommandProcess.cpp ../src/CommandProcess.h\
                     test.cpp

test_CXXFLAGS = @OPENCV_CFLAGS@ -Wall
test_LDADD = @OPENCV_LIBS@ -lm -lfann -lgtest_main -lgtest