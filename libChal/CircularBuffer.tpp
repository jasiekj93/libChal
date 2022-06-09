#pragma once

namespace Chal
{
	template<typename T>
		inline CircularBuffer<T>::CircularBuffer(size_t size)
			: _head(0)
            , _tail(0) 
            , _count(0)
            , Size(size)
            , _buffer(new T[size])
		{
		}

    template<typename T>
		inline CircularBuffer<T>::~CircularBuffer()
		{
            delete[] _buffer;
		}

	template<typename T>
		inline void CircularBuffer<T>::Put(const T &item)
		{
            _buffer[_head] = item;

            _head += 1;
            _head %= Size;

            if(_count < Size)
                _count++;
		}

    template<typename T>
		inline void CircularBuffer<T>::Put(const T *array, size_t size)
		{
           for(auto i = 0; i < size; i++)
                Put(array[i]);
		}

	template<typename T>
		inline T CircularBuffer<T>::Get()
		{
			if (_count == 0)
				return T();

            T result = _buffer[_tail];

            _tail += 1;
            _tail %= Size;
            _count--;

			return result;
		}
    
    template<typename T>
		inline void CircularBuffer<T>::Get(T *array, size_t size)
		{
            for(auto i = 0; i < size; i++)
                array[i] = Get();
		}

	template<typename T>
		inline void CircularBuffer<T>::Clear()
		{
            _head = _tail;
			_count = 0;
		}

	template<typename T>
		inline bool CircularBuffer<T>::IsFull() const
		{
			return (_count == Size);
		}

	template<typename T>
		inline bool CircularBuffer<T>::IsEmpty() const
		{
            return (_count == 0);
		}

	template<typename T>
		inline bool CircularBuffer<T>::IsNotEmpty() const
		{
			return (_count > 0);
		}

	template<typename T>
		inline size_t CircularBuffer<T>::Count() const
		{
            return _count;
		}

	template<typename T>
		inline T CircularBuffer<T>::At(size_t index) const
		{
			if (index >= _count)
				return T();

			index += _tail;
            index %= Size;

			return _buffer[index];
		}

	template<typename T>
		inline T CircularBuffer<T>::operator[](size_t index) const
		{
			return At(index);
		}
}