#include "ada-hw4-p3.h"
#include <stdio.h>
#include <set>

// feel free to use global variables
std::vector<int> contest;
std::vector<int> choose_contest;
std::vector<std::pair<int, int>> rm_pair;
std::vector<int> ret;

void construct() {
    ret.clear();
    for (auto p:rm_pair) {
        ret.push_back(p.first);
        ret.push_back(p.second);
    }
}

std::vector<int> init(int N) {
    contest.resize(N);
    choose_contest.clear();
    rm_pair.clear();
    for (int i = 0; i < N; ++i) {
        contest[i] = i;
        if (choose_contest.empty() || compare(choose_contest.back(), i)) {
            choose_contest.push_back(i);
        }
        else {
            ret.push_back(choose_contest.back());
            ret.push_back(i);
            rm_pair.push_back(std::pair{choose_contest.back(), i});
            choose_contest.pop_back();
        }
    }
    construct();
    return ret;
}

std::vector<int> insert(int p, int id) {
    int flag = 0;
    int contest_sz = contest.size();
    int rt_sz = choose_contest.size();
    for (int i = p - 1; i >= 0; i--) {
        for (int j = 0; j < rt_sz; j++) {
            if (contest[i] == choose_contest[j]) {
                if (!compare(choose_contest[j], id)) {
                    rm_pair.push_back(std::pair{choose_contest[j], id});
                    choose_contest.erase(choose_contest.begin() + j);
                    contest.insert(contest.begin() + p, id);
                    construct();
                    return ret;
                }
                flag = 1;
                break;
            }
        }
        if (flag) break;
    }
    flag = 0;
    for (int i = p; i < contest_sz; i++) {
        for (int j = 0; j < rt_sz; j++) {
            if (contest[i] == choose_contest[j]) {
                if (!compare(id, choose_contest[j])) {
                    rm_pair.push_back(std::pair{id, choose_contest[j]});
                    choose_contest.erase(choose_contest.begin() + j);
                    contest.insert(contest.begin() + p, id);
                    construct();
                    return ret;
                }
                flag = 1;
                break;
            }
        }
        if (flag) break;
    }
    contest.insert(contest.begin() + p, id);
    choose_contest.push_back(id);
    construct();
    return ret;
}

std::vector<int> remove(int p) {
    int sz, ins_p, ins_id;
    sz = choose_contest.size();
    for (int i = 0; i < sz; i++) {
        if (choose_contest[i] == contest[p]) {
            contest.erase(contest.begin() + p);
            choose_contest.erase(choose_contest.begin() + i);
            construct();
            return ret;
        }
    }
    sz = rm_pair.size();
    for (int i = 0; i < sz; i++) {
        if (rm_pair[i].first == contest[p]) {
            contest.erase(contest.begin() + p);
            ins_id = rm_pair[i].second;
            sz = contest.size();
            for (int j = 0; j < sz; j++) {
                if (ins_id == contest[j]) {
                    ins_p = j;
                    contest.erase(contest.begin() + j);
                    break;
                }
            }
            rm_pair.erase(rm_pair.begin() + i);
            return insert(ins_p, ins_id);
        }
        else if (rm_pair[i].second == contest[p]) {
            contest.erase(contest.begin() + p);
            ins_id = rm_pair[i].first;
            sz = contest.size();
            for (int j = 0; j < sz; j++) {
                if (ins_id == contest[j]) {
                    ins_p = j;
                    contest.erase(contest.begin() + j);
                    break;
                }
            }
            rm_pair.erase(rm_pair.begin() + i);
            return insert(ins_p, ins_id);
        }
    }
    construct();
    return ret;
}
