#ifndef __BFS_H__
#define __BFS_H__

#include "adj_list_dir_graph.h"	// �ڽӱ�����ͼ
#include "lk_queue.h"			// ������

template <class ElemType>
void BFSTraverse(const AdjListDirGraph<ElemType> &g, void (*visit)(const ElemType &))
// ��ʼ����������ͼg
// �����������ͼg���й�����ȱ���
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
	{	// ��ÿ�����������ʱ�־
		g.SetTag(v, UNVISITED);
	}

	for (v = 0; v < g.GetVexNum(); v++)
	{	// ����δ���ʵĶ��㰴BFS���������������
		if (g.GetTag(v) == UNVISITED) 
		{
			#ifdef _MSC_VER
				BFS<ElemType>(g, v , visit);	// VC��<ElemType>ȷ������ģ�����
			#else
				BFS(g, v , visit);
			#endif
		}
	}
}

template <class ElemType>
void BFS(const AdjListDirGraph<ElemType> &g, int v, void (*visit)(const ElemType &))
// ��ʼ����������ͼg
// ����������ӵڶ���v�������й����������ͼg
{	
	g.SetTag(v, VISITED);						// �����ʱ�־
	ElemType e;									// ��ʱ����
	g.GetElem(v, e);							// ����v������Ԫ��
	(*visit)(e);								// ���ʶ���v������Ԫ��
	LinkQueue<int> q;							// �������
	q.InQueue(v);								// v���
	while (!q.Empty())
	{	// ����q�ǿ�, ����ѭ��
		int u, w;								// ��ʱ����
		q.OutQueue(u);							// ����
		for (w = g.FirstAdjVex(u); w >= 0; w = g.NextAdjVex(u, w))
		{	// ��u��δ���ʹ����ڽӶ���w���з���
			if (g.GetTag(w) == UNVISITED)
			{	// ��w���з���
				g.SetTag(w, VISITED);			// �����ʱ�־
 				g.GetElem(w, e);				// ����w������Ԫ��
				(*visit)(e);					// ���ʶ���w������Ԫ��
				q.InQueue(w);					// w���
			}
		}
	}
}

#endif
