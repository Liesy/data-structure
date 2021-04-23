#include<iostream>
#include<sstream>
#include<string>
using namespace std;

//自定义的异常类
class illegalParameterValue
{
public:
	illegalParameterValue(string s = "value is illegal") :message(s) {};
	void output() { cout << message; }
private:
	string message;
};