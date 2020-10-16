#include <bits/stdc++.h>
using namespace std;
#define ll long double
#define inf 1e18

int comb(int n, int r)
{
    if (n < r)
    {
        return -1;
    }
    int k = min(n - r, r);
    int ans = 1;
    for (int i = 0; i < k; i++)
    {
        ans *= (n - i);
        ans /= (i + 1);
    }
    return ans;
}

ll binpow(ll a, int b)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main()
{
    ofstream myfile;
    myfile.open("181IT251_IT302_P7_Output_TC6.txt");
    ll a, b, n;
    cout << "Enter the vaue of a b and n \n";
    cin >> a >> b >> n;
    ll ans;
    a = a / 100.0;
    ans = comb(n, b);
    ll b1 = n - b;e5
    ll ans1 = pow(a, b);
    ll ans2 = pow(1 - a, b1);
    cout << ans * ans1 * ans2 << "\n";
    myfile << ans * ans1 * ans2 << "\n";

    myfile.close();
    return 0;
}
