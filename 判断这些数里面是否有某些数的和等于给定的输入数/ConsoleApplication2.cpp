#include <iostream>
#include <vector>
#include <queue>

struct node {
	int n_;
	int level_;
	int* vals_;
	int* ids_;
	bool* is_visit_;
	node* parent_;
	node** p_nodes_;
};

void build(int* a, node** root0, node* parent, int n, int idx, int level, int deep)
{
	if (level == 0)
	{
		*root0 = NULL;
		return;
	}

	*root0 = new node;
	(*root0)->n_ = n - level + 1 - idx;
	(*root0)->ids_ = new int[(*root0)->n_];
	(*root0)->level_ = level;
	(*root0)->vals_ = new int[(*root0)->n_];
	(*root0)->is_visit_ = new bool[(*root0)->n_];
	(*root0)->parent_ = parent;
	(*root0)->p_nodes_ = new node * [(*root0)->n_];
	for (size_t i = idx; i < n - level + 1; i++)
	{
		(*root0)->ids_[i - idx] = i;
		(*root0)->vals_[i - idx] = a[i];
		(*root0)->is_visit_[i - idx] = false;
		if (i + 1 < n)
		{
			build(a, &((*root0)->p_nodes_[i - idx]), *root0, n, i + 1, level - 1, deep + 1);
		}
		else
		{
			(*root0)->p_nodes_[i - idx] = NULL;
		}
	}
}

void search(node* root0, int obj_val)
{
	if (root0 == NULL)
	{
		return;
	}
	for (size_t i = 0; i < root0->n_; i++)
	{
		if (root0->p_nodes_[i] == NULL)
		{
			std::deque<int> path;
			int sum = 0;
			node* node1 = root0;
			do
			{
				sum += node1->vals_[i];
				path.push_front(node1->vals_[i]);
				node1 = node1->parent_;
			} while (node1 != NULL);

			if (sum == obj_val)
			{
				for (size_t i = 0; i < path.size(); i++)
				{
					printf("%d,", path[i]);
				}
				printf("\n");
			}
		}
		else
		{
			search(root0->p_nodes_[i], obj_val);
		}
	}
}

int main()
{
	//int a[5] = { 1, 2, 4, 0, 8 };
	//node* root = NULL;
	//build(a, &root, NULL, 5, 0, 3, 0);

	int a[17] = { 90508, 94818, 93540, 29808, 81620, 31240, 
	99070, 26508, 1800, 19700, 11147, 10120, 98650, 
	37368, 1800, 95480, 27168};
	node* root = NULL;
	build(a, &root, NULL, 17, 0, 9, 0);
	search(root, 400521);
}
