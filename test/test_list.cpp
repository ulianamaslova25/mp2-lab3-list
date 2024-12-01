#include "list.h"

#include <gtest.h>

TEST(TList, can_create_list)
{
	ASSERT_NO_THROW(TList<int> l());
}

TEST(TList, can_create_list_with_positive_length)
{
	ASSERT_NO_THROW(TList<int> l(5));
}

TEST(TList, cant_create_list_with_negative_length)
{
	ASSERT_ANY_THROW(TList<int> l(-5));
}

TEST(TList, can_create_copy_list)
{
	TList<int> list1(5);
	ASSERT_NO_THROW(TList<int> list2(list1));
}

TEST(TList, can_get_size)
{
	TList<int> l(5);
	EXPECT_EQ(5, l.size());
}

TEST(TList, can_get_empty)
{
	TList<int> l(0);
	EXPECT_EQ(1, l.empty());
}

TEST(TList, not_empty_after_insert) {
	TList<int> list;
	list.insert_front(1);
	EXPECT_FALSE(list.empty());
}

TEST(TList, can_move_list)
{
	TList<int> l(5), m;
	ASSERT_NO_THROW(m = std::move(l));
}

TEST(TList, can_move_list_by_constructor) {
	TList<int> list1(5);
	ASSERT_NO_THROW(TList<int> list2(std::move(list1)));
}

TEST(TList, can_set_and_get_by_add)
{
	TList<int> l1(3);
	int cnt = 0;
	for (TList<int>::iterator i = l1.begin(); i != l1.end(); ++i) {
		l1.at(i) = cnt++;
	}
	cnt = 0;
	for (TList<int>::iterator i = l1.begin(); i != l1.end(); ++i) {
		EXPECT_EQ(l1.at(i), cnt++);
	}
}

TEST(TList, can_set_and_get_by_oper)
{
	TList<int> l1(3);
	int cnt = 0;
	for (TList<int>::iterator i = l1.begin(); i != l1.end(); ++i) {
		l1[i] = cnt++;
	}
	cnt = 0;
	for (TList<int>::iterator i = l1.begin(); i != l1.end(); ++i) {
		EXPECT_EQ(l1[i], cnt++);
	}
}

TEST(TList, copied_list_has_its_own_memory)
{
	TList<int> l1(3);
	TList<int> l2(l1);
	EXPECT_NE(l1.begin(), l2.begin());
}

TEST(TList, can_assign_list_to_itself)
{
	TList<int> l1(3);
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	l1 = l1;
	EXPECT_EQ(l1.size(), 3);
	i = 0;
	for (TList<int>::iterator it1 = l1.begin(); it1 != l1.end(); ++it1) {
		EXPECT_EQ(l1.at(it1), i++);
	}
}

TEST(TList, can_assign_lists)
{
	TList<int> l1(3), l2(4);
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	l2 = l1;
	EXPECT_EQ(l2.size(), 3);
	i = 0;
	for (TList<int>::iterator it2 = l2.begin(); it2 != l2.end(); ++it2) {
		EXPECT_EQ(l2.at(it2), i++);
	}
}

TEST(TList, list_is_equal_to_copymoved_one)
{
	TList<int> l1(3);
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	TList<int> l2(std::move(l1));
	EXPECT_EQ(3, l2.size());
	i = 0;
	for (TList<int>::iterator it2 = l2.begin(); it2 != l2.end(); ++it2) {
		EXPECT_EQ(i++, l2.at(it2));
	}

}

TEST(TList, list_is_equal_to_moved_one)
{
	TList<int> l1(3), l2;
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	l2 = std::move(l1);
	EXPECT_EQ(3, l2.size());
	i = 0;
	for (TList<int>::iterator it2 = l2.begin(); it2 != l2.end(); ++it2) {
		EXPECT_EQ(i++, l2.at(it2));
	}

}

TEST(TList, moved_list_is_deleted)
{
	TList<int> l1(3), l2;
	int i = 0;
	for (TList<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
		l1.at(it) = i++;
	}
	l2 = std::move(l1);
	EXPECT_EQ(0, l1.size());
	EXPECT_EQ(l1.begin(), l1.end());

}

TEST(TList, can_insert_front_element) {
	TList<int> l;
	l.insert_front(3);
	EXPECT_EQ(l.size(), 1);
	EXPECT_EQ(l.at(0), 3);
}

TEST(TList, can_insert_multiple_front_elements) {
	TList<int> l;
	l.insert_front(3);
	l.insert_front(2);
	l.insert_front(1);
	EXPECT_EQ(l.size(), 3);
	EXPECT_EQ(l.at(0), 1);
	EXPECT_EQ(l.at(1), 2);
	EXPECT_EQ(l.at(2), 3);
	int i = 1;
	for (auto it = l.begin(); it != l.end(); ++it, ++i) {
		EXPECT_EQ(*it, i);
	}

}

TEST(TList, can_insert_after_element) {
	TList<int> l;
	l.insert_front(1);
	l.insert_after(2, l.begin().cr);
	EXPECT_EQ(l.size(), 2);
	EXPECT_EQ(l.at(0), 1);
	EXPECT_EQ(l.at(1), 2);
}

TEST(TList, can_insert_after_multiple_elements) {
	TList<int> l;
	l.insert_front(1);
	auto node = l.begin().cr;
	l.insert_after(2, node);
	node = node->next;
	l.insert_after(3, node);
	EXPECT_EQ(l.size(), 3);
	int i = 1;
	for (auto it = l.begin(); it != l.end(); ++it, ++i) {
		EXPECT_EQ(*it, i);
	}
}



TEST(TList, can_erase_front_element) {
	TList<int> l;
	l.insert_front(2);
	l.insert_front(1);
	l.erase_front();
	EXPECT_EQ(l.size(), 1);
	EXPECT_EQ(l.at(0), 2);

}


TEST(TList, can_erase_after_element) {
	TList<int> l;
	l.insert_front(3);
	l.insert_front(2);
	l.insert_front(1);
	l.erase_after(l.begin().cr);
	EXPECT_EQ(l.size(), 2);
	EXPECT_EQ(l.at(0), 1);
	EXPECT_EQ(l.at(1), 3);
}

TEST(TList, can_clear_list) {
	TList<int> l;
	l.insert_front(1);
	l.insert_front(2);
	l.clear();
	EXPECT_EQ(l.size(), 0);
	EXPECT_TRUE(l.empty());
}


TEST(TList, throw_erase_after_if_next_is_nullptr)
{
	TList<int> l;
	l.insert_front(1);
	auto node = l.begin().cr;
	ASSERT_ANY_THROW(l.erase_after(node));
}


TEST(TList, throw_at_incorrect_index) {
	TList<int> l(2);
	ASSERT_ANY_THROW(l.at(2));
	ASSERT_ANY_THROW(l.at(-1));
}

TEST(TList, throw_dereference_end_iterator) {
	TList<int> l;
	auto it = l.end();
	ASSERT_ANY_THROW(*it);
}

//TEST(FindKthFromEndTest, work) {
//	TList<int> l(6);
//	for (int i = 0; i < 6; i++) {
//		l[i] = i;
//	}
//	int i = 0;
//	for (auto it = l.begin(); it != l.end(); ++it, ++i) {
//		EXPECT_EQ(*it, i);
//	}
//}