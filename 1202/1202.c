#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree {
    int data;
    struct tree *Left;
    struct tree *back;
    struct tree *Right;
}treeNode;

treeNode *newNode(int key, treeNode *back){
    treeNode * node;
    node = malloc(sizeof(treeNode));
    node->data = key;
    node->back = back;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

void Preorder(treeNode *ptr){
    if(ptr != NULL){
        printf("%d ",ptr->data);
        Preorder(ptr->Left);
        Preorder(ptr->Right);
    }
}

treeNode *searchnum(treeNode *root, int tmp){
    treeNode *now;
    now = root;
    while(1){
        if(tmp > now->data){
            if(now->Right == NULL){
                now->Right = newNode(tmp, now);
                break;
            }
            else{
                now = now->Right;
            }
        }
        else if(tmp == now->data){
            printf("%d  already exist.\n");
            break;
        }
        else{
            if(now->Left == NULL){
                now->Left = newNode(tmp, now);
                break;
            }
            else{
                now = now->Left;
            }
        }
    }
    return root;
}
treeNode *insertdata(treeNode *root, int tmp){
    treeNode *now;
    if(root == NULL){
        root = malloc(sizeof(treeNode));
        root->data = tmp;
        root->Left = NULL;
        root->Right = NULL;
    }
    else{
        root = searchnum(root, tmp);
    }
    return root;
}

treeNode *del(treeNode *root, int tmp){
    treeNode *now;
    int flag = 0;
    treeNode *temp;
    if(root == NULL){
        printf("The tree is empty!\n");
    }
    else{
        now = root;
        while(1){
            if(tmp > now->data){
                if(now->Right == NULL){
                    printf("%d does not exist.\n", tmp);
                    break;
                }
                else{
                    now = now->Right;
                }
            }
            else if(tmp < now->data){
                if(now->Left == NULL){
                    printf("%d does not exist.\n", tmp);
                    break;
                }
                else{
                    now = now->Left;
                }
            }
            else{ //?????????????????????
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            if(now->Left == NULL && now->Right == NULL){ //???????????????
                if(now->data > now->back->data){ //?????????????????????
                    now->back->Right = NULL;
                    free(now);
                }
                else{ //?????????????????????
                    now->back->Left = NULL;
                    free(now);
                }
            }
            else if(now->Left != NULL && now->Right != NULL){ //???????????????
                temp = now->Left;
                if(temp->Right == NULL){ //temp????????????
                    now->data = temp->data;
                    if(temp->Left != NULL){
                        now->Left = temp->Left;
                        now->Left->back = now;
                    }
                    else{
                        now->Left = NULL;
                    }
                    free(temp);
                }
                else{ //temp????????????
                    while(1){
                        temp = temp->Right;
                        if(temp->Right == NULL){
                            break;
                        }
                    }
                    now->data = temp->data;
                    if(temp->Left != NULL){
                        temp->back->Right = temp->Left;
                        temp->Left->back = temp->back;
                    }
                    else{

                        temp->back->Right = NULL;
                    }
                    free(temp);
                }
            }
            else{ //??????????????????
                if(now->Left == NULL){ //????????????
                    if(now == root){
                        root = now->Right;
                    }
                    else if(now->data > now->back->data){ //?????????????????????
                        now->back->Right = now->Right;
                        now->Right->back = now->back;
                    }
                    else{
                        now->back->Left = now->Right;
                        now->Right->back = now->back;
                    }
                }
                else{ //????????????
                    if(now == root){
                        root = now->Left;
                    }
                    else if(now->data > now->back->data){ //?????????????????????
                        now->back->Right = now->Right;
                        now->Right->back = now->back;
                    }
                    else{
                        now->back->Left = now->Right;
                        now->Right->back = now->back;
                    }
                }
            }
        }
    }
    return root;
}

int main(){
    FILE *fp = fopen("input.txt","r");
    if(fp == NULL){
        printf("NO~~~~~\n");
    }
    int tmp;
    int menu;
    int flag = 0;
    treeNode *root = NULL, *now;
    while(fscanf(fp, "%d %d", &menu, &tmp) != EOF){
        flag = 0;
        printf("[1] Insert [2] Delete: %d\n", menu);

        if(menu == 1){
            printf("Insert a number : %d\n", tmp);
            root = insertdata(root, tmp);
        }
        else if(menu == 2){
            printf("Insert a number : %d\n", tmp);
            root = del(root, tmp);
        }
        else{
            flag = 1;
            printf("Please chose again!!\n\n");
        }
        if(flag == 0){
            Preorder(root);
            printf("\n\n");
        }
    }

}
