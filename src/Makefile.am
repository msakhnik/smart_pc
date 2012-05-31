bin_PROGRAMS = smart_pc

smart_pc_SOURCES = HandDetector.cpp HandDetector.h\
	 AnnTrain.cpp AnnTrain.h\
	 CommandProcess.cpp CommandProcess.h\
                     main.cpp

smart_pc_CXXFLAGS = @OPENCV_CFLAGS@ -Wall
smart_pc_LDADD = @OPENCV_LIBS@ -lm -lfann
