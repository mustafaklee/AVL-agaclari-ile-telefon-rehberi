#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//avl ağacları kullanılarak telefon rehberi programı...

struct node {
	int telefonNo;
	char isim[100];
	int height;
	struct node *right;
	struct node *left;
};

void goruntule(struct node *tree){
	if(tree==NULL){
		return;
	}
	goruntule(tree->left);
	printf("%s - %d\n",tree->isim,tree->telefonNo);
	goruntule(tree->right);
}

struct node *NewNode (struct node *tree,int telefonNo,char isim[]){
	if(tree==NULL){
		struct node *root;	
		root=(struct node *)malloc(sizeof(struct node));
		strcpy(root->isim, isim);
		root->telefonNo=telefonNo;
		root->right=NULL;
		root->left=NULL;
		return root;
	}
	if(strcmp(tree->isim, isim) <0){
		tree->right=NewNode(tree->right,telefonNo,isim);
		return tree;
	}else{
		tree->left = NewNode(tree->left,telefonNo, isim);
	}
	
	return tree;
}

int maxValue2(int a , int b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}

int height(struct node *agac){
	if(agac==NULL){
		return -1;
	}
	else{
		int agac_left=0,agac_right=0;
		agac_left=height(agac->left);
		agac_right=height(agac->right);
		if(agac_left>agac_right){
			return agac_left +1;
		}
		else{
			return agac_right+1;
		}
	}
}

struct node *rightRotate(struct node *z) {
	struct node* temp = z -> left; 
	z -> left = temp -> right;
	temp->right = z;
	z -> height = maxValue2(height(z -> left), height(z -> right)) + 1;
	temp -> height = maxValue2 (height(temp -> left), height(temp -> right)) + 1;
	return temp;
}

struct node *leftRotate(struct node *z) {
    struct node *temp = z->right;
    z->right = temp->left;
    temp->left = z;
    z->height = maxValue2(height(z->left), height(z->right)) + 1;
    temp->height = maxValue2(height(temp->left), height(temp->right)) + 1;
    return temp; 
}

struct node *leftRightRotate(struct node *z) {
	z -> left = leftRotate(z -> left); 
	return rightRotate(z); 
}

struct node *rightLeftRotate(struct node *z) {
	z -> right = rightRotate(z -> right);
	return leftRotate(z); 
}

char *minValue(struct node *agac){
	if(agac==NULL){
		return NULL;
	}
	while(agac->left!=NULL){
		agac=agac->left;
	}
	
	return agac->isim;
}

struct node *RehbereKayit(struct node *tree,int telefonNo,char isim[]){
	if(tree != NULL){
		if(strcmp(isim, tree->isim) < 0) 
			tree -> left = RehbereKayit(tree->left,telefonNo,isim);
		else if(strcmp(isim, tree->isim) >0)
			tree -> right = RehbereKayit(tree->right,telefonNo,isim);
		else
			return tree; 
	
		tree -> height = maxValue2(height(tree->left), height(tree->right)) + 1;
		
		if((height(tree->left) - height(tree->right)) > 1 && strcmp(isim, tree->left->isim) < 0)
			return rightRotate(tree);
		
		if((height(tree->left) - height(tree->right)) > 1 && strcmp(isim, tree->right->isim) > 0)
			return leftRightRotate(tree);
		
		if((height(tree->left) - height(tree->right)) < -1 && strcmp(isim, tree->right->isim) > 0)
			return leftRotate(tree);
		
		if((height(tree->left) - height(tree->right)) < -1 && strcmp(isim, tree->left->isim) < 0)
			return rightLeftRotate(tree);
		}
	else{
		tree=NewNode(tree,telefonNo,isim);
	}
return tree;

}

int AraBul(struct node *tree,char ArananIsim[]){
	if(tree==NULL){
		return 0;
	}
	AraBul(tree->left,ArananIsim);
	if(strcmp(tree->isim,ArananIsim)==0){
		printf("%s kisisi bulundu : No:%d\n",tree->isim,tree->telefonNo);
		return 0;
	}
	AraBul(tree->right,ArananIsim);
}

int getBalance(struct node* origin) {
	if (origin == NULL)
		return 0;
	return height(origin ->left) - height(origin ->right);
}

struct node *deleteNode(struct node *root, char SilinecekKisi[]) {
	if(root == NULL)
		return root;
	if(strcmp(SilinecekKisi, root->isim) < 0) 
		root -> left = deleteNode(root -> left, SilinecekKisi);
	else if(strcmp(SilinecekKisi, root->isim) > 0) 
		root -> right = deleteNode(root -> right, SilinecekKisi);
	else { 
		if((root -> left == NULL) || (root -> right == NULL)) {
			struct node *temp = root -> left ? root -> left : root -> right;
			
			if(temp == NULL) { 
				temp = root;
				root = NULL;
			} else
				*root = *temp; 
			free(temp); 
		}
		else { 
			struct node *temp = minValue(root -> right);
			strcpy(root->isim, temp->isim);
			root -> right = deleteNode(root -> right, temp -> isim);
		}
	}
	if (root == NULL)
		return root;
		
	root -> height = maxValue2(height(root -> left), height(root -> right)) + 1;
	if (getBalance(root) > 1 && getBalance(root -> left) >= 0)
		return rightRotate(root);
	if (getBalance(root) > 1 && getBalance(root -> left) < 0) {
		root -> left = leftRotate(root -> left);
		return rightRotate(root); 
	}
	if (getBalance(root) < -1 && getBalance(root -> right) <= 0)
		return leftRotate(root); 
	if (getBalance(root) < -1 && getBalance(root -> right) > 0) {
		root -> right = rightRotate(root -> right); 
		return leftRotate(root); 
	}
	return root;
}

int main() {
	struct node *Bilgiler1=NULL;
	int cikis=0;
	
	printf("Yapmak istediginiz islemi seciniz : \n1-Rehbere Kayit etme\n2-Rehberde Arama yapma\n3-Rehberden numara silme\n4-Rehberi goruntuleme\n***Cikmak icin -1***");
	while(cikis!=-1){
		scanf("%d",&cikis);
		if(cikis==1){
			int telefonNo;
            char isim[100];
            printf("Isim girin: ");
            scanf("%s", isim);
            printf("Telefon numarasi girin: ");
            scanf("%d", &telefonNo);
			Bilgiler1=RehbereKayit(Bilgiler1,telefonNo,isim);
			printf("Kayit tamamlandi Simdi ne yapmak istersiniz?");
		}
		if(cikis==2){
			printf("Aramak istediğiniz kisinin ismini giriniz: ");
			char isim[100];
			scanf("%s",isim);
			AraBul(Bilgiler1,isim);
		}
		if(cikis==3){
			printf("Silmek istediginiz kisinin ismini giriniz: ");
			char isim[100];
			scanf("%s",isim);
			deleteNode(Bilgiler1,isim);
			printf("Silme islemi tamamlandi Simdi ne yapmak istersiniz?");
		}
		if(cikis==4){
			goruntule(Bilgiler1);
		}
	}
	return 0;
}