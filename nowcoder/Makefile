FD_FLAG 	:= -g
FLAG 		:= -std=c++11
CXX			:= g++
CC			:= gcc

TARGET1		:= test_duplicate
TARGET2		:= test_matrix
TARGET3		:= test_fibonacci
TARGET4		:= test_reorder
TARGET5		:= test_queue
TARGET6		:= test_printmatrix
TARGET7 	:= test_moreThanHalf
TARGET8 	:= test_topk
TARGET9 	:= test_maxSubArray
TARGET10 	:= test_minNumber
TARGET11 	:= test_reversePair
TARGET12 	:= test_countK
TARGET13 	:= test_missingNumber
TARGET14 	:= test_twoSum
TARGET15 	:= test_numberOf1
TARGET16 	:= test_power
TARGET17 	:= test_oneTomax
TARGET18 	:= test_nSum

all : \
	$(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) \
	$(TARGET6) $(TARGET7) $(TARGET8) $(TARGET9) $(TARGET10) \
	$(TARGET11) $(TARGET12) $(TARGET13) $(TARGET14) $(TARGET15) \
	$(TARGET16) $(TARGET17) $(TARGET18)

$(TARGET1) : duplicate.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET2) : matrix.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET3) : fibonacci.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET4) : reorder.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET5) : queue.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET6) : printmatrix.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET7) : moreThanHalf.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET8) : topk.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET9) : maxSubArray.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET10) : minNumber.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET11) : reversePairs.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET12) : countK.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET13) : missingNumber.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET14) : twoSum.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET15) : numberOf1.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET16) : power.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET17) : oneTomax.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

$(TARGET18) : nSum.cpp
	$(CXX) $^ -o $@ $(FD_FLAG) $(FLAG)

.PHONY :

clean :
	rm \
		$(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) \
		$(TARGET6) $(TARGET7) $(TARGET8) $(TARGET9) $(TARGET10) \
		$(TARGET11) $(TARGET12) $(TARGET13) $(TARGET14) $(TARGET15) \
		$(TARGET16) $(TARGET17) $(TARGET18)
