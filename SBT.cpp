#include <iostream>
using namespace std;

typedef struct node{
    int key, size;
    struct node * left, * right;

    node(const int k, const int s):key(k), size(s),
        left(NULL), right(NULL){};
} node, * pnode;

//左旋
void LeftRotate(pnode & T)
{
    pnode X = T->right;
    T->right = X->left;
    X->left = T;
    X->size = T->size;
    T->size = 1;
    if(T->left)
        T->size += T->left->size;
    if(T->right)
        T->size += T->right->size;
    T = X;
}

//右旋
void RightRotate(pnode & T)
{
    pnode X = T->left;
    T->left = X->right;
    X->right = T;
    X->size = T->size;
    T->size = 1;
    if(T->left)
        T->size += T->left->size;
    if(T->right)
        T->size += T->right->size;
    T = X;
}

void Maintain(pnode & T, bool flag)
{
    int l = T->left ? T->left->size : 0;
    int r = T->right ? T->right->size : 0;
    if(T == NULL)
        return;
    if(!flag)
    {
        int ll = 0, lr = 0;
        if(T->left)
        {
            ll = T->left->left ? T->left->left->size : 0;
            lr = T->left->right ? T->left->right->size : 0;
        }

        if(r < ll)
            RightRotate(T);
        else if(r < lr)
        {
            LeftRotate(T->left);
            RightRotate(T);
        }
        else return;
    }
    else
    {
        int rl = 0, rr = 0;
        if(T->right)
        {
            rl = T->right->left ? T->right->left->size : 0;
            rr = T->right->right ? T->right->right->size : 0;
        }

        if(l < rr)
            LeftRotate(T);
        else if(l < rl)
        {
            RightRotate(T->right);
            LeftRotate(T);
        }
        else return;
    }
    Maintain(T->left, false);
    Maintain(T->right, true);
    Maintain(T, false);
    Maintain(T, true);
}

void Insert(pnode & T, int key)
{
    if(T == NULL)
    {
        T = new node(key, 1);
    }
    else
    {
        T->size += 1;
        if(key < T->key)
            Insert(T->left, key);
        else
            Insert(T->right, key);

        Maintain(T, key >= T->key);
    }
}

int Delete(pnode & T, int key)
{
    T->size --;
    if(key == T->key || (key < T->key && T->left == NULL) 
        || (key > T->key && T->right == NULL))
    {
        int ret = T->key;

        if(T->left == NULL || T->right == NULL)
        {
            pnode temp = T;
            if(T->left != NULL)
                T = T->left;
            else if(T->right != NULL)
                T = T->right;
            else
            {
                delete T;
                T = NULL;
             }

             if(T)
             {
                delete temp;
                temp = NULL;
             }
        }
        else
        {
            T->key = Delete(T->left, T->key + 1);
        }

        return ret;
    }
    else
    {
        if(key < T->key)
            return Delete(T->left, key);
        else
            return Delete(T->right, key);
    }

    // Maintain(T, false);
    // Maintain(T, true);
}

int findKth(pnode T, int key)
{
    if(T == NULL || T->size < key)
        return -1;
    else
    {
        int l = T->left ? T->left->size : 0;
        int r = T->right ? T->right->size : 0;
        if(key == l + 1)
            return T->key;
        else if(key <= l)
            return findKth(T->left, key);
        else 
            return findKth(T->right, key - l - 1);
    }
}

int main()
{
    int n, a, b;
    char c;
    pnode root = NULL;
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    getchar();

    while(n --)
    {   
        scanf("%c %d", &c, &a);
        getchar();
        if(c == 'I')
        {
            Insert(root, a);
        }
        else if(c == 'Q')
        {
            printf("%d\n", findKth(root, a));
        }
        else if(c == 'D')
        {
            b = Delete(root, a);
            if(b != a)
                Insert(root, b);
            else
                printf("Delete %d\n", a);
        }
    }

    return 0;
}

