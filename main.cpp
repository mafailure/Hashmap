#include<bits/stdc++.h>
using namespace std;
template<typename V> 
class Node 
{
	public: 
	string key; 
	V val; 
	Node * next; 
	Node(string key,V val):key(key),val(val)
	{
		next=NULL; 
	}
	~Node()
	{
		delete next; 
	}
	
};
template<typename V>
class Map 
{
	private: 
	int BUCKETSIZE; 
	int NUMOFKEY; 
	Node<V> ** BUCKET;
	void rehash()
	{
		Node<V>** NEWBUCKET=new Node<V>*[2*BUCKETSIZE]; 
		for(int i=0;i<2*BUCKETSIZE;i++)NEWBUCKET[i]=NULL;
		swap(NEWBUCKET,BUCKET);;
		int NEWBUCKETSIZE=BUCKETSIZE;
		BUCKETSIZE*=2;  
		for(int i=0;i<NEWBUCKETSIZE;i++)
		{
			Node<V> * head= NEWBUCKET[i]; 
			while(head)
			{
				insert(head->key,head->val); 
				head=head->next; 
			}
		}
		for(int i=0;i<NEWBUCKETSIZE;i++)delete NEWBUCKET[i]; 
		delete[]NEWBUCKET; 
	}
	public: 
	Map()
	{
		BUCKETSIZE=10; 
		NUMOFKEY=0; 
		BUCKET=new Node<V>*[10]; 
		for(int i=0;i<BUCKETSIZE;i++)BUCKET[i]=0; 
	}
	~Map()
	{
		for(int i=0;i<BUCKETSIZE;i++)delete BUCKET[i] ; 
		delete[] BUCKET; 
	}
	private: int hashFun(string s)
	{
		int p=1; 
		int pp=31; 
		int hashcode=0; 
		for(int i=0;i<s.size();i++)hashcode=(hashcode+(s[i]+1)*p)%BUCKETSIZE,p=(p*pp)%BUCKETSIZE; 
		return hashcode; 
	}
	public: void insert(string s,V val)
	{
		 int key=this->hashFun(s); 
		 Node<V>* head=BUCKET[key]; 
		 while(head!=NULL)
		 {
		 		if(head->key==s)
		 		{
		 			head->val =val; 
		 			return ; 
		 		}
		 		head=head->next; 
		 }
		 NUMOFKEY++; 
		 Node<V>* temp=new Node<V>(s,val); 
		 temp->next=BUCKET[key]; 
		 BUCKET[key]=temp;
		 if((NUMOFKEY+.0)/BUCKETSIZE >=0.7)rehash(); 
		 return ;  
		 
	}
	public:V search(string s)
	{
		 int key=this->hashFun(s); 
		 Node<V> * head=BUCKET[key]; 
		 while(head!=NULL)
		 {
		 	if (head->key==s)return head->val;
		 	head=head->next;   
		 }
		 return 0; 
	}
	public:void remove(string s)
	{
		int key=this->hashFun(s); 
		Node<V> * head=BUCKET[key];
		Node<V> * prev=0;  
		while(head)
		{
			if(head->key==s)
			{
				if(prev)
				prev->next=head->next; 
				else BUCKET[key]=head->next; 
				head->next=NULL; 
				delete head; 
			}
			prev=head; 
			head=head->next; 
		}
		return; 
	}
	public:void display()
	{
		for(int i=0;i<BUCKETSIZE;i++)
		{
			Node<V> * head=BUCKET[i]; 
			while(head)cout<<head->key<<" -> "<<head->val<<endl,head=head->next;  
		}
	}
	
	
	
	
};
