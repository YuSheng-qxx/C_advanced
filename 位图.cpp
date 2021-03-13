#include<vector>
#include<string>
using namespace std;

class bitMap
{
public:
	//ͨ�����ݷ�Χ��ȷ����Ҫ���Ŀռ��С
	bitMap(int range)
	{
		_bitMap.resize(range / 32 + 1, 0);
	}

	//�����Ϣ
	void set(int data)
	{
		//����λ��
		//1.��������λ�ã�data / 32��  data >> 5
		int idx = data / 32;
		//2.����bitλ�ã�data % 32
		int bitNum = data % 32;
		//3.��Ӧbitλ��1��_bitMap[idx] | (1 << bitNum)
		_bitMap[idx] |= 1 << bitNum;
	}

	//������Ϣ
	int test(int data)
	{
		//����λ��
		//1.����λ��
		int idx = data / 32;
		//2.bitλ��
		int bitNum = data % 32;
		return (_bitMap[idx] >> bitNum) & 1;
	}

	//ɾ����Ϣ
	void reset(int data)
	{
		//1.����λ��
		int idx = data / 32;
		//2.bitλ��
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

//��¡������
//��ϣ����������k
//Ԫ�ظ�����n
//��Ҫ��bitλ������m
//�����ϵ��k = (m / n) * ln2, �����ʿ��Լ���Ľ���
//m = k * n / ln2

//���貼¡����������������ϣ����
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
		//�ֱ���ÿһ����ϣ��������һ����ϣ��λ��
		int idx1 = hf1(data) % _bitCount;
		int idx2 = hf2(data) % _bitCount;
		int idx3 = hf3(data) % _bitCount;
		//ͨ��λͼ�����д��
		_b.set(idx1);
		_b.set(idx2);
		_b.set(idx3);

	}

	bool test(const V& data)
	{
		//ֻҪ��һ��λ��Ϊ0����һ��������
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
		//���ܴ��ڣ�������
		return true;
	}

private:
	bitMap _b;
	//��bitλ����
	size_t _bitCount;
};

void test()
{
	//��Χ��0~99֮���������Ϣ
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