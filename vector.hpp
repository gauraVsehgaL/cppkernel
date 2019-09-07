#include "new.hpp"

namespace ktd
{
	template<typename T, POOL_TYPE PoolType, unsigned long Tag>
	class vector
	{
	public:
		
		vector() :ptr(nullptr), Capacity(0), NumberOfElements(0) {}

		vector(size_t InitialNumberOfElements):ptr(nullptr), Capacity(InitialNumberOfElements), NumberOfElements(0)
		{
			reserve(Capacity);

			NumberOfElements = InitialNumberOfElements;
			for (auto i = 0UL; i < NumberOfElements; i++)
			{
				new (ptr + i) T();
			}
		}

		vector(size_t InitialNumberOfElements, T val):ptr(nullptr), Capacity(InitialNumberOfElements), NumberOfElements(0)
		{
			Capacity = InitialNumberOfElements;
			reserve(Capacity);
			NumberOfElements = InitialNumberOfElements;
			for (auto i = 0UL; i < NumberOfElements; i++)
			{
				new (ptr + i) T(val);
			}
		}

		vector(const vector<T, PoolType, Tag> &other) :ptr(nullptr), Capacity(other.Capacity), NumberOfElements(0)
		{
			if (Capacity > 0)
			{
				reserve(Capacity);
			}
					
			for (auto i = 0UL; i < NumberOfElements; i++)
			{
				new (ptr +i) T(other.ptr[i]);
			}
		}

		vector(vector<T, PoolType, Tag> &&other) :Capacity(other.Capacity), NumberOfElements(other.NumberOfElements)
		{
			this->ptr = other.ptr;
			other.ptr = nullptr;
		}

		vector<T, PoolType, Tag>& operator=(vector<T, PoolType, Tag> &&other)
		{
			if (this != &other)
			{
				this->Capacity = other.Capacity;
				this->NumberOfElements = other.NumberOfElements;
				this->ptr = other.ptr;
				other.ptr = nullptr;
			}

			return *this;
		}

		vector<T, PoolType, Tag>& operator=(const vector<T, PoolType, Tag> &other)
		{
			if (this != &other)
			{
				if (this->Capacity < other.Capacity)
				{
					this->Capacity = other.Capacity;
					auto OrigPtr = this->ptr;
					this->ptr = allocate(Capacity);
					destroy(OrigPtr, this->NumberOfElements);
					deallocate(OrigPtr);
				}

				this->NumberOfElements = other.NumberOfElements;

				for (auto i = 0UL; i < NumberOfElements; i++)
					ptr[i] = other.ptr[i];
			}

			return *this;
		}


		~vector()
		{
			// explicitly call destructors if required.
			if (!ptr)
				return;

			for (auto i = 0UL; i < NumberOfElements; i++)
			{
				ptr[i].~T();
			}

			deallocate(ptr);
		}

		void reserve(size_t NewCapacity)
		{
			if (NewCapacity <= Capacity)
				return;

			auto origptr = ptr;
			ptr = allocate(NewCapacity);
		
			for (auto i = 0UL; i < NumberOfElements; i++)
			{
				new (ptr + i) T(origptr[i]);
			}

			Capacity = NewCapacity;

			if (origptr)
			{
				for (auto i = 0UL; i < NumberOfElements; i++)
				{
					origptr[i].~T();
				}

				deallocate(origptr);
			}
		}

		void push_back(const T &val)
		{
			auto NewCapacity = Capacity;
			if (NumberOfElements + 1 > Capacity)
			{
				// re allocate.
				if (Capacity == 0)
					NewCapacity = 1;
				
				NewCapacity *= 2;

				reserve(NewCapacity);
			}
			
			new (ptr + NumberOfElements) T(val);
			NumberOfElements++;
		}

		void push_back(T &&val)
		{	
			auto NewCapacity = Capacity;
			if (NumberOfElements + 1 > Capacity)
			{
				// re allocate.
				if (Capacity == 0)
					NewCapacity = 1;

				NewCapacity *= 2;

				reserve(NewCapacity);
			}

			new (ptr + NumberOfElements) T(move(val));
			NumberOfElements++;
		}

		template<class ...Args>
		T& emplace_back(Args&&... args)
		{
			auto NewCapacity = Capacity;
			if (NumberOfElements + 1 > Capacity)
			{
				// re allocate.
				if (Capacity == 0)
					NewCapacity = 1;

				NewCapacity *= 2;

				reserve(NewCapacity);
			}

			new (ptr + NumberOfElements) T(forward<Args>(args)...);

			return ptr[NumberOfElements++];
		}

		size_t size()
		{
			return this->NumberOfElements;
		}

		T& operator[](size_t index)
		{
			return ptr[index];
		}

		void Clear()
		{
			destroy(ptr, NumberOfElements);
			NumberOfElements = 0;
		}

	private:
		
		T *ptr;
		size_t Capacity;
		size_t NumberOfElements;

		T* allocate(size_t NewCapacity)
		{
			return static_cast<T*>(ExAllocatePoolWithTag(PoolType, sizeof(T) * NewCapacity, Tag));
		}

		void destroy(T *mem, size_t NumElems)
		{
			if (!mem)
				return;

			for (auto i = 0UL; i < NumElems; i++)
			{
				mem[i].~T();
			}
		}

		void deallocate(T* mem)
		{
			if (mem)
				ExFreePool(mem);
		}
	};
}