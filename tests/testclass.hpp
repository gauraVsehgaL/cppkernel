class test
{
public:
	test(test&& other)
	{
		other;
		DbgPrint("test moveConstructor\n");
	}

	test& operator=(test&& other)
	{
		other;
		DbgPrint("test moveAssignment operator\n");
		return *this;
	}

	test& operator=(const test& other)
	{
		other;
		DbgPrint("testcopyAssignment operator\n");
		return *this;
	}

	test(const test& other)
	{
		other;
		DbgPrint("test CopyConstructor\n");
	}
	test()
	{
		DbgPrint("test Constructor\n");
	}
	~test()
	{
		DbgPrint("test Destructor\n");
	}
};

class anothertestclass
{
public:

	anothertestclass(anothertestclass&& other)
	{
		other;
		DbgPrint("anothertestclass moveConstructor\n");
	}

	anothertestclass& operator=(anothertestclass&& other)
	{
		other;
		DbgPrint("anothertestclass moveAssignment operator\n");
		return *this;
	}

	anothertestclass& operator=(const anothertestclass& other)
	{
		other;
		DbgPrint("anothertestclass copyAssignment operator\n");
		return *this;
	}

	anothertestclass(const anothertestclass& other)
	{
		other;
		DbgPrint("teanothertestclassst CopyConstructor\n");
	}
	anothertestclass(int a)
	{
		a;
		DbgPrint("anothertestclass Constructor\n");
	}
	anothertestclass()
	{
		DbgPrint("anothertestclass Constructor\n");
	}

	~anothertestclass()
	{
		DbgPrint("anothertestclass Destructor\n");
	}
};


class container
{
	void *ptr;
public:
	container(container&& other)
	{
		other;
		ptr = ExAllocatePool(PagedPool, 100);
		DbgPrint("container moveConstructor\n");
	}

	container& operator=(container&& other)
	{
		other;
		ptr = ExAllocatePool(PagedPool, 100);
		DbgPrint("container moveAssignment operator\n");
		return *this;
	}

	container& operator=(const container& other)
	{
		other;
		ptr = ExAllocatePool(PagedPool, 100);
		DbgPrint("container copyAssignment operator\n");
		return *this;
	}

	container(const container& other)
	{
		other;
		ptr = ExAllocatePool(PagedPool, 100);
		DbgPrint("container CopyConstructor\n");
	}
	container()
	{
		ptr = ExAllocatePool(PagedPool, 100);
		DbgPrint("container Constructor\n");
	}

	~container()
	{
		ExFreePool(ptr);
		DbgPrint("container Destructor\n");
	}
};