#pragma once
#include "stdafx.h"
//#include <hash_map>
#include <unordered_map>
#include <map>
//#include <hash_set>
#include <unordered_set>
#include <set>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <array>
#include <algorithm>
#include <functional>

typedef	std::function<void(void *)>	EachFunction;
typedef	std::function<void(void *, void *)>	PairFunction;

#if 0	//하이라이트 때문에 /* */ 주석이 아닌 #if 0 ~ #endif로 처리
template <typename KEY, typename VALUE>
class HashTable
{
	typedef std::hash_map<KEY, VALUE>			MAP;
	typedef	typename MAP::iterator				ITER;
	typedef	typename MAP::const_iterator		CITER;

	MAP map_;
public:
	MAP &	map() { return map_; }

	void	clear() { map_.clear(); }
	size_t	size() { return map_.size(); }
	bool	empty() { return map_.empty(); }
	ITER	begin() { return map_.begin(); }
	ITER	end() { return map_.end(); }

	VALUE		front()
	{
		if (this->empty()) {
			return (VALUE) nullptr;
		}
		return this->begin()->second();
	}

	VALUE		back()
	{
		if (this->empty()) {
			return (VALUE) nullptr;
		}
		auto iter = this->end();
		--iter;
		return iter->second;
	}

	void		push(KEY key, VALUE value)
	{
		std::pair<KEY, VALUE> node(key, value);
		map_.insert(node);
	}

	VALUE		pop(KEY key)
	{
		auto iter = map_.find(key);
		if (iter == map_.end()) {
			return (VALUE) nullptr;
		}
		VALUE value = iter->second;
		map_.erase(iter);
		return value;
	}

	VALUE		get(KEY key)
	{
		if (this->empty()) {
			return (VALUE) nullptr;
		}
		auto iter = map_.find(key);
		return (iter == this->end()) ? (VALUE) nullptr : iter->second;
	}

	VALUE		next(KEY key, KEY &key2)
	{
		if (this->empty()) {
			return (VALUE) nullptr;
		}
		auto iter = map_.upper_bound(key);
		if (iter == this->end()) {
			return (VALUE) nullptr;
		}
		key2 = iter->first;
		return iter->second;
	}

	void		clearObjects(EachFunction func)
	{
		for (auto iter : map_) {
			if (func) {
				func(iter.second);
				continue;
			}
			SAFE_DELETE(iter.second);
		}
		this->clear();
	}

	void		clearObjects()
	{
		for (auto iter : map_) {
			SAFE_DELETE(iter.second);
		}
		this->clear();
	}

	void		doEach(EachFunction func)
	{
		if (!func) {
			return;
		}
		for (auto iter : map_) {
			func(iter.second);
		}
	}

	void		doPair(PairFunction func)
	{
		if (!func) {
			return;
		}
		for (auto iter : map_) {
			func(iter.second);
		}
	}
};
#endif
