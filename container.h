#pragma once
//boost::array：一个固定大小的数组，可以容纳任意类型的元素。
//boost::vector：一个可变大小的数组，可以容纳任意类型的元素。
//boost::list：一个双向链表，可以容纳任意类型的元素。
//boost::forward_list：一个单向链表，可以容纳任意类型的元素。
//boost::deque：一个双端队列，可以容纳任意类型的元素。
//boost::stack：一个后进先出的数据结构，可以容纳任意类型的元素。
//boost::queue：一个先进先出的数据结构，可以容纳任意类型的元素。
//boost::circular_buffer：一个循环缓冲区，可以容纳任意类型的元素。
//boost::multi_array：一个多维数组，可以容纳任意类型的元素。
//boost::unordered_map：一个哈希表，可以容纳键值对。
//boost::unordered_set：一个哈希表，可以容纳任意类型的元素。
//boost::map：一个关联数组，可以容纳键值对。
//boost::set：一个集合，可以容纳任意类型的元素。
//boost::flat_hash_map：一个哈希表，可以容纳键值对。
//boost::flat_hash_set：一个哈希表，可以容纳任意类型的元素。
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

