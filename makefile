#ʹ��.o�滻.cpp
OBJS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
#���ӵĿ��ļ�
LIBS=
#ָ�����ӿ��Ŀ¼
LDFLAGS=
#������
CXX=g++
#ָ��ͷ�ļ�����Ŀ¼
INCPATH=
#������ѡ��
CXXFLAGS=-std=c++11 -O2 -Wall
#�������
TARGET=
$(TARGET):$(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)
.cpp.o:
	$(CXX) $(INCPATH) -c $^ $(CXXFLAGS)
.PHONY:clean
clean:
	rm -f $(TARGET) *.o