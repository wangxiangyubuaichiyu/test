#include<iostream>

using namespace std;
//���ϰ����Ϊ��
//������
class lead
{
public:
	lead():next(nullptr){}
	//��֯������
	void nexthr(lead* s)
	{
		next = s;
	}
	//���쵼���
	virtual void leave(int day) = 0;
protected:
	lead* next;
};
//����
class hr :public lead
{
public:
	void leave(int day)
	{
		cout << "����˵��";
		if (day <= 1)
		{
			cout << "����\n";
		}
		else
		{
			cout << "����̫�����Ҿ���\n";
			next->leave(day);
		}
	}
};
//����
class manager :public lead
{
public:
	void leave(int day)
	{
		cout << "����˵��";
		if (day <= 3)
		{
			cout << "����\n";
		}
		else
		{
			cout << "����̫�������ϰ�\n";
			next->leave(day);
		}
	}
};
//�ϰ�
class boss :public lead
{
public:
	void leave(int day)
	{
		cout << "�ϰ�˵��";
		if (day <= 30)
		{
			cout << "����\n";
		}
		else
		{
			cout << "����̫����������׼\n";
		}
	}
};
int main()
{
	lead* a = new hr;
	lead* s = new manager;
	lead* d = new boss;
	//��װ��
	a->nexthr(s);
	s->nexthr(d);

	a->leave(10);
	return 0;
}