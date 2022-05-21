#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cell1;
    double cell2;
    struct Item *next;
} Item;

typedef struct {
    Item* head;
    Item* tail;
    int size;
} Matrix;

Matrix* Create() {
    Matrix * m = malloc(sizeof(Matrix));
    m->head = m->tail= NULL;
    m->size = 0;
    return m;
}

void PushBack(Matrix* m, int cell1, double cell2) {
    Item* new = malloc(sizeof(Item));
    new->cell1 = cell1;
    new->cell2 = cell2;
    new->next = NULL;
    Item *tmp = (Item *) m->tail;
    m->tail = new;
    if (m->head == NULL)
        m->head = m->tail;
    else
        tmp->next = (struct Item *) m->tail;
    m->size++;
}

void Print(Matrix *m, int str, int stlb) {
    Item* temp = (Item *) m->head;
    int str1 = 0;
    for (int i = 0; i < m->size; i++) {
        printf("%d  %.1lf | ", temp->cell1, temp->cell2);
        temp = (Item *) temp->next;
    }

    int* z = calloc(str+1, sizeof(int));
    temp = (Item *) m->head;
    for (int i = 1; i < m->size; i++) {
        if (temp->cell1 == 0)
            str1 = (int)temp->cell2;
        else
            if (temp->cell2 != 0)
                z[str1]++;
        temp = (Item *) temp->next;
    }

    double sum = 0;
    int maxstr = 0;
    for (int i = 1; i <= str; i++) {
        if (z[i] > maxstr)
            maxstr = z[i];
    }

    printf("\n");
    double matrix[str+1][stlb+1];
    for (int i = 1; i <= str; i++) {
        for (int j = 1; j <= stlb; j++) {
            matrix[i][j] = 0;
        }
    }
    temp = (Item *) m->head;
    for (int i = 0; i < m->size; i++) {
        if (temp->cell1 == 0)
            str1 = (int)temp->cell2;
        else
            matrix[str1][temp->cell1] = temp->cell2;
        temp = (Item *) temp->next;
    }
    for (int i = 1; i <= str; i++) {
        for (int j = 1; j <= stlb; j++) {
            printf("%10.2lf", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 1; i <= str; i++) {
        if (z[i] == maxstr) {
            int k = i;
            for (int j = 1; j <= stlb; j++) {
                sum = sum + matrix[k][j];
            }
            printf("Number: %d, sum: %.2lf\n", i, sum);
            sum = 0;
        }
    }

}

int main() {
    Matrix* m = Create();
    FILE *in = fopen("input.txt", "r");
    char n[] = "";
    char lll;
    char *b;
    double n1;
    int strNum = 1;
    int stlbNum = 1;
    PushBack(m, 0, strNum);
    strNum++;
    while (1) {
        fscanf(in,"%s", &n);
        fscanf(in,"%c", &lll);

        n1 = strtod(n,&b);
        if (n1 != 0) {
            PushBack(m, stlbNum, n1);
        }
        stlbNum++;
        if (lll == '\n') {
            PushBack(m, 0, strNum);
            strNum++;
            stlbNum = 1;
        }
        if (feof(in)) {
            PushBack(m, 0, 0);
            break;
        }
    }
    strNum--;
    stlbNum--;
    Print(m, strNum, stlbNum);
    fclose(in);
    return 0;
}
