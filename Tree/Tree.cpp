﻿#pragma once
#include "pch.h"
#include "ArrayListTree.h"
#include "LinkedListTree.h"

/*
배열 기반 리스트와 링크드 리스트 기반 트리

-배열 기반리스트-
-장점 : 큰 차이로는 배열 기반 리스트는 메모리할당이 연속적으로 되어있기때문에 메모리 캐시 효율성이 좋음-> 캐시 메모리에 근처에있는데이터가 저장이 되니 연속적으로 읽을 때 빠를 수 밖에 없음. 임의 접근 가능
-단점 : 배열의 크기를 초과하면 재할당 필요. 삽입 삭제시 중간에서 부터 하는경우 시간이 걸림 특히 배열 크기 초과시 리사이징 필요. 배열의 시작이나 끝부분은 O(1)삽입 삭제이 가능하지만 중간일 경우 O(n)


-링크드 링스트 기반-
-장점 : 리스트의 앞 뒤 중간 어느부분이든 원소를 삽입 삭제할떄 O(1)이 걸림.
-단점 : 메모리 오버헤드 가 일어남 연속적으로 메모리에 있지않기 떄문에 다음 영역을 가리키는 포인터가 추가 필요. 캐시효율성도 배열 기반에 비해 좋지않음. 삽입삭제는 O(1)이지만 탐색은 O(n) 임의 접근 불가 

*/ 

int main()
{
    
    ArrayListTree* arraytree = new ArrayListTree();

    arraytree->add_element(5);
    arraytree->add_element(10);
    arraytree->add_element(20);
    arraytree->add_element(9);
    arraytree->add_element(13);
    arraytree->add_element(3);

    for (int32 i = 0; i < arraytree->GetTree().size(); i++)
    {
        if (arraytree->GetTree()[i].has_value())
            cout << arraytree->GetTree()[i].value() << endl;
        else
            cout << "empty" <<endl;
    }

    cout << arraytree->get_height() << endl;
    cout << arraytree->get_min_value() << endl;
    cout << arraytree->get_max_value() << endl;

    cout << "-------------------------------" << endl;

    arraytree->delete_element(9);
    arraytree->delete_element(100);

    for (int32 i = 0; i < arraytree->GetTree().size(); i++)
    {
        if (arraytree->GetTree()[i].has_value())
            cout << arraytree->GetTree()[i].value() << endl;
        else
            cout << "empty" << endl;
    }
    cout << arraytree->get_height() << endl;
    cout << arraytree->get_min_value() << endl;
    cout << arraytree->get_max_value() << endl;

    system("pause");
}

