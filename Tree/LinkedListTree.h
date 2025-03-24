#pragma once
/*
	TreeNode
	�θ� ������ ������ �־���ұ�? ����ߴµ� �ϴ� ����.
*/

struct TreeNode 
{
	int32 data;
	TreeNode* left;
	TreeNode* right;
};


/*
	LinkedListTree
*/
class LinkedListTree
{
	//��ũ�� ����Ʈ Ʈ��
public:
	LinkedListTree();
	LinkedListTree(int32 size);
	~LinkedListTree();

	bool resize(int32 size);
	bool reserve(int32 size);

	bool add_element(int32 num);
	bool delete_element(int32 num);

private:
	std::vector<int32> _nodes;

	int32 left_child(int32 index) { return 2 * index + 1; }
	int32 right_child(int32 index) { return 2 * index + 2; }
	int32 parent(int32 index) { return(index - 1) / 2; }


	bool add_recursive(int32_t index, int32_t num);  // ����� �߰� �Լ�
	bool delete_recursive(int32_t index, int32_t num);  // ����� ���� �Լ�
	int32_t find_min(int32_t index);  // �ּҰ��� ã�� �Լ�

};

