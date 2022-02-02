#pragma once

#include <memory>
#include <functional>
#include <list>

template <typename T, int N = 10>
class my_allocator {

private:
	const size_t arena_size_default = N * sizeof(T) * 1024;
	size_t arena_size;
	// hate this shit
	std::unique_ptr<T, std::function<void(T*)>> arena;
	// OK to keep raw pointers here, they do not own, just point to chunks to be allocated.
	std::list<T*> chunks;
public:
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T value_type;

	template<typename U>
	struct rebind
	{
		typedef my_allocator<U> other;
	};
	my_allocator(my_allocator &other) = delete;
	my_allocator operator = (my_allocator &other) = delete;

	my_allocator() : arena_size(arena_size_default),
		arena(static_cast<T*>(::malloc(arena_size)),
			[this] ([[maybe_unused]] T *d) {
				 ::free(arena.get());
			})
	 {
		for (size_t i = 0; i < arena_size / (sizeof(T) * N); i += N) {
			chunks.push_back(arena.get() + i);
		}
	}

	value_type * allocate(size_type size) {

		if (size > N) {
			std::cout << "trying to allocate " << size  << " elements " << std::endl;
			throw std::bad_alloc();
		}
		if (chunks.empty())
			throw std::bad_alloc();

		auto result = chunks.front();
		chunks.pop_front();

		return static_cast<value_type *>(result);
	}

	void deallocate(value_type *v, size_type size) {

		if (size > N)
			throw std::logic_error("unexpected size");

		chunks.push_back(v);
	}
};
