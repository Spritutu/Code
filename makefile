#ʹ��.o�滻.cpp
SRC:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,%.o,$(notdir $(SRC)))
#���ӵĿ��ļ�
LIBS:=
#ָ�����ӿ��Ŀ¼
LDFLAGS:=
#������
CXX:=g++
#ָ��ͷ�ļ�����Ŀ¼
INCPATH:=
#������ѡ��
CXXFLAGS:=-std=c++11 -O2 -Wall
#�������
TARGET:=
$(TARGET):$(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)
$(OBJS):$(SRC)
	$(CXX) $(INCPATH) -c $^ $(CXXFLAGS)
.PHONY:clean
clean:
	rm -f $(TARGET) *.o