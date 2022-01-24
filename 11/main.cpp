// discussion: b09902008, b09902010
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    long long val;
    int idx;
    struct Node *nxt;
}Node;

int main() {
    int T, flag;
    int N;
    long long tmp0, tmp1;
    int s0_ptr;
    long long s0[100000];
    Node *pos, *neg, *n_tmp;
    scanf("%d%d", &T, &flag);
    while (T--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%lld", &(s0[i]));
        }
        pos = NULL, neg = NULL, tmp0 = 0, tmp1 = 0;
        for (int i = 0; i < N; i++) {
            if (s0[i] > 0) {
                if (pos) {
                    if (s0[i] > pos->val) {
                        tmp0 += s0[i] - pos->val;
                        n_tmp = (Node *)malloc(sizeof(Node));
                        n_tmp->val = s0[i];
                        n_tmp->idx = i + 1;
                        n_tmp->nxt = pos->nxt;
                        pos = n_tmp;
                    }
                }
                else {
                    tmp0 = s0[i];
                    pos = (Node *)malloc(sizeof(Node));
                    pos->val = s0[i];
                    pos->idx = i + 1;
                    pos->nxt = NULL;
                }
                if (s0[i] + tmp1 > tmp0) {
                    tmp0 = s0[i] + tmp1;
                    pos = (Node *)malloc(sizeof(Node));
                    pos->val = s0[i];
                    pos->idx = i + 1;
                    pos->nxt = neg;
                }
            }
            else {
                if (neg) {
                    if (s0[i] > neg->val) {
                        tmp1  += s0[i] - neg->val;
                        n_tmp = (Node *)malloc(sizeof(Node));
                        n_tmp->val = s0[i];
                        n_tmp->idx = i + 1;
                        n_tmp->nxt = neg->nxt;
                        neg = n_tmp;
                    }
                }
                else {
                    tmp1 = s0[i];
                    neg = (Node *)malloc(sizeof(Node));
                    neg->val = s0[i];
                    neg->idx = i + 1;
                    neg->nxt = NULL;
                }
                if (s0[i] + tmp0 > tmp1) {
                    tmp1 = s0[i] + tmp0;
                    neg = (Node *)malloc(sizeof(Node));
                    neg->val = s0[i];
                    neg->idx = i + 1;
                    neg->nxt = pos;
                }
            }
        }
        if (pos) {
            printf("%lld\n", tmp0);
            if (flag) {
                s0_ptr = 0;
                while (pos) {
                    s0[s0_ptr++] = pos->idx;
                    pos = pos->nxt;
                }
                printf("%d", s0_ptr);
                for (int i = s0_ptr - 1; i >= 0; i--) {
                    printf(" %lld", s0[i]);
                }
                printf("\n");
            }
        }
        else {
            printf("%lld\n", tmp1);
            if (flag) {
                s0_ptr = 0;
                while (neg) {
                    s0[s0_ptr++] = neg->idx;
                    neg = neg->nxt;
                }
                printf("%d", s0_ptr);
                for (int i = s0_ptr - 1; i >= 0; i--) {
                    printf(" %lld", s0[i]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}
