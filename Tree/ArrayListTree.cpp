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
			_nodes.shrink_to_fit();  // ���ʿ��� �޸� �Ҵ� ����
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
		// �� �߰� ������ ���� �ּ� �ִ밪 ����
		update_min_max(num);

		// �� ����� �θ���� ��Ʈ���� ���̸� ����
		int32 index = _nodes.size() - 1;  // ���� �߰��� ����� �ε���
		while (index >= 0) {
			update_height(index);  // ���� ����� ���̸� ����
			index = parent(index);  // �θ� ���� �̵�
		}
	}

	return result;
}

bool ArrayListTree::delete_element(int32 num)
{
	// Ʈ���� ��Ʈ���� �����Ͽ� ������ �� ã��
	return delete_recursive(0, num);
}

bool ArrayListTree::add_recursive(int32_t index, int32_t num)
{
	if (index >= _nodes.size()) {
		_nodes.push_back(num);  // ���ο� ��带 �߰�
		return true;
	}

	if (num < _nodes[index]) {
		int32_t leftIndex = left_child(index);
		if (leftIndex >= _nodes.size()) {
			_nodes.push_back(num);
		}
		else {
			return add_recursive(leftIndex, num);  // ���� ����Ʈ���� ��� ȣ��
		}
	}
	else {
		int32_t rightIndex = right_child(index);
		if (rightIndex >= _nodes.size()) {
			_nodes.push_back(num);
		}
		else {
			return add_recursive(rightIndex, num);  // ������ ����Ʈ���� ��� ȣ��
		}
	}

	return true;
}

bool ArrayListTree::delete_recursive(int32_t index, int32_t num)
{
	if (index >= _nodes.size()) return false;  // ������ ����� ����

	if (_nodes[index] == num) 
	{
		//������ ���� ã�� ��� ������ ����ǻ��¿� ���� case�� ����.

		//�ڽ��̾��� �׳� �����ص� ok
		if (left_child(index) >= _nodes.size() && right_child(index) >= _nodes.size()) {
			_nodes.erase(_nodes.begin() + index);
			return true;
		}

		// �ڽ��� �ϳ��� �ִ� ��� ������ �ڽ� 
		if (left_child(index) >= _nodes.size()) {
			_nodes[index] = _nodes[right_child(index)];
			_nodes.erase(_nodes.begin() + right_child(index));
			return true;
		}
		// �ڽ��� �ϳ��� �ִ� ��� ���� �ڽ�
		if (right_child(index) >= _nodes.size()) {
			_nodes[index] = _nodes[left_child(index)];
			_nodes.erase(_nodes.begin() + left_child(index));
			return true;
		}

		// �ڽ��� �� ���� ���: ������ ����Ʈ������ �ּҰ��� ã�Ƽ� ��ü
		int32_t minIndex = find_min(right_child(index));
		_nodes[index] = _nodes[minIndex];
		delete_recursive(minIndex, _nodes[minIndex]);
		return true;

	}

	if (num < _nodes[index]) {
		return delete_recursive(left_child(index), num);  // ���� ����Ʈ���� ��� ȣ��
	}
	else {
		return delete_recursive(right_child(index), num);  // ������ ����Ʈ���� ��� ȣ��
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

	// ���� ����� ���̴� ���ʰ� ������ �ڽ��� ���� �� ū �� + 1
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




