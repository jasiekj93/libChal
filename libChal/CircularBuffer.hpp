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
	template<typename T>
		class CircularBuffer
		{
		public:
			CircularBuffer(size_t);
			~CircularBuffer();

			void Put(const T &);
            void Put(const T *, size_t);
			T Get();
            void Get(T *, size_t);
			void Clear();

			bool IsEmpty() const;
			bool IsNotEmpty() const;
			bool IsFull() const;
			size_t Count() const;

			T operator[](size_t) const;
			T At(size_t) const;

            const size_t Size;

		private:
			T *_buffer;
            size_t _head;
            size_t _tail;
            size_t _count;
		};
}

#include <libChal/CircularBuffer.tpp>
