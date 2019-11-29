FD_FLAG 	:= -g -pthread
FLAG 		:= -std=c++11
CXX			:= g++
CC			:= gcc

TARGET1		:= test_mutex
TARGET2		:= test_unique_lock
TARGET3		:= test_lock_guard
TARGET4		:= test_mutex_linux

all : $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)

$(TARGET1) : mutex_test.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET2) : unique_lock_test.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET3) : lock_guard_test.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET4) : mutex_linux_test.c
	$(CC) $^ -o $@ $(FD_FLAG)

.PHONY :

clean :
	rm $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)
