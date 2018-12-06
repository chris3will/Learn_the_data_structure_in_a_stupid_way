#include"map"
#include"queue"
#include"iostream"
#include"algorithm"
#include"utility"
using namespace std;

// template<class T>
// class Tree;

// template<class T>
// class weightTable {
//     private:
//     map<T,int> weight_table;
//     map<T,double>normal_wei_table;
//     int total_weight;
//     public:
//     bool Add(int num, T elem);
//     bool Delete(int num, T elem);
// };

template <class T>
class TreeNode {
	// friend Tree<T>;
private:
	T element;
	TreeNode<T> *lchild;
	TreeNode<T> *rchild;
public:
	TreeNode(T elem) :element(elem), lchild(nullptr), rchild(nullptr) {}
	bool addL(TreeNode<T> &elem);
	bool addR(TreeNode<T> &elem);
};

class wei_node_pair;

template<class T>
class weight_TreeNode :public TreeNode<T> {
	friend wei_node_pair;
private:
	int weight;
public:
	weight_TreeNode(T elem, int weight = 0) :TreeNode<T>(elem), weight(weight) {}
	weight_TreeNode* operator+(weight_TreeNode &obj) {
		return new weight_TreeNode('\0', this->weight + obj.weight);
	}
	int GetWeight() const {
		return this->weight;
	}
};

class wei_node_pair {
	friend bool operator >(wei_node_pair a, wei_node_pair b);
private:
	pair<int, weight_TreeNode<char>*> elem;
public:
	wei_node_pair(weight_TreeNode<char> &obj) {
		elem.first = obj.weight;
		elem.second = &obj;
	}
	// wei_node_pair(int weight) {
	//     elem.first = weight;
	//     elem.second = this;
	// }
	// bool operator <(const wei_node_pair &obj) {
	//     return this->elem.first < obj.elem.first;
	// }
	// bool operator >(const wei_node_pair &obj) {
	//     return this->elem.first > obj.elem.first;
	// }
	weight_TreeNode<char> * second() const {
		return elem.second;
	}
};
bool operator >(wei_node_pair a, wei_node_pair b) {
	return a.elem.first > b.elem.first;
}
// template <class T>
// class Tree {
//     private:
//     TreeNode<T> *root;
//     int elemNum;
//     public:
//     Tree():elemNum(0),root(nullptr){}
//     TreeNode<T> & Root() {return *root}
//     TreeNode<T> &Parent(T elem);
//     TreeNode<T> &LChild(T elem);
//     TreeNode<T> &RightSibling(T elem);
//     bool TreeEmpty();
//     int TreeDepth();
//     void Traverse();
// };

priority_queue<wei_node_pair, vector<wei_node_pair>, greater<wei_node_pair> > pq;

weight_TreeNode<char>* buildHuffman(priority_queue<wei_node_pair, vector<wei_node_pair>, greater<wei_node_pair> > pq);

template<class T>
bool TreeNode<T>::addL(TreeNode<T> &elem) {
	if (lchild == nullptr) {
		lchild = &elem;
		return true;
	}
	return false;
}

template<class T>
bool TreeNode<T>::addR(TreeNode<T> &elem) {
	if (rchild == nullptr) {
		rchild = &elem;
		return true;
	}
	return false;
}

weight_TreeNode<char>* buildHuffman(priority_queue<wei_node_pair, vector<wei_node_pair>, greater<wei_node_pair> > pq) {
	weight_TreeNode<char> *root, *right, *left;
	if (pq.empty()) {
		return nullptr;
	}
	if (pq.size() == 1) {
		root = pq.top().second();
		pq.pop();
		return root;
	}
	while (true) {
		right = pq.top().second();
		pq.pop();
		left = pq.top().second();
		pq.pop();
		root = *right + *left;
		root->addL(*left);
		root->addR(*right);
		if (pq.empty()) {
			break;
		}
		pq.push(wei_node_pair(*root));
	}
	return root;
}


int main()
{
	priority_queue<wei_node_pair, vector<wei_node_pair>, greater<wei_node_pair> > pq;

	weight_TreeNode<char> a1('a', 1);
	weight_TreeNode<char> a2('b', 2);
	weight_TreeNode<char> a3('c', 3);
	weight_TreeNode<char> a4('d', 9);



	wei_node_pair a5(a1);
	pq.push( a5);
	weight_TreeNode<char> *tt = buildHuffman(pq);
	return 0;
}