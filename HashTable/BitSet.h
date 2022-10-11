#pragma once
#include <vector>


//λͼ����������ݴ��ڣ�������Ӧ��bitλ����0��1
// �Ϳ��Ե����ʡ�ռ������
//�� 17 ��Ӧ��ӳ����� 00000010 00000000 00000000 
//�� 5  ��Ӧ��ӳ����� 00100000
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
			size_t j = x / 8;
			size_t i = x % 8;

			return _bit[i] & (1 << j);
		}

	private:
		std::vector<char> _bits;
	};


}
