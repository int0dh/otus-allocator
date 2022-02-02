#pragma once

#include <vector>

template <typename T, typename Storage>
struct my_iterator {
	Storage &vec_;
	size_t offset;

	my_iterator(Storage & vec) : vec_{vec}, offset{0} {}
	my_iterator(Storage & vec, size_t size) : vec_{vec}, offset{size} {}

	bool operator != (const my_iterator<T, Storage> &other) const {
		return !(*this == other);
	}

	bool operator == (const my_iterator<T, Storage> &other) const {
		return offset == other.offset;
	}

	my_iterator& operator ++() {
		++ offset;
		return *this;
	}

	T& operator * () const {
		return vec_.at(offset);
	}
};

template <typename T, typename A>
struct my_container {
	using Storage = std::vector<T, A>;

	Storage vec;

	my_container(auto & data) {
		vec.reserve(data.size());
		for (auto &k : data) {
			vec.push_back(k);
		}
	}
	void push_back(T item) {
		vec.push_back(item);
	}
	my_iterator<T, Storage> begin() {
		return my_iterator<T, Storage>(vec);
	}
	my_iterator<T, Storage> end() {
		return my_iterator<T, Storage>(vec, vec.size());
	}
};
