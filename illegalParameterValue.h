#include<iostream>
#include<sstream>
#include<string>
using namespace std;

//�Զ�����쳣��
class illegalParameterValue
{
public:
	illegalParameterValue(string s = "value is illegal") :message(s) {};
	void output() { cout << message; }
private:
	string message;
};