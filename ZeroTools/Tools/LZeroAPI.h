#pragma once

namespace Zero
{
	//��������
	void swap(int& a, int& b)
	{
		if (a != b)
		{
			a ^= b;
			b ^= a;
			a ^= b;
		}
	}

	//���ŷ�ת
	int signreverse(int a)
	{
		return ~a + 1;
	}

	//ȡ����ֵ
	int abs_ex(int val)
	{
		int i = val >> 31;
		return (val^i) - i;
	}
}