typedef struct nod Nod;
struct nod
{
    char val;
    Nod *left, *right;
};
enum afis
{
    da,
    nu
};
typedef struct stiva Stack;
struct stiva
{
    Nod *value;
    Stack *next;
};

void afisare(Nod *a);
Nod *pop(Stack **stack);
Stack *push(Stack *stack, Nod *nod);
Stack *create_stack_node();
Nod *create_tree(char val);
Nod *calculator(char s[], int *skip);
void afisare_nebuna(Nod *, int);
int calcul(Nod *a);
int rezultat(char *s, enum afis afisare);