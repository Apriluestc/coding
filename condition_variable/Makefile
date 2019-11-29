FD_FLAG	:= -pthread
FLAG	:= -g -std=c++11
CXX		:= g++

TARGET1	:= test_wait
TARGET2	:= test_notify
TARGET3	:= test_condition_variable_any

all : $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1) : condition_variable_wait_test.cpp
	$(CXX) $^ -o $@ $(FLAG) $(FD_FLAG)

$(TARGET2) : condition_variable_notify_test.cpp
	$(CXX) $^ -o $@ $(FLAG) $(FD_FLAG)

$(TARGET3) : condition_variable_any_test.cpp
	$(CXX) $^ -o $@ $(FLAG) $(FD_FLAG)

.PHONY :

clean :
	rm $(TARGET1) $(TARGET2)
