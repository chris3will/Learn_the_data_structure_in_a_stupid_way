#ifndef __PI_H__
#define __PI_H__

// �ļ�·����:ex1_8\alg.h 
struct Data
{	// �洢��ͨ�����
	unsigned s: 4;					// �͵�һλ
	unsigned u: 4;					// ͨ���һλ
};

void Pi(int precision)
{
	ofstream outFile("pi.txt");													// �洢������ļ�
	unsigned int n = (unsigned int)((precision + 5) / log10((double)2)) + 3;	// ���㵽��n��Ϊֹ
	int aSize = precision + 7 + (int)log10((double)4 * n);						// ���������С
	Data *dt;						// PIΪdt[0].s. dt[1].s dt[2].s dt[3].s dt[3].s ... dt[aSize-1].s
									// ������ͨ��dt[0].u dt[1].u dt[2].u dt[3].u ... dt[aSize-1].u  
	int a = 1, b = 3;				// ��ͨ��Ϊ2*1/3*2/5*3/7...*a/b,��1��Ϊ2*1/3,a=1,b=3
	int i;							// ��ʱ����
	
	dt = new Data[aSize];			// Ϊdt����洢�ռ�
	for (i = 0; i < aSize; i++)
	{	// ��dt�ĸ����ʼ��Ϊ0
		dt[i].s = dt[i].u = 0;
	}

	dt[0].s = 2;					// �����ĵ�0��
	dt[0].u = 2;					// �����ĵ�0��
	int noZeroPos = 0;				// ����u�ĵ�һ������Ԫ�ص��±�

	for (unsigned int count = 0; count <= n; count++)
	{
		// ����u *= a;
		int c;						// ��ʱ����
		int d = 0;					// �˴�d��ʾ��������еĽ�λ����
		for (i = aSize - 1; i >= noZeroPos; i--)
		{
			c = dt[i].u * a + d;	// ����˻�
			dt[i].u = c % 10;		// ��iλ
			d = c / 10;				// ��λ
		}
		for (i = noZeroPos - 1; i >= 0 && d > 0; i--)
		{	// u*a���λ�Ľ�λ
			c = dt[i].u * a + d;	// ����˻�
			dt[i].u = c % 10;		// ��iλ
			d = c / 10;				// ��λ
		}
		noZeroPos = i + 1;			// �µ�ͨ��ĵ�һ������Ԫ�ص��±�
		
		// ����u /= b;
		d = 0;						// �˴�d��ʾ��������е�����
		for (i = noZeroPos; i < aSize; i++)
		{
			c = dt[i].u + d * 10;	// ������d����10����ӵ�dt[i].u 
			dt[i].u = c / b;		// �����µĵ�iλ
			d = c % b;				// �����µ�����
			if (dt[i].u != 0) break;
		}

		noZeroPos = i;				// �µ�����u�ĵ�һ������Ԫ�ص��±�
		for (i = noZeroPos + 1; i<aSize; i++)
		{
			c = dt[i].u + d * 10;	// ������d����10����ӵ�dt[i].u 
			dt[i].u = c / b;		// �����µĵ�iλ
			d = c % b;				// �����µ�����
		}

		// ����s += u;
		d = 0;						// �˴�d��ʾ��������еĽ�λ����
		for (i = aSize - 1; i >= noZeroPos; i--)
		{
			c = dt[i].s + dt[i].u + d;	// �����
			dt[i].s = c % 10;		// �����µĵ�iλ
			d = c / 10;				// ��λ
		}
		for(i = noZeroPos - 1; i >= 0; i--)
		{
			c = dt[i].s + d;		// dt.s[i] + d���ܴ���10,�����µĽ�λ
			dt[i].s = c % 10;		// �����µĵ�iλ
			if (c / 10 == 0) break;	// �޽�λ
			d = c / 10;				// ��λ
		}

		a++;						// ��һ���a
		b += 2;						// ��һ���b
	}

	// �����������ļ�pi.txt��
	outFile << dt[0].s << ".";
	for (i = 1; i < precision; i++)
	{
		outFile << dt[i].s;
	}
	outFile << endl;
	if (dt[precision].s == 9 && dt[precision + 1].s == 9 && dt[precision + 2].s == 9 && 
		dt[precision + 3].s == 9 && dt[precision + 4].s == 9 && dt[precision + 5].s == 9 ||
		dt[precision].s == 0 && dt[precision + 1].s == 0 && dt[precision + 2].s == 0 && 
		dt[precision + 3].s == 0 && dt[precision + 4].s == 0 && dt[precision + 5].s == 0)
	{	// �����PI���λ���������
		outFile << "���λ���������" << endl;
	}

	outFile.close();				// �ر��ļ�
	delete []dt;					// �ͷ�dt
}


#endif