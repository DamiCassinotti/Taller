cmake_minimum_required(VERSION 3.8)
project(TP3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Makefile src/commonSocket.cpp src/commonSocket.h src/clientMain.cpp
        src/serverMain.cpp src/clientBinaryFile.cpp src/clientBinaryFile.h
        src/clientOperations.h src/commonFile.cpp src/commonFile.h
        src/serverThread.cpp src/serverThread.h  src/serverThreads.cpp
        src/serverThreads.h src/serverCardsData.cpp
        src/serverCardsData.h src/serverProcessingCardException.cpp src/serverProcessingCardException.h src/serverAcceptConnectionsThread.cpp src/serverAcceptConnectionsThread.h src/serverProcessClientThread.cpp src/serverProcessClientThread.h src/serverQuitThread.cpp src/serverQuitThread.h)

add_executable(TP3 ${SOURCE_FILES})