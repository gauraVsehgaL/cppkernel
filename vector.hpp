#include "new.hpp"

namespace ktd
{
	template<typename T, POOL_TYPE PoolType, unsigned long Tag>
	class vector
	{
	public:
		
		vector() :ptr(nullptr), Capacity(0), NumberOfElements(0) {}

		vector(size_t InitialNumberOfElements)
		{
			Capacity = InitialNumberOfElements;
			NumberOfElements = InitialNumberOfElements;

			ptr = new(PoolType, Tag) T[Capacity];
		}

		vector(size_t InitialNumberOfElements, T val)
		{
			Capacity = InitialNumberOfElements;
			NumberOfElements = InitialNumberOfElements;

			ptr = new(PoolType, Tag) T[Capacity];
			for (auto i = 0UL; i < Capacity; i++)
			{
				ptr[i] = val;
			}
		}

		vector(const vector<T, PoolType, Tag> &other) :Capacity(other.Capacity), NumberOfElements(other.NumberOfElements)
		{
			this->ptr = new(PoolType, Tag) T[Capacity];
			for (auto i = 0UL; i < NumberOfElements; i++)
				ptr[i] = other.ptr[i];
		}

		vector(vector<T, PoolType, Tag> &&other) :Capacity(other.Capacity), NumberOfElements(other.NumberOfElements)
		{
			this->ptr = other.ptr;
			other.ptr = nullptr;
		}

		vector<T, PoolType, Tag>& operator=(vector<T, PoolType, Tag> &&other)
		{
			if (*this != other)
			{
				this->Capacity = other.Capacity;
				this->NumberOfElements = other.NumberOfElements;
				this->ptr = other.ptr;
				other->ptr = nullptr;
			}

			return *this;
		}

		vector<T, PoolType, Tag>& operator=(const vector<T, PoolType, Tag> &other)
		{
			if (*this != other)
			{
				if (this->Capacity < other.Capacity)
				{
					this->Capacity *= 2;
					Reallocate();
				}

				this->NumberOfElements = other.NumberOfElements;

				for (auto i = 0UL; i < NumberOfElements; i++)
					ptr[i] = other.ptr[i];
			}

			return *this;
		}


		~vector()
		{
			if (ptr)
				delete[] ptr;
		}

		void Reallocate()
		{
			auto origptr = ptr;
			ptr = new(PoolType, Tag) T[Capacity];
			memcpy(ptr, origptr, NumberOfElements * sizeof(T));
			if (origptr)
				delete[] origptr;
		}

		void push_back(const T &val)
		{
			if (NumberOfElements + 1 > Capacity)
			{
				// re allocate.
				if (Capacity == 0)
					Capacity = 1;

				Capacity *= 2;
				Reallocate();
			}
			
			ptr[NumberOfElements] = val;
			NumberOfElements++;
		}

		void push_back(T &&val)
		{	
			if (NumberOfElements + 1 > Capacity)
			{
				// re allocate.
				if (Capacity == 0)
					Capacity = 1;

				Capacity *= 2;
				Reallocate();
			}

			new (ptr + NumberOfElements) T(move(val));
			NumberOfElements++;
		}

		template<class ...Args>
		T& emplace_back(Args&&... args)
		{
			if (NumberOfElements + 1 > Capacity)
			{
				// re allocate.
				if (Capacity == 0)
					Capacity = 1;

				Capacity *= 2;
				Reallocate();
			}

			new (ptr + NumberOfElements) T(forward<Args>(args)...);

			return ptr[NumberOfElements++];
		}

		size_t size()
		{
			return this->NumberOfElements;
		}

		T& operator=(size_t index)
		{
			return ptr[index];
		}

	private:
		
		T *ptr;
		size_t Capacity;
		size_t NumberOfElements;
	};
}