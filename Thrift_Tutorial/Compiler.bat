@echo off
echo ��ʼ����,���Ե�.......

.\thrift-0.9.3.exe --gen cpp Interface.thrift

copy  gen-cpp\* .\Thrift_Client\
copy  gen-cpp\* .\Thrift_Server\

rd /s /q .\gen-cpp


echo �������..............

pause