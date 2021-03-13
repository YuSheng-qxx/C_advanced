#include<vector>
#include<string>
using namespace std;

class bitMap
{
public:
	//通过数据范围，确定需要开的空间大小
	bitMap(int range)
	{
		_bitMap.resize(range / 32 + 1, 0);
	}

	//存放信息
	void set(int data)
	{
		//计算位置
		//1.计算整数位置：data / 32，  data >> 5
		int idx = data / 32;
		//2.计算bit位置：data % 32
		int bitNum = data % 32;
		//3.对应bit位置1：_bitMap[idx] | (1 << bitNum)
		_bitMap[idx] |= 1 << bitNum;
	}

	//查找信息
	int test(int data)
	{
		//计算位置
		//1.整数位置
		int idx = data / 32;
		//2.bit位置
		int bitNum = data % 32;
		return (_bitMap[idx] >> bitNum) & 1;
	}

	//删除信息
	void reset(int data)
	{
		//1.整数位置
		int idx = data / 32;
		//2.bit位置
		int bitNum = data % 32;
		_bitMap[idx] &= ~(1 << bitNum);
	}
private:
	vector<int> _bitMap;
	//size_t _size;
};

struct HashFun1
{
	size_t operator()(const string& str)
	{
		size_t hashret = 0;
		for (char ch : str)
		{
			hashret = hashret * 131 + ch;
		}
		return hashret;
	}
};

struct HashFun2
{
	size_t operator()(const string& str)
	{
		size_t hashret = 0;
		for (char ch : str)
		{
			hashret = hashret * 65599 + ch;
		}
		return hashret;
	}
};

struct HashFun3
{
	size_t operator()(const string& str)
	{
		size_t magic = 63689;
		size_t hashret = 0;
		for (char ch : str)
		{
			hashret = hashret * magic + ch;
			magic *= 378551;
		}
		return hashret;
	}
};

//布隆过滤器
//哈希函数个数：k
//元素个数：n
//需要的bit位数量：m
//满足关系：k = (m / n) * ln2, 误判率可以极大的降低
//m = k * n / ln2

//假设布隆过滤器中有三个哈希函数
template <class V, class HF1, class HF2, class HF3>
class bloomFilter
{
public:
	bloomFilter(size_t dataNum)
		:_b(5 * dataNum)
		, _bitCount(5 * dataNum)
	{}

	void set(const V& data)
	{
		HF1 hf1;
		HF2 hf2;
		HF3 hf3;
		//分别用每一个哈希函数计算一个哈希的位置
		int idx1 = hf1(data) % _bitCount;
		int idx2 = hf2(data) % _bitCount;
		int idx3 = hf3(data) % _bitCount;
		//通过位图，进行存放
		_b.set(idx1);
		_b.set(idx2);
		_b.set(idx3);

	}

	bool test(const V& data)
	{
		//只要有一个位置为0，就一定不存在
		HF1 hf1;
		int idx1 = hf1(data) % _bitCount;
		if (!_b.test(idx1))
			return false;
		HF2 hf2;
		int idx2 = hf2(data) % _bitCount;
		if (!_b.test(idx2))
			return false;
		HF3 hf3;
		int idx3 = hf3(data) % _bitCount;
		if (!_b.test(idx3))
			return false;
		//可能存在，有误判
		return true;
	}

private:
	bitMap _b;
	//总bit位数量
	size_t _bitCount;
};

void test()
{
	//范围：0~99之间的数据信息
	bitMap b(100);
	b.set(1);
	b.set(32);
	b.set(96);
	b.set(99);
	int ret = b.test(1);
	ret = b.test(30);
}

int main()
{
	test();
	return 0;
}