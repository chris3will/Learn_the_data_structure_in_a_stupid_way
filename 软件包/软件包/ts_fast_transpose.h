#ifndef __SIMPLE_TRANSPOSE_H__
#define __SIMPLE_TRANSPOSE_H__

#include "tri_sparse_matrix.h"		// ϡ��������Ԫ��˳���

template<class ElemType>
void FastTranspose(const TriSparseMatrix<ElemType> &source, TriSparseMatrix<ElemType> &dest)
// �����������ϡ�����sourceת�ó�ϡ�����dest
{
	dest.rows = source.cols;							// ����
	dest.cols = source.rows;							// ����
	dest.num = source.num;								// ����Ԫ�ظ���
	dest.maxSize = source.maxSize;						// ������Ԫ�ظ���
	delete []dest.triElems;								// �ͷŴ洢�ռ�
	dest.triElems = new Triple<ElemType>[dest.maxSize];	// ����洢�ռ�

	int *cNum = new int[source.cols + 1];				// sourceÿһ�еķ���Ԫ����
	int *cPos = new int[source.cols + 1];				// sourceÿһ�еĵ�һ������Ԫ��dest�еĴ洢λ��


	if (dest.num > 0)
	{
		for (int col = 1; col <= source.cols; col++) cNum[col] = 0;	// ��ʼ��cNum
		for (int sourcePos = 0; sourcePos < source.num; sourcePos++)
			++cNum[source.triElems[sourcePos].col];		// ͳ��sourceÿһ�еķ���Ԫ����
		cPos[1] = 0;									// ��һ�еĵ�һ������Ԫ��dest�洢����ʼλ��
		for (col = 2; col <= source.cols; col++)
		{	// ѭ����ÿһ�еĵ�һ������Ԫ��dest�洢����ʼλ��
			cPos[col] = cPos[col - 1] + cNum[col - 1];	
		}

		for (sourcePos = 0; sourcePos < source.num; sourcePos++)
		{	// ѭ������source����Ԫ��
			int destPos = cPos[source.triElems[sourcePos].col];	
				// ���ڱ�ʾdest��ǰ�е���һ������Ԫ��Ԫ��Ĵ洢λ��
			dest.triElems[destPos].row = source.triElems[sourcePos].col;		// �б���
			dest.triElems[destPos].col = source.triElems[sourcePos].row;		// �б���
			dest.triElems[destPos].value = source.triElems[sourcePos].value;	// ����Ԫ��ֵ����
			++cPos[source.triElems[sourcePos].col];				
				// dest��ǰ�е���һ������Ԫ��Ԫ��Ĵ洢��λ��
		}
	}

	delete []cNum;										// �ͷ�cNum
	delete []cPos;										// �ͷ�cPos
}



#endif

