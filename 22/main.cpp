//discussion: b09902008, b09902010, b09902017, b09902060, b09902061
#include <bits/stdc++.h>

typedef struct node{
    struct node *par;
    long sz;
}node;

long crowdness = 0;
node* cat_pos[100010];
std::map<long, node*> pos;

node* find_node_par(node *n){
    if (!n) return n;
    return (n->par == n) ? n: (n = find_node_par(n->par));
}

void add_node(const long pos_idx, const long cat_idx) {
    node *par;
    auto iter = pos.find(pos_idx);
    par = find_node_par(cat_pos[cat_idx]);
    if (par) {
        crowdness -= par->sz * (par->sz - 1) / 2;
        par->sz -= 1;
        crowdness += par->sz * (par->sz - 1) / 2;
    }
    if (iter == pos.end()) {
        cat_pos[cat_idx] = (node *)malloc(sizeof(node));
        cat_pos[cat_idx]->par = cat_pos[cat_idx];
        cat_pos[cat_idx]->sz = 1; 
        pos[pos_idx] = cat_pos[cat_idx];
    }
    else {
        crowdness -= pos[pos_idx]->sz * (pos[pos_idx]->sz - 1) / 2;
        pos[pos_idx]->sz += 1;
        crowdness += pos[pos_idx]->sz * (pos[pos_idx]->sz - 1) / 2;
        cat_pos[cat_idx] = pos[pos_idx];
    }
}

void attract(const long pos_idx, const long r) {
    auto low = pos.lower_bound(pos_idx - r), up = pos.upper_bound(pos_idx + r);
    node *tmp, *tmp0, *tmp1;
    std::vector<long> s;
    if (low == up) return;
    tmp = (*low).second;
    for (auto iter = std::next(low); iter != up; iter++) {
        tmp0 = (*iter).second;
        if (tmp->sz < tmp0->sz) {
            tmp1 = tmp0;
            tmp0 = tmp;
            tmp = tmp1;
        }
        crowdness -= tmp->sz * (tmp->sz - 1) / 2;
        crowdness -= tmp0->sz * (tmp0->sz - 1) / 2;
        tmp->sz += tmp0->sz;
        tmp0->par = tmp;
        crowdness += tmp->sz * (tmp->sz - 1) / 2;
    }
    pos.erase(low, up);
    pos[pos_idx] = tmp;
}

int main() {
    int N, Q, cmd;
    long arg0, arg1;
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%ld", &arg0);
        add_node(arg0, i);
    }
    while (Q--) {
        scanf("%d%ld%ld", &cmd, &arg0, &arg1);
        if (cmd == 1) attract(arg0, arg1);
        else add_node(arg1, arg0);
        printf("%ld\n", crowdness);
    }
    return 0;
}
