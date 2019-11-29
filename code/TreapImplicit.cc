struct item {
    int cnt, value, prior;
    item * l, * r;
    item() { }
};
typedef item * pitem;

int cnt (pitem t) {
    return t ? t->cnt : 0;
}

void upd_cnt (pitem t) {
    if (t) {
        t->cnt = 1 + cnt(t->l) + cnt (t->r);
    }
}

void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt (t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    int cur_key = add + cnt(t->l); // вычисляем неявный ключ
    if (key <= cur_key)
        split (t->l, l, t->l, key, add),  r = t;
    else
        split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt (t);
}

void insert (pitem & t, int pos, pitem new_item) {
    pitem t1, t2;
    split(t, t1, t2, pos);
    merge(t1, t1, new_item);
    merge(t, t1, t2);
}

void erase (pitem & t, int pos) {
    if (pos == cnt(t->l))
        merge (t, t->l, t->r);
    else
        erase (pos < cnt(t->l) ? t->l : t->r, pos < cnt(t->l) ? pos : pos - cnt(t->l) - 1);
}
