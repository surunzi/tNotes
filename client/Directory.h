/*
     Ŀ¼�� Directory
     ��������Ҫ����
*/
#include<string>
using namespace std;
#ifndef DIRECTORY_H
#define DIRECTORY_H
class Directory
{
public:
    string nodeId;                  //Ŀ¼id,�������ͬ��ʹ��
    string name;                    //Ŀ¼����
    string createTime;              //Ŀ¼����ʱ��
    string modifiedTime;             //Ŀ¼�޸�ʱ��
    Directory(string nodeId,string name,string createTime,string modifiedTime)
    {
    this->nodeId=nodeId;
    this->name=name;
    this->createTime=createTime;
    this->modifiedTime=modifiedTime;
    }
    ~Directory(){}
};
#endif