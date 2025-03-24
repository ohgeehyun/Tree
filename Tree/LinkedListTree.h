#pragma once
/*
	TreeNode
	부모 정보도 가지고 있어야할까? 고민했는데 일단 진행.
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
	//링크드 리스트 트리
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


	bool add_recursive(int32_t index, int32_t num);  // 재귀적 추가 함수
	bool delete_recursive(int32_t index, int32_t num);  // 재귀적 삭제 함수
	int32_t find_min(int32_t index);  // 최소값을 찾는 함수

};

