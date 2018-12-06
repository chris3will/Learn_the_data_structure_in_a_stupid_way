#ifndef __SIMPLE_TRANSPOSE_H__
#define __SIMPLE_TRANSPOSE_H__

#include "tri_sparse_matrix.h"		// ϡ��������Ԫ��˳���

template<class ElemType>
void SimpleTranspose(const TriSparseMatrix<ElemType> &source, TriSparseMatrix<ElemType> &dest)
// �����������ϡ�����sourceת�ó�ϡ�����dest
{
	dest.rows = source.cols;							// ����
	dest.cols = source.rows;							// ����
	dest.num = source.num;								// ����Ԫ�ظ���
	dest.maxSize = source.maxSize;						// ������Ԫ�ظ���
	delete []dest.triElems;								// �ͷŴ洢�ռ�
	dest.triElems = new Triple<ElemType>[dest.maxSize];	// ����洢�ռ�

	if (dest.num > 0)
	{
		int destPos = 0;								// ϡ�����dest����һ����Ԫ��Ĵ��λ��
		for (int col = 1; col <= source.cols; col++)
		{	// ת��ǰ���б�Ϊת�ú����
			for (int sourcePos = 0; sourcePos < source.num; sourcePos++)
			{	// ���ҵ�col�е���Ԫ��
				if (source.triElems[sourcePos].col == col)
				{	// �ҵ���col�е�һ����Ԫ��,ת�ú����dest
					dest.triElems[destPos].row = source.triElems[sourcePos].col;	// �б���
					dest.triElems[destPos].col = source.triElems[sourcePos].row;	// �б���
					dest.triElems[destPos].value = source.triElems[sourcePos].value;
						// ����Ԫ��ֵ����
					destPos++;														// ����һ��Ԫ�صĴ��λ��
				}
			}
		}
	}
}

#endif

