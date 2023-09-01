#include <iostream>
#include<memory>
using namespace std;
template<class T>
class My23tree
{
private:
	struct Node
	{
		int type;//识别当前节点是及节点类型的0，2，3，4
		T data[3];//存入数据的个数
		Node* p[4];//指针的个数
		Node()
		{
			type = 0;
			memset(data, 0, sizeof(T) * 3);
			memset(p, 0, sizeof(Node*) * 4);//这个函数是创建一个对象，然后把里面的值都初始化为零
		}
	};
	Node* TreeNode;
	void _insert(T t, Node* p, Node* onp)
	{
		if (p->type==0)//当节点是0指针的时候
		{
			p->data[0] = t;
			p->type = 2;
			return;
		}
		 if (p->type==2)//当节点是2指针的时候
		{
			if (p->data[1]<t)//当数据大于第一个数据的时候
			{
				if (p->p[1])//当数据有左孩子的时候放到右节点
				{
					_insert(t, p->p[1], p);
				}
				else//没有左孩子直接放到旁边
				{
					p->data[1] = t;
					p->type = 3;
				}
			}
			else
			{
				if (p->p[0])//当数据有左孩子的时候放到右节点
				{
					_insert(t, p->p[0], p);
				}
				else//没有左孩子直接放到旁边
				{

					p->data[1] = p->data[0];
					p->data[0] = t;
					p->type = 3;
				}
			}
		}
		else//当节点是3指针的时候
		{
			if (p->data[0]>t)//插左边
			{
				if (p->p[0])//有孩子
				{
					_insert(t, p->p[0], p);
				}
				else
				{
					p->data[2] = p->data[1];
					p->data[1] = p->data[0];
					p->data[0] = t;
					p->type++;
				}
			}
			else if (p->data[1] > t&&p->data[0] < t)//插中间
			{
				if (p->p[1])//有孩子
				{
					_insert(t, p->p[1], p);
				}
				else
				{
					p->data[2] = p->data[1];
					p->data[1] = t;
					p->type++;
				}
			}
			else if (p->data[2] < t)//插右边
			{
				if (p->p[2])//有孩子
				{
					_insert(t, p->p[2], p);
				}
				else
				{
					p->data[2] = t;
					p->type++;
				}
			}
		}
		if (p->type==4)//当节点是4指针的时候
		{
			//创建两个节点
			Node* node1 = new Node;
			Node* node2 = new Node;
			node1->data[0] = p->data[0];
			node1->p[0] = p->p[0];
			node1->p[1] = p->p[1];
			node1->type = 2;
			node2->data[0] = p->data[2];
			node2->p[0] = p->p[2];
			node2->p[1] = p->p[3];
			node2->type = 2;
			T ts = p->data[1];//临时存储中间数据
			if (onp)
			{
				//5 找位置 做插入
				if (ts< onp->data[0]) {//左边
					if (onp->p[2]) {//最右边有孩子
						onp->data[2] = onp->data[1];
						onp->data[1] = onp->data[0];
						onp->data[0] = ts;

						onp->p[3] = onp->p[2];
						onp->p[2] = onp->p[1];
						onp->p[1] = node2;
						onp->p[0] = node1;
					}
					else if (onp->p[1]) {//最右边没有孩子，中间有孩子
						onp->data[1] = onp->data[0];
						onp->data[0] = ts;
						
						onp->p[2] = onp->p[1];
						onp->p[1] = node2;
						onp->p[0] = node1;
					}
				}
				else if (2 == onp->type ||
					(onp->type > 1)
					&&
					ts < onp->data[1]) {//中间

					if (onp->p[2]) {//最右边有孩子
						onp->data[2] = p->data[1];
						onp->data[1] = ts;
						
						onp->p[3] = onp->p[2];
						onp->p[2] = node2;
						onp->p[1] = node1;
					}
					else if (onp->p[1]) {//最右边没有孩子，中间有孩子
						onp->data[1] = ts;
						onp->p[2] = node2;
						onp->p[1] = node1;
					}
				}
				else if (3 == onp->type ||
					(onp->type > 2) && (ts< onp->data[2])) {//右边
					if (onp->p[2]) {
						onp->data[2] = ts;
						onp->p[3] = node2;
						onp->p[2] = node1;
					}
				}
				onp->type++;
				//6 释放内存
				delete p;
			}
			else//当前是没有父节点
			{
				memset(p->data, 0, sizeof(T) * 3);
				memset(p->p, 0, sizeof(Node*) * 4);
				p->data[0] = ts;
				p->type = 2;
				p->p[0] = node1;	p->p[1] = node2;
			}
		}
	}
public:
	My23tree() { TreeNode = nullptr; }
	~My23tree(){}
	void insert(T t)
	{
		if (TreeNode)
		{
			_insert(t, TreeNode, NULL);
		}
		else
		{
			TreeNode = new Node();
			TreeNode->data[0] = t;
			TreeNode->type = 2;
		}

	}
};

int main()
{
	int arr[10] = { 55, 99, 24, 66, 11, 10, 77, 13, 38, 91 };
	My23tree<int> t;

	for (int i = 0; i < 10; i++)
		t.insert(arr[i]);

    return 0;
}

