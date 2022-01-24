#include <bits/stdc++.h>
#include <glpk.h>

namespace ypglpk{
  using std::vector,std::pair;
  bool output=0;
  constexpr double INF=1e300;
  // set whether to output verbose information about the solver (for debugging)
  void set_output(bool _output){
    output=_output;
  }
  // for interal usage. please do not call it unless you are really sure about what you are doing
  void set_constraints(glp_prob *P,const vector<vector<double>> &A,const vector<double> &b,const vector<double> &c){
    int n=c.size(),m=b.size();
    glp_set_obj_dir(P,GLP_MIN);
    glp_add_rows(P,m);
    glp_add_cols(P,n);
    for(int i=0;i<m;i++) glp_set_row_bnds(P,i+1,GLP_LO,b[i],INF);
    for(int i=0;i<n;i++) glp_set_col_bnds(P,i+1,GLP_LO,0,0);
    for(int i=0;i<n;i++) glp_set_obj_coef(P,i+1,c[i]);
    vector<int> ia(1),ja(1); vector<double> ar(1);
    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
        if(A[i][j]==0) continue;
        ia.push_back(i+1); ja.push_back(j+1);
        ar.push_back(A[i][j]);
      }
    }
    glp_load_matrix(P,(int)ia.size()-1,ia.data(),ja.data(),ar.data());
  }
  pair<double,vector<double>> mixed_integer_linear_programming(const vector<vector<double>> &A,const vector<double> &b,const vector<double> &c,const vector<bool> &isint){
    int n=c.size();
    glp_term_out(output?GLP_ON:GLP_OFF);
    glp_prob *milp=glp_create_prob();
    set_constraints(milp,A,b,c);
    for(int i=0;i<n;i++){
      if(isint[i]) glp_set_col_kind(milp,i+1,GLP_IV);
    }
    glp_iocp parm;
    glp_init_iocp(&parm);
    parm.presolve = GLP_ON;
    if(glp_intopt(milp,&parm)){
      glp_delete_prob(milp);
      return {-INF,{}};
    }
    vector<double> ans(n);
    for(int i=0;i<n;i++) ans[i]=glp_mip_col_val(milp,i+1);
    double opt=glp_mip_obj_val(milp);
    glp_delete_prob(milp);
    return {opt,ans};
  }
}

typedef struct {
    int arr[82];
    int sz;
}set;

int vertex_num, edge_num;
int edges[82][82];
std::vector<bool> vis(82);
std::vector<std::vector<double>> cliques;
std::vector<double> b;
std::vector<double> c;
std::vector<bool> isint;

set intersect(int v, set s) {
    for (int i = 0; i < vertex_num; ++i)
        if (s.arr[i] && !edges[v][i])
            s.arr[i] = 0, --s.sz;
    return s;
}

void BronchKerbosch(set r, set p, set x) {
    int pivot;
    if (p.sz == 0) {
        if (x.sz == 0)
            for (int i = 0; i < vertex_num; ++i)
                cliques[i].push_back(r.arr[i]);
        return;
    }
    for (pivot = 0; pivot < vertex_num; ++pivot)
        if (p.arr[pivot] || x.arr[pivot]) break;
    for (int i = 0; i < vertex_num; ++i) {
        if (p.arr[i] && !edges[pivot][i]) {
            r.arr[i] = 1, ++r.sz;
            BronchKerbosch(r, intersect(i, p), intersect(i, x));
            r.arr[i] = 0, --r.sz;
            p.arr[i] = 0, --p.sz;
            if (!x.arr[i]) x.arr[i] = 1, ++x.sz;
        }
    }
}

int main() {
    int T;
    int u, v;
    set r, p, x;
    int clique_sz;
    std::pair<double, std::vector<double>> get_lp;
    int ans_ptr;
    std::vector<int> ans[82];
    bool flag;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &vertex_num, &edge_num);
        cliques.resize(vertex_num);
        b.resize(vertex_num);
        fill(b.begin(), b.end(), 1);
        isint.resize(vertex_num);
        fill(isint.begin(), isint.end(), true);
        for (int i = 0; i < vertex_num; ++i) {
            cliques[i].clear();
            vis[i] = false;
            r.arr[i] = 0, p.arr[i] = 1, x.arr[i] = 0;
            memset(edges[i], 0, 82 * sizeof(int));
        }
        for (int i = 0; i < edge_num; ++i) {
            scanf("%d%d", &u, &v);
            edges[u][v] = 1;
            edges[v][u] = 1;
        }
        r.sz = 0, p.sz = vertex_num, x.sz = 0;
        BronchKerbosch(r, p, x);
        c.resize((*cliques.begin()).size());
        fill(c.begin(), c.end(), 1);
        isint.resize((*cliques.begin()).size());
        fill(isint.begin(), isint.end(), true);
        fill(vis.begin(), vis.end() + vertex_num, false);
        get_lp = ypglpk::mixed_integer_linear_programming(cliques, b, c, isint);
        clique_sz = get_lp.second.size();
        ans_ptr = 0;
        for (int i = 0; i < clique_sz; i++) {
            flag = false;
            if ((int)get_lp.second[i] == 1) {
                for (int j = 0; j < vertex_num; j++) {
                    if ((int)cliques[j][i] > 0 && !vis[j]) {
                        vis[j] = true;
                        if (flag) ans[ans_ptr - 1].push_back(j);
                        else {
                            flag = true;
                            ans_ptr += 1;
                            ans[ans_ptr - 1].clear();
                            ans[ans_ptr - 1].push_back(j);
                        }
                    }
                }
            }
        }
        printf("%d\n", ans_ptr);
        for (int i = 0; i < ans_ptr; i++) {
            printf("%ld ", ans[i].size());
            for (auto v: ans[i]) printf("%d ", v);
            putchar('\n');
        }
    }
    return 0;
}
