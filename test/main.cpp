#include <gtest/gtest.h>

#include <LruCache.h>

TEST(LruCache, InvalidSize) {
	EXPECT_THROW((LruCache<int, int>{0}), std::runtime_error);
}

TEST(LruCache, Exists) {
	LruCache<int, int> cache(2);
	
	EXPECT_FALSE(cache.Exists(0));
	
	cache.Set(0, 42);
	EXPECT_TRUE(cache.Exists(0));
}

TEST(LruCache, SetOne) {
	LruCache<int, int> cache(2);
	
	cache.Set(0, 42);
	EXPECT_TRUE(cache.Exists(0));
	EXPECT_FALSE(cache.Exists(1));
}

TEST(LruCache, SetTwo) {
	LruCache<int, int> cache(2);
	
	cache.Set(0, 42);
	cache.Set(1, 42);
	EXPECT_TRUE(cache.Exists(0));
	EXPECT_TRUE(cache.Exists(1));
}

TEST(LruCache, SetThree) {
	LruCache<int, int> cache(2);
	
	cache.Set(0, 42);
	cache.Set(1, 42);
	cache.Set(2, 42);
	EXPECT_FALSE(cache.Exists(0));
	EXPECT_TRUE(cache.Exists(1));
	EXPECT_TRUE(cache.Exists(2));
}

TEST(LruCache, SetExisting) {
	LruCache<int, int> cache(2);
	
	cache.Set(0, 42);
	cache.Set(1, 42);
	cache.Set(2, 42);
	cache.Set(0, 42);
	EXPECT_TRUE(cache.Exists(0));
	EXPECT_FALSE(cache.Exists(1));
	EXPECT_TRUE(cache.Exists(2));
}

TEST(LruCache, Get) {
	LruCache<int, int> cache(2);
	
	cache.Set(0, 42);
	cache.Set(1, 42);
	
	EXPECT_EQ(cache.Get(0), 42);
	
	cache.Set(2, 42);
	
	EXPECT_EQ(cache.Get(0), 42);
	EXPECT_THROW(cache.Get(1), std::runtime_error);
}

TEST(LruCache, Erase) {
	LruCache<int, int> cache(2);
	
	cache.Set(0, 42);
	cache.Set(1, 42);
	EXPECT_TRUE(cache.Exists(0));
	EXPECT_TRUE(cache.Exists(1));
	
	cache.Erase(1);
	EXPECT_FALSE(cache.Exists(1));
	
	cache.Erase(0);
	EXPECT_FALSE(cache.Exists(0));
}
