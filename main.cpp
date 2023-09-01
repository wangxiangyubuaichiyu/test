#include<iostream>

using namespace std;
//以上班请假为例
//抽象类
class lead
{
public:
	lead():next(nullptr){}
	//组织链函数
	void nexthr(lead* s)
	{
		next = s;
	}
	//向领导请假
	virtual void leave(int day) = 0;
protected:
	lead* next;
};
//主管
class hr :public lead
{
public:
	void leave(int day)
	{
		cout << "主管说：";
		if (day <= 1)
		{
			cout << "可以\n";
		}
		else
		{
			cout << "天数太长，找经理\n";
			next->leave(day);
		}
	}
};
//经理
class manager :public lead
{
public:
	void leave(int day)
	{
		cout << "经理说：";
		if (day <= 3)
		{
			cout << "可以\n";
		}
		else
		{
			cout << "天数太长，找老板\n";
			next->leave(day);
		}
	}
};
//老板
class boss :public lead
{
public:
	void leave(int day)
	{
		cout << "老板说：";
		if (day <= 30)
		{
			cout << "可以\n";
		}
		else
		{
			cout << "天数太长，不予批准\n";
		}
	}
};
int main()
{
	lead* a = new hr;
	lead* s = new manager;
	lead* d = new boss;
	//组装链
	a->nexthr(s);
	s->nexthr(d);

	a->leave(10);
	return 0;
}