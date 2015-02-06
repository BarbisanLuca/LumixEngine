#include "unit_tests/suite/lumix_unit_tests.h"

#include "core/array.h"
#include "core/hash_map.h"

namespace
{
	void UT_insert(const char* params)
	{
		Lumix::DefaultAllocator allocator;
		Lumix::HashMap<int32_t, int32_t> hash_table(allocator);

		LUMIX_EXPECT_TRUE(hash_table.empty());

		size_t values[10] = {
			1, 2, 3, 4, 5, 6, 7, 8, 9, 10
		};

		for (size_t val : values)
		{
			hash_table.insert(val, val);
		}

		for (size_t val : values)
		{
			LUMIX_EXPECT_EQ(hash_table[val], val);
		}
	};

	void UT_array(const char* params)
	{
		Lumix::DefaultAllocator allocator;
		Lumix::HashMap<int32_t, Lumix::Array<int> > hash_table(allocator);

		LUMIX_EXPECT_TRUE(hash_table.empty());
	};

	void UT_clear(const char* params)
	{
		Lumix::DefaultAllocator allocator;
		Lumix::HashMap<int32_t, int32_t> hash_table(allocator);

		LUMIX_EXPECT_TRUE(hash_table.empty());

		const size_t COUNT = 20;

		for (size_t i = 0; i < COUNT; i++)
		{
			hash_table.insert(i, i);
		}

		for (size_t i = 0; i < COUNT; i++)
		{
			LUMIX_EXPECT_EQ(hash_table[i], i);
		}

		LUMIX_EXPECT_FALSE(hash_table.empty());

		hash_table.clear();

		LUMIX_EXPECT_TRUE(hash_table.empty());

		hash_table.rehash(8);

		for (size_t i = 0; i < COUNT; i++)
		{
			hash_table.insert(i, i);
		}
	};

	void UT_constIterator(const char* params)
	{
		typedef Lumix::HashMap<int32_t, int32_t> HashTableType;

		Lumix::DefaultAllocator allocator;
		HashTableType hash_table(allocator);

		LUMIX_EXPECT_TRUE(hash_table.empty());

		size_t values[10] = {
			1, 2, 3, 4, 5, 6, 7, 8, 9, 10
		};

		for (size_t val : values)
		{
			hash_table.insert(val, val);
		}

		for (size_t val : values)
		{
			LUMIX_EXPECT_EQ(hash_table[val], val);
		}

		const HashTableType& const_hash_table = hash_table;
		for (HashTableType::constIterator const_it = const_hash_table.begin(); const_it != const_hash_table.end(); ++const_it)
		{
			LUMIX_EXPECT_EQ(const_it.value(), values[const_it.key() - 1]);
		}
	}
}

REGISTER_TEST("unit_tests/core/hash_map/insert", UT_insert, "")
REGISTER_TEST("unit_tests/core/hash_map/array", UT_array, "")
REGISTER_TEST("unit_tests/core/hash_map/clear", UT_clear, "")
REGISTER_TEST("unit_tests/core/hash_map/constIterator", UT_constIterator, "")

