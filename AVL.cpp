#include<iostream>
#include<cstring>
#include<cstdlib>
#define MAX 50
#define SIZE 20
using namespace std;

struct AVLnode
{
	public:
	char cWord[SIZE],cMeaning[MAX];
	AVLnode *left,*right;
	int iB_fac,iHt;
};

class tree
{
	
	public:
		AVLnode *root;
		tree()
		{
			root=NULL;
		}
		int height(AVLnode*);
		int bf(AVLnode*);
		AVLnode* insert(AVLnode*,char[SIZE],char[MAX]);
		AVLnode* rotate_left(AVLnode*);
		AVLnode* rotate_right(AVLnode*);
		AVLnode* LL(AVLnode*);
		AVLnode* RR(AVLnode*);
		AVLnode* LR(AVLnode*);
		AVLnode* RL(AVLnode*);
		AVLnode* delet(AVLnode*,char x[SIZE]);
		void inorder(AVLnode*);
};

AVLnode *tree::delet(AVLnode *curr,char x[SIZE])
{
	AVLnode *temp;
	if(curr==NULL)
		return(0);
	else
		if(strcmp(x,curr->cWord)>0)
		{
			curr->right=delet(curr->right,x);
			if(bf(curr)==2)
			if(bf(curr->left)>=0)
				curr=LL(curr);
			else
				curr=LR(curr);
		}
		else
		if(strcmp(x,curr->cWord)<0)
		{
			curr->left=delet(curr->left,x);
			if(bf(curr)==-2)
			if(bf(curr->right)<=0)
				curr=RR(curr);
			else
				curr=RL(curr);
		}
	else
	{
		if(curr->right!=NULL)
		{
			temp=curr->right;
			while(temp->left!=NULL)
			temp=temp->left;
			strcpy(curr->cWord,temp->cWord);
			curr->right=delet(curr->right,temp->cWord);
			if(bf(curr)==2)
			if(bf(curr->left)>=0)
				curr=LL(curr);
			else
				curr=LR(curr);
		}
		else
		return(curr->left);
	}
	curr->iHt=height(curr);
	return(curr);
}


AVLnode* tree :: insert(AVLnode*root,char newword[SIZE],char newmeaning[MAX])
{
	if(root==NULL)
	{
		root=new AVLnode;
		root->left=root->right=NULL;
		strcpy(root->cWord,newword);
		strcpy(root->cMeaning,newmeaning);
	}
	
	else if(strcmp(root->cWord,newword)!=0)
	{
		if(strcmp(root->cWord,newword)>0)
		{
			root->left=insert(root->left,newword,newmeaning);
			if(bf(root)==2)
			{
				if (strcmp(root->left->cWord,newword)>0)
					root=LL(root);
				else
					root=LR(root);
			}
		}
		
		else if(strcmp(root->cWord,newword)<0)
		{
			root->right=insert(root->right,newword,newmeaning);
			if(bf(root)==-2)
			{
				if(strcmp(root->right->cWord,newword)>0)
					root=RR(root);
				else
					root=RL(root);
			}
		}
	}
	else
		cout<<"\nRedundant AVLnode";
	root->iHt=height(root);
	return root;
}

int tree :: height(AVLnode* curr)
{
	int lh,rh;
	if(curr==NULL)
		return 0;
	if(curr->right==NULL && curr->left==NULL)
		return 0;
	else
	{
		lh=lh+height(curr->left);
		rh=rh+height(curr->right);
		if(lh>rh)
			return lh+1;
		return rh+1;
	}
}		

int tree :: bf(AVLnode* curr)
{
	int lh,rh;
	if(curr==NULL)
		return 0;
	else
	{
		if(curr->left==NULL)
			lh=0;
		else
			lh=1+curr->left->iHt;
		if(curr->right==NULL)
			rh=0;
		else
			rh=1+curr->right->iHt;
		return(lh-rh);
	}
}
			
AVLnode* tree :: rotate_right(AVLnode* curr)
{
	AVLnode* temp;
	temp=curr->left;
	curr->left=temp->right;
	temp->left=curr;
	curr->iHt=height(curr);
	temp->iHt=height(temp);
	return temp;
}

AVLnode* tree :: rotate_left(AVLnode* curr)
{
	AVLnode* temp;
	temp=curr->right;
	curr->right=temp->left;
	temp->left=curr;
	curr->iHt=height(curr);
	temp->iHt=height(temp);
	return temp;
}

AVLnode* tree :: RR(AVLnode* curr)
{
	curr=rotate_left(curr);
	return curr;
}

AVLnode* tree :: LL(AVLnode* curr)
{
	curr=rotate_right(curr);
	return curr;
}
	
AVLnode* tree :: RL(AVLnode* curr)
{
	curr->right=rotate_right(curr->right);
	curr=rotate_left(curr);
	return curr;
}

AVLnode* tree::LR(AVLnode* curr)
{
	curr->left=rotate_left(curr->left);
	curr=rotate_right(curr);
	return curr;
}

void tree :: inorder(AVLnode* curr)
{
	if(curr!=NULL)
	{
		inorder(curr->left);
		cout<<"\n\t"<<curr->cWord<<"\t"<<curr->cMeaning;
		inorder(curr->right);
	}
}

int main()
{
	int Ch;
	tree a;
	AVLnode *curr=NULL;
	char c[SIZE],cMean[MAX];
	cout<<"\n\tAVL TREE IMPLEMENTATION";	
	while(Ch!=4)
	{	
		cout<<"\n\t\tMENU";
		cout<<"\n1.Insert\n2.Inorder\n3.Delete\n4.Exit";
		cout<<"\nEnter your choice :";
		cin>>Ch;
		
		switch(Ch)
		{
			case 1:	cout<<"\nEnter Word : ";
				cin>>c;
				
				cout<<"\nEnter Meaning : ";
				cin.ignore();
				cin.getline(cMean,MAX);
				a.root=a.insert(a.root,c,cMean);
				break;
			
			case 2:	cout<<"\n\tWORD\tMEANING";
				a.inorder(a.root);
				break;
				
			case 3:	cout<<"\nEnter the word to be deleted : ";
					cin>>c;
					curr=a.delet(a.root,c);
					if(curr==NULL)
						cout<<"\nWord not present!";
					else
						cout<<"\nWord deleted Successfully!";
					curr=NULL;
					break;
			
			case 4:	exit(0);
		}
	}
	 
	return 0;
}