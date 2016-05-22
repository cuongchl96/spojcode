#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i= a; i<= b; i++)
#define FORD(i,a,b) for(int i= a; i>= b; i--)
#define For(i,a,b) for(int i= a; i< b; i++)
#define Ford(i,a,b) for(int i= a; i> b; i--)
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
#define Fill(s,a) memset(s,a,sizeof(s));
#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef unsigned long long ull;

const int N = 100100;

struct line
{
    ll a, b;
};

int n, id[N];
ll B, sumA[N], sumB[N], sumBT[N], f[N], t[N], b[N], a[N];
line tree[8*N+10];

bool cmp(int a, int b)
{
    return t[a] < t[b];
}

ll get(line d, ll x)
{
    return d.a * x + d.b;
}

ll Query(int s, int l, int r, int x)
{
    if (l > x || r < x) return -1e15;
    ll res = get(tree[s],x);
    if (l == r) return res;

    int mid = (l + r) >> 1;
    res = max(res,Query(2*s,l,mid,x));
    res = max(res,Query(2*s+1,mid+1,r,x));
    return res;
}

void Update(int s, int l, int r, line d)
{
    if (get(tree[s],l) >= get(d,l) && get(tree[s],r) >= get(d,r)) return;

    if (get(tree[s],l) <= get(d,l) && get(tree[s],r) <= get(d,r))
    {
        tree[s] = d;
        return;
    }

    int mid = (l + r) >> 1;

    if (get(tree[s],l) >= get(d,l) && get(tree[s],mid) >= get(d,mid))
    {
        Update(2*s+1,mid+1,r,d);
        return;
    }

    if (get(tree[s],l) <= get(d,l) && get(tree[s],mid) <= get(d,mid))
    {
        Update(2*s+1,mid+1,r,tree[s]);
        tree[s] = d;
        return;
    }

    if (get(tree[s],mid+1) >= get(d,mid+1) && get(tree[s],r) >= get(d,r))
    {
        Update(2*s,l,mid,d);
        return;
    }

    if (get(tree[s],mid+1) <= get(d,mid+1) && get(tree[s],r) <= get(d,r))
    {
        Update(2*s,l,mid,tree[s]);
        tree[s] = d;
        return;
    }

}

int main()
{
    ios_base::sync_with_stdio(false);
    //freopen("test.inp","r",stdin);
    //freopen("test.out","w",stdout);
    cin >> n >> B;
    FOR(i,1,n)
    {
        cin >> t[i] >> a[i] >> b[i];
        id[i] = i;
    }

    sort(id+1,id+n+1,cmp);

    FOR(i,1,n)
    {
        sumA[id[i]] = sumA[id[i-1]] + a[id[i]];
        sumB[id[i]] = sumB[id[i-1]] + b[id[i]];
        sumBT[id[i]] = sumBT[id[i-1]] + b[id[i]] * t[id[i]];
    }
    FOR(i,1,n)
    {
        int x = id[i];
        f[x] = sumA[x] + sumBT[x] - t[x] * sumB[x] - B + Query(1,1,N,t[x]);
        Update(1,1,N,(line){sumB[x],f[x]-sumA[x]-sumBT[x]});
    }
    cout << f[id[n]] << endl;
    return 0;
}
