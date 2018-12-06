#ifndef __PARENT_TREE_NODE_H__
#define __PARENT_TREE_NODE_H__

// ˫����ʾ�������ģ�� 
template <class ElemType>
struct ParentTreeNode 
{
// ���ݳ�Ա:
	ElemType data;									// ������
	int parent;										// ˫��λ����

// ���캯��ģ��:
	ParentTreeNode();								// �޲����Ĺ��캯��ģ��
	ParentTreeNode(ElemType item, int pt = -1);		// ��֪������ֵ��˫��λ�ý������
};

// ˫����ʾ�������ģ���ʵ�ֲ���
template<class ElemType>
ParentTreeNode<ElemType>::ParentTreeNode()
// �������������˫����Ϊ-1�Ľ��
{
	parent = -1;
}

template<class ElemType>
ParentTreeNode<ElemType>::ParentTreeNode(ElemType item, int pt)
// �������������һ��������Ϊitem��˫����Ϊpt�Ľ��
{
	data = item;
	parent = pt;
}

#endif
