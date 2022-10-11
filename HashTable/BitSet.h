#pragma once
#include <vector>


//位图就是如果数据存在，则在相应的bit位上由0至1
// 就可以到达节省空间的作用
//如 17 对应的映射就是 00000010 00000000 00000000 
//如 5  对应的映射就是 00100000
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
			size_t j = x / 8;
			size_t i = x % 8;

			return _bit[i] & (1 << j);
		}

	private:
		std::vector<char> _bits;
	};


}
