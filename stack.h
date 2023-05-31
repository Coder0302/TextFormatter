#include <stdlib.h>
struct StackStruct
{
    int countInStack;
    char *stack;
} Stack_default = {0};
typedef struct StackStruct Stack;

void push(Stack *st, char value)
{
    st->stack = (char *)realloc(st->stack, sizeof(char) * ++st->countInStack);
    st->stack[st->countInStack - 1] = value;
}

char pop(Stack *st)
{
    if (st->countInStack > 0)
    {
        char res = st->stack[st->countInStack - 1];
        st->stack = (char *)realloc(st->stack, sizeof(char) * --st->countInStack);
        return res;
    }
    return -1;
}
