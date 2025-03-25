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
		_nodes.resize(size, std::nullopt);
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
		cout << "삽입 완료: " << num << endl; 
		return true;
	}

	bool result = add_recursive(0, num);

	if (result)
	{
		// 값 추가 성공후 높이 최소 최대값 갱신
		update_min_max(num);

		// 새 노드의 부모부터 루트까지 높이를 갱신
		int32 index = _nodes.size() - 1; 
		while (index > 0) { 
			update_height(index);  
			int32 parentIndex = parent(index);
			if (parentIndex == index) break; 
			index = parentIndex;  
		}
	}
	cout << "삽입 완료: " << num << endl;
	return result;
}

bool ArrayListTree::delete_element(int32 num)
{
	// 트리의 루트부터 시작하여 삭제할 값 찾기
	if (delete_recursive(0, num))
	{
		cout << "element 삭제 완료" << endl;
		return true;
	}
	else
	{
		cout << "삭제 할 element가 트리에 존재 하지 않습니다." << endl;
		return false;
	}
		
}

bool ArrayListTree::add_recursive(int32_t index, int32_t num)
{
	if (index >= _nodes.size()) {
		_nodes.resize(index + 1, std::nullopt);
	}

	// 현재 위치가 비어있다면 바로 삽입
	if (!_nodes[index].has_value()) {
		_nodes[index] = num;
		return true;
	}

	if (num < _nodes[index]) {
		int32 leftIndex = left_child(index);
		return add_recursive(leftIndex, num);  // 왼쪽 서브트리로 이동
	}
	else {
		int32 rightIndex = right_child(index);
		return add_recursive(rightIndex, num);  // 오른쪽 서브트리로 이동
	}

	return true;
}

bool ArrayListTree::delete_recursive(int32_t index, int32_t num)
{
	if (index >= _nodes.size()) return false;  // 범위를 벗어나면 실패

	if (_nodes[index].has_value() && _nodes[index].value() == num)
	{
		// 자식이 없는 경우: 단순히 제거
		if ((left_child(index) >= _nodes.size() || !_nodes[left_child(index)].has_value()) &&
			(right_child(index) >= _nodes.size() || !_nodes[right_child(index)].has_value())) {
			_nodes[index] = std::nullopt;
		}
		// 자식이 하나인 경우
		else if (left_child(index) >= _nodes.size() || !_nodes[left_child(index)].has_value()) {
			_nodes[index] = _nodes[right_child(index)];
			_nodes[right_child(index)] = std::nullopt;
		}
		else if (right_child(index) >= _nodes.size() || !_nodes[right_child(index)].has_value()) {
			_nodes[index] = _nodes[left_child(index)];
			_nodes[left_child(index)] = std::nullopt;
		}
		// 자식이 두 개인 경우: 오른쪽 서브트리에서 최소값을 찾아 교체
		else
		{
			int32 minIndex = find_min_index(right_child(index));
			_nodes[index] = _nodes[minIndex];
			delete_recursive(minIndex, _nodes[minIndex].value());
		}

		update_min_max_after_delete();

		while (index > 0)
		{
			update_height(index);
			index = parent(index);
		}
		update_height(0);

		return true;

	}

	if (num < _nodes[index]) {
		return delete_recursive(left_child(index), num);  // 왼쪽 서브트리로 재귀 호출
	}
	else {
		return delete_recursive(right_child(index), num);  // 오른쪽 서브트리로 재귀 호출
	}

	return false;
}

void ArrayListTree::update_height(int32_t index)
{
	int32_t left = left_child(index);
	int32_t right = right_child(index);

	int32 left_height = (left < _nodes.size() && _nodes[left].has_value()) ? _height : 0;
	int32 right_height = (right < _nodes.size() && _nodes[right].has_value()) ? _height : 0;

	// 현재 노드의 높이는 왼쪽과 오른쪽 자식의 높이 중 큰 값 + 1
	_height = std::max(left_height, right_height) + 1;
}

void ArrayListTree::update_min_max(int32_t num)
{
	if (!_nodes.empty()) {
		_min_value = std::min(_min_value, num);
		_max_value = std::max(_max_value, num);
	}
	else {
		_min_value = num;
		_max_value = num;
	}
}

void ArrayListTree::update_min_max_after_delete()
{
	_min_value = find_min(0);
	_max_value = find_max(0);
}

int32 ArrayListTree::find_min(int32 index)
{
	int32 minValue = INT_MAX;
	while (index < _nodes.size()) {
		if (_nodes[index].has_value()) {
			minValue = std::min(minValue, _nodes[index].value());
		}
		index = left_child(index);
	}
	return (minValue == INT_MAX) ? _min_value : minValue;
}

int32 ArrayListTree::find_max(int32 index)
{
	int32 maxValue = INT_MIN;
	while (index < _nodes.size()) {
		if (_nodes[index].has_value()) {
			maxValue = std::max(maxValue, _nodes[index].value());
		}
		index = right_child(index);
	}
	return (maxValue == INT_MIN) ? _max_value : maxValue;
}

int32 ArrayListTree::find_min_index(int32 index)
{
	while (index < _nodes.size() && _nodes[index].has_value()) {
		int32 left = left_child(index);
		if (left < _nodes.size() && _nodes[left].has_value()) {
			index = left;
		}
		else {
			break;
		}
	}
	return index;
}




