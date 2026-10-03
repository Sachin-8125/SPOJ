#include <cstdio>
#include <cstring>

struct Node {
    char op, var;
    Node *left, *right;
};

char expr[256];
int pos;
char buf[1024];
int bpos;

Node* parseE(); Node* parseT(); Node* parseF();

Node* mk(char op, char var, Node* l, Node* r) {
    Node* n = new Node(); n->op=op; n->var=var; n->left=l; n->right=r; return n;
}

Node* parseE() {
    Node* left = parseT();
    while (expr[pos]=='+' || expr[pos]=='-') {
        char op = expr[pos++];
        left = mk(op, 0, left, parseT());
    }
    return left;
}

Node* parseT() {
    Node* left = parseF();
    while (expr[pos]=='*' || expr[pos]=='/') {
        char op = expr[pos++];
        left = mk(op, 0, left, parseF());
    }
    return left;
}

Node* parseF() {
    if (expr[pos]=='(') { pos++; Node* n = parseE(); pos++; return n; }
    return mk(0, expr[pos++], 0, 0);
}

int prec(char op) {
    if (op=='+' || op=='-') return 1;
    if (op=='*' || op=='/') return 2;
    return 0;
}

void emit(Node* n, char pop, bool isRight) {
    if (!n->op) { buf[bpos++] = n->var; return; }
    bool need = false;
    if (pop) {
        int mp = prec(n->op), pp = prec(pop);
        if (mp < pp) need = true;
        else if (mp == pp && isRight && (pop=='-' || pop=='/')) need = true;
    }
    if (need) buf[bpos++] = '(';
    emit(n->left, n->op, false);
    buf[bpos++] = n->op;
    emit(n->right, n->op, true);
    if (need) buf[bpos++] = ')';
}

void freeTree(Node* n) { if(!n) return; freeTree(n->left); freeTree(n->right); delete n; }

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", expr);
        pos = 0;
        Node* root = parseE();
        bpos = 0;
        emit(root, 0, false);
        buf[bpos] = 0;
        printf("%s\n", buf);
        freeTree(root);
    }
}