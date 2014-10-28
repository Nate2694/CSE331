/**
 * A hash set.
 * Stub written by James Daly, 8 Oct 2014
 * Completed by [YOUR NAME]
 */
#pragma once

#ifndef HASH_SET_H
#define HASH_SET_H

#include <algorithm>
#include <functional>
#include <iostream>

template<class T>
class HashSet
{
public:
	HashSet(std::function<unsigned int(const T&)> hash, double loadFactor);
	HashSet(HashSet<T> &other);
	virtual ~HashSet();
	
	// Supplied Methods
	bool IsEmpty() const { return Size() == 0; }
	unsigned int Size() const { return size; }
	double GetLoadFactor() const { return loadFactor; }
	void DisplayItems() const { ForEach([](const T& item) { std::cout << item << std::endl; }); }
	double GetLoad() const { return ((double)Size()) / (double)NumBuckets(); }
	
	// Methods that you must complete
	unsigned int NumBuckets() const { /* TODO */ return 0; }
	bool Contains(const T& item) const;
	bool Insert(const T &item);
	bool Remove(const T &item);
	void Clear();
	void ForEach(std::function<void (const T&)> func) const;
	unsigned int MaxBucketSize() const;
	double PercentEmptyBuckets() const;
	
private:
	unsigned int size;
	double loadFactor;
	std::function<unsigned int (const T&)> hash;
	// You need some data source to store items
	
	
	// You can put any helper methods here
};

/**
 * Default constructor
 */
template<class T>
HashSet<T>::HashSet(std::function<unsigned int(const T&)> hash, double loadFactor):
	size(0),
	loadFactor(loadFactor),
	hash(hash)
{
	// Empty: You can put other initialization information here
}

/**
 * Copy Constructor
 * Uses uniform instantiation to initialize itself
 * and then copies all of the items from the other set
 */
template<class T>
HashSet<T>::HashSet(HashSet<T> &other) :
	HashSet(other.hash, other.loadFactor)
{
	auto insertItem = [=](const T& x){ this->Insert(x); };
	other.ForEach(insertItem);
}

/**
 * Destructor
 * Any cleanup you need to do can be done here
 */
template<class T>
HashSet<T>::~HashSet()
{
	// Empty: You can put any steps necessary for cleanup here
}

/**
 * Returns true iff the item is in the set
 */
template<class T>
bool HashSet<T>::Contains(const T &item) const
{
	// TODO
	return false;
}

/**
 * Inserts the item into the set.
 * Only one copy can exist in the set at a time.
 * Returns true iff the item was successfully added.
 */
template<class T>
bool HashSet<T>::Insert(const T &item)
{
	// TODO
	return false;
}

/**
 * Removes the item from the set.
 * Returns true iff the item was successfully removed.
 */
template<class T>
bool HashSet<T>::Remove(const T &item)
{
	// TODO
	return false;
}

/**
 * Removes all elements from the set.
 */
template<class T>
void HashSet<T>::Clear()
{
	// TODO
}

/**
 * Invokes the function once on each item in the set.
 * The exact order is undefined.
 */
template<class T>
void HashSet<T>::ForEach(std::function<void (const T&)> func) const
{
	// TODO
}

/**
 * Finds the maximum number of items in a bucket.
 */
template<class T>
unsigned int HashSet<T>::MaxBucketSize() const
{
	// TODO
	return 0;
}

/**
 * Finds which fraction of the buckets are empty
 * The result is returned as a percent
 */
template<class T>
double HashSet<T>::PercentEmptyBuckets() const
{
	// TODO
	return 100.0;
}

#endif