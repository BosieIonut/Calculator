#include <stdio.h>
#include <stdlib.h>
#include "arbori.h"

Nod *create_tree(char val)
{
    Nod *tree;
    tree = (Nod*)malloc(sizeof(Nod));
    tree->left = NULL;
    tree->right = NULL;
    tree->val = val;
    return tree;
}

Stack *create_stack_node()
{
    Stack *stack;
    stack = (Stack*)malloc(sizeof(Stack));
    stack->value = NULL;
    return stack;
}
void afisare(Nod *a)
{
    if (a == NULL)
        return;
    afisare(a->left);
    printf("%c ", a->val);
    afisare(a->right);
}
Stack *push(Stack *stack, Nod *nod)
{
    Stack *c;
    c = create_stack_node();
    c->value = nod;
    if (stack == NULL)
        stack = c;
    else
    {
        c->next = stack;
        stack = c;
    }

    return stack;
}

Nod *pop(Stack **stack)
{
    Stack *c = NULL;
    Nod *d = NULL;
    if (*stack == NULL)
        return NULL;
    c = *stack;
    (*stack) = (*stack)->next;
    d = c->value;
    free(c);
    return d;
}

int rezultat(char *s, enum afis afisare)
{
    Nod *a = NULL;
    int lungime;
    a = calculator(s,&lungime);
    if(afisare == da)
        afisare_nebuna(a,0);
    return calcul(a);
}

Nod *calculator(char *s, int *skip)
{
    Stack *operatii = NULL, *operatori = NULL;
    int i = 0, sk;
    while (s[i] != '=' && s[i] != '\0' && s[i] != ')')
    {
        if (s[i] == '(')
        {
                operatori = push(operatori, calculator(s + i + 1,&sk));
                i+=sk+1;
        }
        else if(s[i] >= '0' && s[i] <= '9')
        {
            operatori = push(operatori, create_tree(s[i]));
        }
        else if (s[i] == '*' || s[i] == '/')
        {
            operatii = push(operatii, create_tree(s[i]));
        }
        else if (s[i] == '+' || s[i] == '-')
        {
           while(operatii && (operatii->value->val == '*' || operatii->value->val == '/'))
                {
                    Nod *aux;
                    aux = pop(&operatii);
                    aux->right = pop(&operatori);
                    aux->left = pop(&operatori);
                    operatori = push(operatori, aux);
                 }
            operatii = push(operatii, create_tree(s[i]));
        }
        i++;
    }
    Nod *aux;
    while (operatii)
    {
        aux = pop(&operatii);
        aux->right = pop(&operatori);
        aux->left = pop(&operatori);
        operatori = push(operatori, aux);
    }
    *skip = i;
    return operatori->value;
}

int calcul(Nod *a)
{
    if(a->left == NULL && a->right== NULL) 
        return (int)(a->val-'0');
    if(a->val == '+') return calcul(a->left) + calcul(a->right);
    if(a->val == '-') return calcul(a->left) - calcul(a->right);
    if(a->val == '*') return calcul(a->left) * calcul(a->right);
    if(a->val == '/') return calcul(a->left) / calcul(a->right);
}
void afisare_nebuna(Nod *node, int s)
{
    if(node == NULL)
        return;

    s += 10;
    
    afisare_nebuna(node->right, s);
    printf("\n");
    for(int i = 10; i < s; i++)
        printf(" ");
    printf("%c\n", node->val);
    
    afisare_nebuna(node->left, s);

}

Nod *calculator2(char *s, int *skip)
{
    Stack *operatii = NULL, *operatori = NULL;
    int i = 0, sk;
    while (s[i] != '=' && s[i] != '\0' && s[i] != ')')
    {
        if (s[i] == '(')
            {
                operatori = push(operatori, calculator(s + i + 1,&sk));
                i+=sk;
            }
        else
        {
            if (s[i] >= '0' && s[i] <= '9')
                operatori = push(operatori, create_tree(s[i]));
            else
            {
                if (s[i] == '*' || s[i] == '/')
                    operatii = push(operatii, create_tree(s[i]));

                if (s[i] == '+' || s[i] == '-')
                {

                    if ((operatii && (operatii->value->val == '+' || operatii->value->val == '-')) || !operatii)
                        operatii = push(operatii, create_tree(s[i]));

                    if (operatii && (operatii->value->val == '*' || operatii->value->val == '/'))
                    {
                        Nod *aux;
                        aux = pop(&operatii);
                        aux->left = pop(&operatori);
                        aux->right = pop(&operatori);
                        operatori = push(operatori, aux);
                        operatii = push(operatii, create_tree(s[i]));
                    }
                }
            }
        }
        i++;
    }
    while (operatii)
    {
        Nod *aux;
        aux = pop(&operatii);
        aux->left = pop(&operatori);
        aux->right = pop(&operatori);
        operatori = push(operatori, aux);
    }
    *skip = i;
    return operatori->value;
}

