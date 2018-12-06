#ifndef __DFS_H__
#define __DFS_H__

#include "adj_matrix_dir_graph.h"	// �ڽӾ�������ͼ

template <class ElemType>
void DFSTraverse(const AdjMatrixDirGraph<ElemType> &g, void (*visit)(const ElemType &))
// ��ʼ����������ͼg
// �����������ͼg����������ȱ���
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
	{	// ��ÿ�����������ʱ�־
		g.SetTag(v, UNVISITED);
	}

	for (v = 0; v < g.GetVexNum(); v++)
	{	// ����δ���ʵĶ��㰴DFS���������������
		if (g.GetTag(v) == UNVISITED)
		{	// ��v��ʼ���������������   
			#ifdef _MSC_VER
				DFS<ElemType>(g, v , visit);	// VC��<ElemType>ȷ������ģ�����
			#else
				DFS(g, v , visit);
			#endif
		}
	}
}

template <class ElemType>
void DFS(const AdjMatrixDirGraph<ElemType> &g, int v, void (*visit)(const ElemType &))
// ��ʼ����������ͼg
// ����������Ӷ���v�������������������ͼg
{	
	g.SetTag(v, VISITED);			// �����ʱ�־
	ElemType e;						// ��ʱ����
	g.GetElem(v, e);				// ����v������Ԫ��
	(*visit)(e);					// ���ʶ���v������Ԫ��
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w))
	{	// ��v����δ���ʹ����ڽӶ���w�ݹ����DFS
		if (g.GetTag(w) == UNVISITED)
		{	// ��w��ʼ���������������
			#ifdef _MSC_VER
				DFS<ElemType>(g, w , visit);	// VC��<ElemType>ȷ������ģ�����
			#else
				DFS(g, w , visit);
			#endif
		}
	}
}

#endif
