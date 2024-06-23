#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

int node_data[2000];
struct node{
    int data;
    struct node *left, *right;
};

struct node* newNode (int data){
    struct node* temp = (struct node *) malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* constructTree1(int post[], int* postIndex,int data, int min, int max,int nodenum){
    if (*postIndex < 0)
        return NULL;
    struct node* root = NULL;
    if (data > min && data < max){
        root = newNode(data);
        *postIndex = *postIndex - 1;
        if (*postIndex >= 0){
            root->right = constructTree1(post, postIndex,post[*postIndex],data, max, nodenum);
            root->left = constructTree1(post, postIndex,post[*postIndex],min, data, nodenum);
        }
    }
    return root;
}

struct node *constructTree (int post[],int nodenum){
    int postIndex = nodenum-1;
    return constructTree1(post, &postIndex,post[postIndex],-2000, 2000, nodenum);
}

int cnt = 0;
void printPreorder (struct node* node){
    if (node == NULL)
        return;
    node_data[cnt] = node->data;
    cnt++;
	printPreorder(node->left);
    printPreorder(node->right);
}

int findHeight1(node* root, int tar,int& height){
    if (root == NULL) {
        return -1;
    }
    int leftHeight = findHeight1(root->left, tar, height);
    int rightHeight= findHeight1(root->right, tar, height);
    int ans = max(leftHeight, rightHeight) + 1;  
    if (root->data == tar)
        height = ans;
    return ans;
}

int findHeight(node* root, int tar){
    int h = -1;
    int maxHeight = findHeight1(root, tar, h);
    return h;
}

int heightmax[2000];
void findmax(node* root,int currentheight,int &printnum){
    if(root==NULL){
        return;
    }
    if(currentheight>printnum){
        heightmax[printnum] = root->data;
        printnum++;
    }
    findmax(root->right,currentheight+1,printnum);
    findmax(root->left,currentheight+1,printnum);
}

int main(int argc, char *argv[]){
    ifstream infile; 
    infile.open(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);
    // TODO: Please code here
	int BSTnum;
	infile>>BSTnum;
	for(int j = 0;j<BSTnum;j++){
        int nodenum;
    	infile>>nodenum;
		int post[nodenum];	
		for(int i = 0;i<nodenum;i++){	
    		infile>>post[i];
		}
    	struct node *root = constructTree(post,nodenum);
    	printPreorder(root);
        for(int i = 0;i<nodenum;i++){
            outfile<<node_data[i]<<" ";
        }
    	outfile<<endl;
    	int maxheight = findHeight(root, post[nodenum-1])+1;
        outfile<<maxheight<<endl;
        int printnum = 0;
        findmax(root,1,printnum);
        for(int i = 0;i<maxheight;i++){
            outfile << heightmax[i]<<endl;
        }
        cnt = 0;
    }
    infile.close();
    outfile.close();   
}


