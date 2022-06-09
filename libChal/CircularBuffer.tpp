#pragma once

namespace Chal
{
	template<typename T, size_t SIZE>
		inline CircularBuffer<T, SIZE>::CircularBuffer()
			: _head(0)
            , _tail(0) 
            , _isFull(false)
		{
		}

	template<typename T, size_t SIZE>
		inline bool CircularBuffer<T, SIZE>::Put(const T &item)
		{
			if (_isFull)
				return false;

            _buffer[_head] = item;

            _head += 1;
            _head %= SIZE;

            if(_head == _tail)
                _isFull = true;

			return true;
		}

	template<typename T, size_t SIZE>
		inline T CircularBuffer<T, SIZE>::Get()
		{
			if (IsEmpty())
				return T();

            T result = _buffer[_tail];

            _tail += 1;
            _tail %= SIZE;

            if(_isFull)
                _isFull = false;

			return result;
		}

	template<typename T, size_t SIZE>
		inline void CircularBuffer<T, SIZE>::Clear()
		{
            _head = _tail;
			_isFull = false;
		}

	template<typename T, size_t SIZE>
		inline bool CircularBuffer<T, SIZE>::IsFull() const
		{
			return _isFull;
		}

	template<typename T, size_t SIZE>
		inline bool CircularBuffer<T, SIZE>::IsEmpty() const
		{
			if (_isFull)
				return false;
	
			if (_head != _tail)
				return false;

			return true;
		}

	template<typename T, size_t SIZE>
		inline bool CircularBuffer<T, SIZE>::IsNotEmpty() const
		{
			return (IsEmpty() == false);
		}

	template<typename T, size_t SIZE>
		inline size_t CircularBuffer<T, SIZE>::Count() const
		{
			if (_isFull)
				return SIZE;

            if(_head >= _tail)
                return _head - _tail;
            else
                return SIZE + _head - _tail;
		}

	template<typename T, size_t SIZE>
		inline size_t CircularBuffer<T, SIZE>::Size() const
		{
			return SIZE;
		}

	template<typename T, size_t SIZE>
		inline T CircularBuffer<T, SIZE>::At(size_t index) const
		{
			if (index >= Count())
				return T();

			index += _tail;
            index %= SIZE;

			return _buffer[index];
		}

	template<typename T, size_t SIZE>
		inline T CircularBuffer<T, SIZE>::operator[](size_t index) const
		{
			return At(index);
		}
}