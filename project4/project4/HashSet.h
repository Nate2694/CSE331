/**
 * A hash set.
 * Stub written by James Daly, 8 Oct 2014
 * Completed by [Nathan Seifert]
 */
#pragma once

#ifndef HASH_SET_H
#define HASH_SET_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;

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
	unsigned int NumBuckets() const {return numBuckets;}
	bool Contains(const T& item) const;
	bool Insert(const T &item);
    bool Insert2(const T &item, int b);
	bool Remove(const T &item);
	void Clear();
	void ForEach(std::function<void (const T&)> func) const;
	unsigned int MaxBucketSize() const;
	double PercentEmptyBuckets() const;
	void Rehash(int x);
    
private:
	unsigned int size;// total elements
    int numBuckets;// total buckets
    int lF; // integer form of loadFactor
	double loadFactor;
	std::function<unsigned int (const T&)> hash;
	// You need some data source to store items
    vector<vector<T>> bucketList;
	
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
    lF = (int) (loadFactor + .5);
    bucketList.resize(10);
    numBuckets = 10;
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
    
    int f = hash(item);
    for(auto t : bucketList[f]){
        if(t == item){return true;}
    }
    //if we couldn't find it first try, might as well be meticulous about it
    for(int i = 0; i < numBuckets; i++){
        for(auto t : bucketList[i]){
            if(t == item){return true;}
        }
    }
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
    if(Contains(item)){return false;}// it's already in there silly

    int b = hash(item);
    
    int i = b;
    
    while(i < numBuckets){
        if(Insert2(item, i)){return true;}
        i++;
    }
    i = 0;
    while(i < b){
        if(Insert2(item, i)){return true;}
    }// if we have gotten to this point and still haven't inserted, better rehash the table.
    
    Rehash(numBuckets*2);
    return Insert(item);// try again

}

template<class T>
bool HashSet<T>::Insert2(const T &item, int i){
    
    if(bucketList[i].size() < lF){
        bucketList[i].push_back(item); return true;
    }
    else{ return false;}
}

/**
 * Removes the item from the set.
 * Returns true iff the item was successfully removed.
 */
template<class T>
bool HashSet<T>::Remove(const T &item)
{
    if(Contains(item)){
        int f = hash(item);
        for(int k = 0; k < bucketList[f].size(); k++){
            if(bucketList[f][k] == item){bucketList[f].erase(bucketList.begin()+ k); return true;}
        }
        // if we can't find it first swoop then let's try em all
        for(int i = 0; i < numBuckets; i++){
            for(int j = 0; j < bucketList[i].size(); j++){
                if(bucketList[i][j] == item){bucketList[i].erase(bucketList.begin()+ j); return true;}
            }
        }
    }
    else{ return false; }
}

/**
 * Removes all elements from the set.
 */
template<class T>
void HashSet<T>::Clear()
{
    for(int i = 0; i < numBuckets; i++){
        bucketList[i].clear();
    }
}

/**
 * Invokes the function once on each item in the set.
 * The exact order is undefined.
 */
template<class T>
void HashSet<T>::ForEach(std::function<void (const T&)> func) const
{
    for(int i = 0; i < numBuckets; i++){
        for(int j = 0; j < numBuckets; j++){
            func(bucketList[i][j]);
        }
    }
}

/**
 * Finds the maximum number of items in a bucket.
 */
template<class T>
unsigned int HashSet<T>::MaxBucketSize() const
{
    int maxSize = 0;
    
    for(int i = 0; i < numBuckets; i++){
        if(bucketList[i].size() > maxSize){ maxSize = bucketList[i].size();}
    }
	return maxSize;
}

/**
 * Finds which fraction of the buckets are empty
 * The result is returned as a percent
 */
template<class T>
double HashSet<T>::PercentEmptyBuckets() const
{
    int empBuks = 0;
    
    for(int i = 0; i < numBuckets; i++){
        if(bucketList[i].size() == 0){empBuks++;}
    }
    return ( (double) empBuks / (double) numBuckets ) * 100.0  ;
}

template<class T>
void HashSet<T>::Rehash(int x){
    cout<< "Rehashing..."<<endl;
    cout<< "New Size: "<< x <<endl;
    
    vector<T> temp;
    
    for(int i = 0; i < numBuckets; i++){
        for(auto t: bucketList[i]){
            temp.push_back(t);
        }
    }// got all the values in a temp vector
    numBuckets = x;
    Clear();
    bucketList.resize(x);
    for(int i = 0; i < temp.size(); i++){
        Insert(temp[i]);
    }
    temp.clear();
    return;
    
}

#endif