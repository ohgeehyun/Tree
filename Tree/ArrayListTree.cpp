#include "pch.h"
#include "ArrayListTree.h"

ArrayListTree::ArrayListTree() 
{
}

ArrayListTree::~ArrayListTree()
{
	_nodes.clear();
}

bool ArrayListTree::resize(int32 size)
{   
	try 
	{
		_nodes.resize(size);

		if (_nodes.size() < _nodes.capacity()) {
			_nodes.shrink_to_fit();  // 불필요한 메모리 할당 제거
		}

		 return true;
	}
	catch(const std::bad_alloc& e)
	{
		cout << "Memory allocation failed : " << e.what() << std::endl;
		return false;
	}
}

bool ArrayListTree::reserve(int32 size)
{
	try
	{
		_nodes.reserve(size);

		return true;
	}
	catch(const std::bad_alloc & e)
	{
		cout << "Memory reserve failed : " << e.what() << std::endl;
		return false;
	}
}

bool ArrayListTree::add_element(int32 num)
{
	if (_nodes.empty()) {
		_nodes.push_back(num);
		_min_value = num;
		_max_value = num;
		_height = 1;
		return true;
	}

	bool result = add_recursive(0, num);

	if (result)
	{
		// 값 추가 성공후 높이 최소 최대값 갱신
		update_min_max(num);

		// 새 노드의 부모부터 루트까지 높이를 갱신
		int32 index = _nodes.size() - 1;  // 새로 추가된 노드의 인덱스
		while (index >= 0) {
			update_height(index);  // 현재 노드의 높이를 갱신
			index = parent(index);  // 부모 노드로 이동
		}
	}

	return result;
}

bool ArrayListTree::delete_element(int32 num)
{
	// 트리의 루트부터 시작하여 삭제할 값 찾기
	return delete_recursive(0, num);
}

bool ArrayListTree::add_recursive(int32_t index, int32_t num)
{
	if (index >= _nodes.size()) {
		_nodes.push_back(num);  // 새로운 노드를 추가
		return true;
	}

	if (num < _nodes[index]) {
		int32_t leftIndex = left_child(index);
		if (leftIndex >= _nodes.size()) {
			_nodes.push_back(num);
		}
		else {
			return add_recursive(leftIndex, num);  // 왼쪽 서브트리로 재귀 호출
		}
	}
	else {
		int32_t rightIndex = right_child(index);
		if (rightIndex >= _nodes.size()) {
			_nodes.push_back(num);
		}
		else {
			return add_recursive(rightIndex, num);  // 오른쪽 서브트리로 재귀 호출
		}
	}

	return true;
}

bool ArrayListTree::delete_recursive(int32_t index, int32_t num)
{
	if (index >= _nodes.size()) return false;  // 범위를 벗어나면 실패

	if (_nodes[index] == num) 
	{
		//삭제할 값은 찾은 경우 삭제할 노드의상태에 따라 case가 나뉨.

		//자식이없음 그냥 삭제해도 ok
		if (left_child(index) >= _nodes.size() && right_child(index) >= _nodes.size()) {
			_nodes.erase(_nodes.begin() + index);
			return true;
		}

		// 자식이 하나만 있는 경우 오른쪽 자식 
		if (left_child(index) >= _nodes.size()) {
			_nodes[index] = _nodes[right_child(index)];
			_nodes.erase(_nodes.begin() + right_child(index));
			return true;
		}
		// 자식이 하나만 있는 경우 왼쪽 자식
		if (right_child(index) >= _nodes.size()) {
			_nodes[index] = _nodes[left_child(index)];
			_nodes.erase(_nodes.begin() + left_child(index));
			return true;
		}

		// 자식이 두 개인 경우: 오른쪽 서브트리에서 최소값을 찾아서 교체
		int32_t minIndex = find_min(right_child(index));
		_nodes[index] = _nodes[minIndex];
		delete_recursive(minIndex, _nodes[minIndex]);
		return true;

	}

	if (num < _nodes[index]) {
		return delete_recursive(left_child(index), num);  // 왼쪽 서브트리로 재귀 호출
	}
	else {
		return delete_recursive(right_child(index), num);  // 오른쪽 서브트리로 재귀 호출
	}
}

int32_t ArrayListTree::find_min(int32_t index)
{
	while (left_child(index) < _nodes.size()) {
		index = left_child(index);
	}
	return index;
}

void ArrayListTree::update_height(int32_t index)
{
	int32_t left = left_child(index);
	int32_t right = right_child(index);

	int32_t left_height = (left < _nodes.size()) ? _height : 0;
	int32_t right_height = (right < _nodes.size()) ? _height : 0;

	// 현재 노드의 높이는 왼쪽과 오른쪽 자식의 높이 중 큰 값 + 1
	_height = std::max(left_height, right_height) + 1;
}

void ArrayListTree::update_min_max(int32_t num)
{
	if (num < _min_value) {
		_min_value = num;
	}
	if (num > _max_value) {
		_max_value = num;
	}
}

void ArrayListTree::update_min_max_after_delete()
{
	if (_nodes.empty()) {
		_min_value = INT_MAX;
		_max_value = INT_MIN;
		return;
	}

	_min_value = find_min(0);
	_max_value = find_max(0);
}

int32 ArrayListTree::find_min(int32 index)
{
	while (left_child(index) < _nodes.size()) {
		index = left_child(index);
	}
	return _nodes[index];
}

int32 ArrayListTree::find_max(int32 index)
{
	while (right_child(index) < _nodes.size()) {
		index = right_child(index);
	}
	return _nodes[index];
}




