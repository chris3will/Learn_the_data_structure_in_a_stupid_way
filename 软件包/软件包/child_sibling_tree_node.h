#ifndef __CHILD_SIBLING_FOREST_NODE_H__
#define __CHILD_SIBLING_FOREST_NODE_H__

// �����ֵܱ�ʾ�������ģ��
template <class ElemType>
struct ChildSiblingTreeNode 
{
// ���ݳ�Ա:
	ElemType data;								// ������
	ChildSiblingTreeNode<ElemType> *firstChild;	// ָ���׺���ָ����
	ChildSiblingTreeNode<ElemType> *rightSibling;// ָ�����ֵ�ָ����

// ���캯��ģ��:
	ChildSiblingTreeNode();						// �޲����Ĺ��캯��ģ��
	ChildSiblingTreeNode(ElemType item,			// ��֪������ֵ��ָ���׺��������ֵ�ָ�뽨�����
		ChildSiblingTreeNode<ElemType> *fChild = NULL,
		ChildSiblingTreeNode<ElemType> *rSibling = NULL);	
		
};

// �����ֵܱ�ʾ�������ģ���ʵ�ֲ���
template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode()
// �������������ָ����Ϊ�յĽ��
{
	firstChild = rightSibling = NULL;			// ָ���׺��Ӽ��ֵܵ�ָ�붼Ϊ��
}

template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode(ElemType item,			// ��֪������ֵ��˫��λ�ý����ṹ
		ChildSiblingTreeNode<ElemType> *fChild,
		ChildSiblingTreeNode<ElemType> *rSibling)
// �������������һ��������Ϊitem���׺���ΪfChild�����ֵ�ΪrChild�Ľ��
{
	data = item;								// ����
	firstChild = fChild;						// �׺���
	rightSibling = rSibling;					// ���ֵ�
}

#endif
