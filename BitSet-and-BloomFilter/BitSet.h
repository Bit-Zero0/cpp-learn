#pragma once
#include <vector>


//位图就是如果数据存在，则在相应的bit位上由0至1
// 就可以到达节省空间的作用
//如 17 对应的映射就是 00000010 00000000 00000000 
//如 5  对应的映射就是 00100000

//面试题
//给40亿个不重复的无符号整数，没排过序。给一个无符号整数，如何快速判断一个数是否在这40亿个数中。
//此题就可以使用位图。
namespace fmy
{
	template<size_t N>
	class bitset 
	{
	public:
		bitset()
		{
			_bits.resize(N / 8 + 1, 0);
		}

		void set(size_t x)
		{
			size_t i = x / 8;//求出数据所在字节
			size_t j = x % 8;//求出数据应该左移多少位

			_bits[i] |= (1 << j);//使用 左移 后 |= 保证不会影响到其他比特位
		}

		void reset(size_t x)
		{
			size_t i = x / 8;
			size_t j = x % 8;

			_bits[i] &= (~(1 << j));
		}

		bool test(size_t x)//检查在位图中有没有这个数据
		{
			size_t i = x / 8;
			size_t j = x % 8;

			return _bits[i] & (1 << j);
		}

	private:
		std::vector<char> _bits;
	};

	void test_bitset()
	{
		bitset<100> bs;
		bs.set(5);
		bs.set(4);
		bs.set(10);
		bs.set(20);

		cout << bs.test(5) << endl;
		cout << bs.test(4) << endl;
		cout << bs.test(10) << endl;
		cout << bs.test(20) << endl;
		cout << bs.test(21) << endl;
		cout << bs.test(6) << endl << endl;

		bs.reset(20);
		bs.reset(10);
		bs.reset(5);
		bs.set(44);

		cout << bs.test(5) << endl;
		cout << bs.test(4) << endl;
		cout << bs.test(10) << endl;
		cout << bs.test(20) << endl;
		cout << bs.test(21) << endl;
		cout << bs.test(6) << endl;
		cout << bs.test(44) << endl;

		//bitset<0xffffffff> bs;
		/*bitset<-1> bs;*/
	}
}


//位图应用
//给定100亿个整数，设计算法找到只出现一次的整数？
template<size_t N>
class TwoBitSet
{
public:
	void Set(size_t x)
	{
		if (!_bs1.test(x) && !_bs2.test(x))//数据出现一次进入_bs2
		{
			_bs2.set(x);
		}
		else if (!_bs1.test(x) && _bs2.test(x))//数据出现超过一次，进入_bs1,表示这个数据出现多次
		{
			_bs1.set(x);
			_bs2.reset(x);
		}
	}

	void PrintOnceNum()
	{
		for (size_t i = 0; i < N; i++)
		{
			if (!_bs1.test(i) && _bs2.test(i))//_bs2中的数据就是只出现过一次的数据。
			{
				cout << i << endl;
			}
		}
	}
private:
	fmy::bitset<N> _bs1;
	fmy::bitset<N> _bs2;
};

void TestTwoBitSet()
{
	int a[] = { 99,0,4,50,33,44,2,5,99,0,50,99,50,2 };
	TwoBitSet<100> bs;
	for (auto e : a)
	{
		bs.Set(e);
	}

	bs.PrintOnceNum();
}

