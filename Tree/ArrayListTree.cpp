#include "pch.h"
#include "ArrayListTree.h"

ArrayListTree::ArrayListTree() 
{
}

ArrayListTree::ArrayListTree(int32 size) 
{
	_nodes.resize(size);
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
		return true;
	}

	return add_recursive(0, num);
}

bool ArrayListTree::delete_element(int32 num)
{
	for (int32 i = 0; i < _nodes.size(); i++)
	{
		if (_nodes[i] == num)
		{
			_nodes[i] = _nodes.back();
			_nodes.pop_back();
			return true;
		}
	}
	return false;
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

		if (left_child(index) >= _nodes.size() && right_child(index) >= _nodes.size()) {
			_nodes.erase(_nodes.begin() + index);
			return true;
		}

		// �ڽ��� �ϳ��� �ִ� ���
		if (left_child(index) >= _nodes.size()) {
			_nodes[index] = _nodes[right_child(index)];
			_nodes.erase(_nodes.begin() + right_child(index));
			return true;
		}

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




