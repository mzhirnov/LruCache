#pragma once

#include <list>
#include <unordered_map>

template <typename TKey, typename TValue>
class LruCache {
public:
	explicit LruCache(size_t maxSize)
		: _maxSize(maxSize)
	{
		if (_maxSize < 1) {
			throw std::runtime_error("invalid argument");
		}
	}
	
	void Erase(const TKey& key) {
		if (auto it = _index.find(key); it != _index.end()) {
			_data.erase(it->second);
			_index.erase(it);
		}
	}
	
	const TValue& Get(const TKey& key) {
		if (auto it = _index.find(key); it != _index.end()) {
			// Move to top
			_data.splice(_data.begin(), _data, it->second);
			 return _data.front().second;
		}
		
		throw std::runtime_error("key not found");
	}
	
	void Set(const TKey& key, const TValue& value) {
		if (auto it = _index.find(key); it != _index.end()) {
			// Assign new value
			auto& [k, v] = *it->second;
			v = value;
			// Move to top
			_data.splice(_data.begin(), _data, it->second);
		}
		else {
			if (_index.size() == _maxSize) {
				// Remove old one
				_index.erase(_data.back().first);
				_data.pop_back();
			}
			_data.emplace_front(key, value);
			_index.emplace(key, _data.begin());
		}
	}
	
	bool Exists(const TKey& key) {
		return _index.contains(key);
	}

private:
	using Data = std::pair<TKey, TValue>;
	using DataQueue = std::list<Data>;
	
	DataQueue _data;
	
	std::unordered_map<TKey, typename DataQueue::iterator> _index;
	
	const size_t _maxSize = 1;
};
