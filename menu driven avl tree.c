//MENU DRIVEN AVL TREE

#include<stdio.h>
#include<stdlib.h>

struct node{
	struct node*left;
	struct node* right;
	int key;
	int h;
};

struct node* NewNode(int data){
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->left = NULL;
	temp->right = NULL;
	temp->key =data;
	temp->h =0;
	return temp;
}

int Height(struct node* temp){
if(temp == NULL)return -1;
else return temp->h;
}

int GETBALANCE(struct node* temp){
	if(temp == NULL)return 0;
	return (Height(temp->left)-Height(temp->right));
}

struct node* RIGHTROTATE(struct node* temp){
	struct node* left = temp->left;
	struct node* right = left->right;
	left->right=temp;
	temp->left = right;
	
	temp->h = 1+((Height(temp->left)>Height(temp->right))?Height(temp->left):Height(temp->right));
	left->h = 1+((Height(left->left)>Height(left->right))?Height(left->left):Height(left->right));
	return left;
}

struct node* LEFTROTATE(struct node* temp){
	struct node* rightnode = temp->right;
	struct node* leftnode = rightnode->left;
	rightnode->left = temp;
	temp->right = leftnode;
	
	temp->h = 1+((Height(temp->left)>Height(temp->right))?Height(temp->left):Height(temp->right));
	rightnode->h = 1+((Height(rightnode->left)>Height(rightnode->right))?Height(rightnode->left):Height(rightnode->right));
	return rightnode;
}
struct node* INSERT(struct node* head,int k){
	if(head == NULL)return NewNode(k);
	else if(head->key > k){
		head->left = INSERT(head->left,k);
	}
	else head->right = INSERT(head->right,k);
	
	head->h = 1+ ((Height(head->left) > Height(head->right))?Height(head->left):Height(head->right));
	
	int bal = GETBALANCE(head);
	
	if(bal > 1 && k  < head->left->key)return RIGHTROTATE(head);
	if(bal < -1 && k > head->right->key)return LEFTROTATE(head);
	if(bal >1 && k > head->left->key){
		head->left = LEFTROTATE(head->left);
		return RIGHTROTATE(head);
	}
	
	if(bal < -1 && k < head->right->key){
		head->right = RIGHTROTATE(head->right);
		return LEFTROTATE(head); 
	}
	
	return head;
}


struct node* SEARCH(struct node* A,int k){
	if (A== NULL)return NULL;
	if(A->key == k)return A;
	if (A->key > k) return SEARCH(A->left,k);
	else return SEARCH(A->right,k);
}

struct node* TREEMINIMUM(struct node* temp){
	if(temp == NULL)return NULL;
	while(temp->left != NULL)temp = temp->left;
	return temp;
}

struct node* DELETENODE(struct node* head,int k){
	if(head==NULL){
	return head;
	}
	
	else if(head->key > k){
		head->left = DELETENODE(head->left,k);
	}
	else if(head->key < k) head->right = DELETENODE(head->right,k);
	else if(head->key == k){
		
		if(head->left == NULL){
			if(head->right == NULL)return NULL;
			struct node* temp = head;
			head=head->right;
			free(temp);
		}
		else if(head->right == NULL){
			struct node* temp =  head;
			head= head->left;
			free(temp);
		}
		
		else {
		
		struct node* temp = TREEMINIMUM(head->right);
		head->key = temp->key;
		head->right = DELETENODE(head->right,temp->key);
		
		}
		}
		head->h = 1 + ((Height(head->left)>Height(head->right))?Height(head->left):Height(head->right));
		
		int bal = GETBALANCE(head);
		
		if(bal > 1 && GETBALANCE(head->left)>=0)return RIGHTROTATE(head);
		if(bal < -1 && GETBALANCE(head->right)<=0)return LEFTROTATE(head);
		if(bal >1 && GETBALANCE(head->left)<0){
			head->left = LEFTROTATE(head->left);
			return RIGHTROTATE(head);
		}
		
		if(bal < -1 && GETBALANCE(head->right)>0){
			head->right = RIGHTROTATE(head->right);
			return LEFTROTATE(head); 
		}
		
		return head;
	
	

}




int IsAVL(struct node* A){
	if(A== NULL)return 1;
	if(GETBALANCE(A) > 1 || GETBALANCE(A) < -1 )return 0;
	return IsAVL(A->left);
	return IsAVL(A);
	return IsAVL(A->right);
}

void PRINTTREE(struct node* A){
	if(A == NULL){
		printf("( )");
		return;
	}
	printf("(");
	printf(" %d ",A->key);
	PRINTTREE(A->left);
	printf(" ");
	PRINTTREE(A->right);
	printf(" )");
}

void main(){
	struct node* head = NULL;
	char x;
	int k;
	while(1){
	scanf("%c",&x);
	if(x=='i'){
		scanf("%d",&k);
		head = INSERT(head,k);
	}
	if(x=='d'){
		scanf("%d",&k);
		struct node* search = SEARCH(head,k);
		if(search == NULL)printf("FALSE");
		else{
		printf("%d",k);
		head = DELETENODE(head,k);
		}printf("\n");
	}
	if(x=='s'){
		scanf("%d",&k);
		struct node* search = SEARCH(head,k);
		if(search == NULL)printf("FALSE");
		else printf("TRUE");
		printf("\n");
	}
	if(x=='b'){
		scanf("%d",&k);
		struct node* search = SEARCH(head,k);
		if(search == NULL){printf("FALSE");
		printf("\n");}
		else{
		printf("%d\n",GETBALANCE(search));}
		
	}
	if(x=='p'){PRINTTREE(head);
		printf("\n");}
	if(x=='e'){break;}
	}
}
