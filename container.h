#pragma once
//boost::array��һ���̶���С�����飬���������������͵�Ԫ�ء�
//boost::vector��һ���ɱ��С�����飬���������������͵�Ԫ�ء�
//boost::list��һ��˫���������������������͵�Ԫ�ء�
//boost::forward_list��һ�������������������������͵�Ԫ�ء�
//boost::deque��һ��˫�˶��У����������������͵�Ԫ�ء�
//boost::stack��һ������ȳ������ݽṹ�����������������͵�Ԫ�ء�
//boost::queue��һ���Ƚ��ȳ������ݽṹ�����������������͵�Ԫ�ء�
//boost::circular_buffer��һ��ѭ�������������������������͵�Ԫ�ء�
//boost::multi_array��һ����ά���飬���������������͵�Ԫ�ء�
//boost::unordered_map��һ����ϣ���������ɼ�ֵ�ԡ�
//boost::unordered_set��һ����ϣ�����������������͵�Ԫ�ء�
//boost::map��һ���������飬�������ɼ�ֵ�ԡ�
//boost::set��һ�����ϣ����������������͵�Ԫ�ء�
//boost::flat_hash_map��һ����ϣ���������ɼ�ֵ�ԡ�
//boost::flat_hash_set��һ����ϣ�����������������͵�Ԫ�ء�
#include <iostream>
#include <vector>
#include <boost/container/map.hpp>
#include <boost/container/vector.hpp>
class container
{
public:
	container() {
		createContain();
	}
	void createContain();

};

