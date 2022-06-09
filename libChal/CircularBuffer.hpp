#pragma once

/**
 * @file CircularBuffer.hpp
 * @author Adrian Szczepanski
 * @date 02-11-2021
 * @brief 
 * @details
 */
#include <stddef.h>

namespace Chal
{
	template<typename T, size_t SIZE>
		class CircularBuffer
		{
		public:
			CircularBuffer();

			bool Put(const T &);
			T Get();
			void Clear();

			bool IsFull() const;
			bool IsEmpty() const;
			bool IsNotEmpty() const;
			size_t Count() const;
			size_t Size() const;

			T operator[](size_t) const;
			T At(size_t i) const;
			
		private:
			T _buffer[SIZE];
            size_t _head;
            size_t _tail;
            bool _isFull;
		};
}

#include <libChal/CircularBuffer.tpp>
