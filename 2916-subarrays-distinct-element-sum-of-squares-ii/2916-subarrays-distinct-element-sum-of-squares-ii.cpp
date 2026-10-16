
class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const long long MOD = 1000000007;
        int n = nums.size();

        vector<long long> tree(4 * n, 0);
        vector<long long> lazy(4 * n, 0);
        vector<long long> sq(4 * n, 0);

        auto push = [&](int node, int l, int r) {
            if (lazy[node] == 0) return;

            long long len = r - l + 1;
            long long d = lazy[node];

            sq[node] = (sq[node] + 2LL * d * tree[node] % MOD
                       + len * d % MOD * d % MOD) % MOD;
            tree[node] = (tree[node] + len * d) % MOD;

            if (l != r) {
                lazy[node * 2] = (lazy[node * 2] + d) % MOD;
                lazy[node * 2 + 1] = (lazy[node * 2 + 1] + d) % MOD;
            }

            lazy[node] = 0;
        };

        auto update = [&](auto&& self, int node, int l, int r,
                          int ql, int qr) -> void {
            push(node, l, r);

            if (qr < l || r < ql) return;

            if (ql <= l && r <= qr) {
                lazy[node] = (lazy[node] + 1) % MOD;
                push(node, l, r);
                return;
            }

            int mid = l + (r - l) / 2;
            self(self, node * 2, l, mid, ql, qr);
            self(self, node * 2 + 1, mid + 1, r, ql, qr);

            tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
            sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
        };

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int left = last[nums[i]] + 1;
            update(update, 1, 0, n - 1, left, i);
            last[nums[i]] = i;
            ans = (ans + sq[1]) % MOD;
        }

        return (int)ans;
    }
};
