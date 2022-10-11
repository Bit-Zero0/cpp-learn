#pragma once
#include <vector>


//λͼ����������ݴ��ڣ�������Ӧ��bitλ����0��1
// �Ϳ��Ե����ʡ�ռ������
//�� 17 ��Ӧ��ӳ����� 00000010 00000000 00000000 
//�� 5  ��Ӧ��ӳ����� 00100000

//������
//��40�ڸ����ظ����޷���������û�Ź��򡣸�һ���޷�����������ο����ж�һ�����Ƿ�����40�ڸ����С�
//����Ϳ���ʹ��λͼ��
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
			size_t i = x / 8;//������������ֽ�
			size_t j = x % 8;//�������Ӧ�����ƶ���λ

			_bits[i] |= (1 << j);//ʹ�� ���� �� |= ��֤����Ӱ�쵽��������λ
		}

		void reset(size_t x)
		{
			size_t i = x / 8;
			size_t j = x % 8;

			_bits[i] &= (~(1 << j));
		}

		bool test(size_t x)//�����λͼ����û���������
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


//λͼӦ��
//����100�ڸ�����������㷨�ҵ�ֻ����һ�ε�������
template<size_t N>
class TwoBitSet
{
public:
	void Set(size_t x)
	{
		if (!_bs1.test(x) && !_bs2.test(x))//���ݳ���һ�ν���_bs2
		{
			_bs2.set(x);
		}
		else if (!_bs1.test(x) && _bs2.test(x))//���ݳ��ֳ���һ�Σ�����_bs1,��ʾ������ݳ��ֶ��
		{
			_bs1.set(x);
			_bs2.reset(x);
		}
	}

	void PrintOnceNum()
	{
		for (size_t i = 0; i < N; i++)
		{
			if (!_bs1.test(i) && _bs2.test(i))//_bs2�е����ݾ���ֻ���ֹ�һ�ε����ݡ�
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

