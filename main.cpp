#include <iostream>

#define MAX_N (int)(1e5 + 1)
int *tree, *lazy;

int get(int start, int end, int index, int const &l, int const &r)
{
    if (lazy[index])
    {
        tree[index] += lazy[index] * (end - start + 1);
        if (start != end)
        {
            lazy[index * 2] += lazy[index];
            lazy[index * 2 + 1] += lazy[index];
        }
        lazy[index] = 0;
    }
    if (start > r || end < l)
        return 0;
    if (start >= l && end <= r)
        return tree[index];
    int mid = (start + end) / 2;
    return std::max(get(start, mid, index * 2, l, r), get(mid + 1, end, index * 2 + 1, l, r));
}

void update(int start, int end, int index, int const &l, int const &r)
{
    if (start > r || end < l)
        return;
    if (start >= l && end <= r)
    {
        tree[index] += (start - end + 1);
        if (start != end)
        {
            lazy[index * 2]++;
            lazy[index * 2 + 1]++;
        }
        return;
    }
    int mid = (start + end) / 2;
    update(start, mid, index * 2, l, r);
    update(mid + 1, end, index * 2 + 1, l, r);
    tree[index] = std::max(tree[index * 2], tree[index * 2 + 1]);
}

int main()
{
    int q, x, w, t, tests;
    std::cin >> tests;
    int len = 3 * MAX_N;
    while (tests--)
    {
        std::cin >> q;
        tree = (int *)calloc(len, sizeof(int));
        lazy = (int *)calloc(len, sizeof(int));
        while (q--)
        {
            std::cin >> w >> x;
            t = get(1, MAX_N, 1, x, x);
            if (t == get(1, MAX_N, 1, x + w, x + w) && t >= get(1, MAX_N, 1, x, x + w))
            {
                std::cout << "YES\n";
                update(1, MAX_N, 1, x, x + w);
            }
            else
            {
                std::cout << "NO\n";
            }
        }
    }
    return 0;
}
