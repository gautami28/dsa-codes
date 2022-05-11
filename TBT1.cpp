#include<iostream>

using namespace std;

struct node{
	int data;
	node *left,*right;
	bool leftthread,rightthread;
};

class tree
{
	public:
		node *head;
		
		tree()
		{
			head = NULL;
			
		}
	void insert(int key)
	{
		node *temp;
		if(head==NULL)
		{
			head = new node;
			head->data = key;
			head->left=NULL;    
		    head->right=NULL; 
		    head->leftthread = true;
		    return;
		}
		temp = head;
	  	bool flag = false;
		  
		 while(!flag) 
		 {
		 	if(key< temp->data)
		 	{
		 		if(temp->left == NULL)
				{
					node *p = new node;
					p->data = key;
					p->left=NULL;    
		    		p->right=NULL; 
		    		temp->left = p;
		    		flag = true;
				}
				else
				{
					temp = temp->left;
				}	
			}
			else
			{
				if(temp->right == NULL)
				{
					node *p = new node;
					p->data = key;
					p->left=NULL;    
		    		p->right=NULL; 
		    		temp->right = p;
		    		p->rightthread = false;
		    		flag = true;
				}
				else
				{
					temp = temp->right;
					temp->leftthread = false;
				}	
			}
		 }
	}
	
	void preorder(node *temp)
	{
		if(temp==NULL)
		{return;}
    	cout<<temp->data<<" ";
    	preorder(temp->left);
    	preorder(temp->right);
	}
};

int main()
{
	int n;
	tree t;
	t.insert(15);
	t.insert(1);
	t.insert(30);
	t.insert(2);
	t.insert(40);
	cout<<t.head->data<<" "<<t.head->right->data<<" "<<t.head->left->data<<" "<<t.head->right->right->data<<" "<<t.head->left->right->data;
	cout<<endl;
	t.preorder(t.head);
	return 0;
}