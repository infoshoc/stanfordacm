#include <iostream>
#include <cstdio>
#include <ext/rope> //header with rope
using namespace std;
using namespace __gnu_cxx; //namespace with rope

int main()
{
    ios_base::sync_with_stdio(false);
    rope <int> v; //use as usual STL container
    rope <int> vv(n, 0); //rope <int> v(n) builds rope from single elemet n!!
    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; ++i)
        v.push_back(i); //initialization
        vv.mutable_reference_at(i) = i + 1;

    int l, r;

    for(int i = 0; i < m; ++i)
    {
        cin >> l >> r;
        --l, --r;
        rope <int> cur = v.substr(l, r - l + 1); //SubRope
        v.erase(l, r - l + 1); // Erase
        v.insert(v.mutable_begin(), cur); //Push Front
    }

    for(rope <int>::iterator it = v.mutable_begin(); it != v.mutable_end(); ++it) // Iteration
        cout << *it << " ";

    return 0;
}


