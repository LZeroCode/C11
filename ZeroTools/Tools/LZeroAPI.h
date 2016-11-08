#pragma once

namespace Zero
{
	//交换数据
	void swap(int& a, int& b)
	{
		if (a != b)
		{
			a ^= b;
			b ^= a;
			a ^= b;
		}
	}

	//符号反转
	int signreverse(int a)
	{
		return ~a + 1;
	}

	//取绝对值
	int abs_ex(int val)
	{
		int i = val >> 31;
		return (val^i) - i;
	}
}