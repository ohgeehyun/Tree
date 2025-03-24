#pragma once

/*
	ArrayListTree
*/
class ArrayListTree
{
public:
	ArrayListTree();
	~ArrayListTree();

	bool resize(int32 size);
	bool reserve(int32 size);

	bool add_element(int32 num);
	bool delete_element(int32 num);

	int32_t get_height() const { return _height; }
	int32_t get_min_value() const { return _min_value; }
	int32_t get_max_value() const { return _max_value; }


private:
	std::vector<int32> _nodes;
	int32 _height = 0;
	int32 _min_value = INT_MAX;
	int32 _max_value = INT_MIN;

	int32 left_child(int32 index) { return 2 * index + 1; }
	int32 right_child(int32 index) { return 2 * index + 2; }
	int32 parent(int32 index) { return(index - 1) / 2; }


	bool add_recursive(int32_t index, int32_t num);  // ����� �߰� �Լ�
	bool delete_recursive(int32_t index, int32_t num);  // ����� ���� �Լ�
	int32_t find_min(int32_t index);  // �ּҰ��� ã�� �Լ�
	void update_height(int32_t index); // ���� ����
	void update_min_max(int32_t num); // �ּҰ��� �ִ밪 ����
	void update_min_max_after_delete();

	int32 find_min(int32 index);
	int32 find_max(int32 index);

};

