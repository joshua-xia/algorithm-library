#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;

const int MAXN = 500050;

/**
* ֧�������޸ĵ���״���� (2)
* ����汾����ԭ�����ӽ� BIT �ֻ����״����ά��������� 
* Ч�ʱȽϸ�Ҳ��д��������Ե���˵һЩ���������ѯ�Ĳ��������Ը��� 
* ���ʵ�����״���黹��ԭ������״���飬ֻ��˼ά�е�仯
* ��ѯ��ʱ����ԭֵ����������ֵ�Ϳ����ˣ���������˼�� 
* @date 2017/11/3 11:22
*/
struct IntervalBIT {
    int n;
    LL a[MAXN];
    
    void init(int t) {
        n = t;
        memset(a, 0, sizeof a);
    }
    
    int lowbit(int x)
    {
        return x & (-x);
    }
    
    void add(int pos, LL addVal) {
        while (pos <= n)
        {
            a[pos] += addVal;
            pos += lowbit(pos);
        }
    }
    
    LL sum(int pos) {
      LL res = 0;
      while (pos > 0)
      {
          res += a[pos];
          pos -= lowbit(pos);
      }
      return res;
    }
};

IntervalBIT tree;
int n, m;
LL data[MAXN];

int main()
{
    scanf("%d%d", &n, &m);
    tree.init(n);
    
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &data[i]);
    }
    
    for (int i = 1; i <= m; i++)
    {
        int x, y, cmds;
        LL val;
        
        scanf("%d", &cmds);
        if (cmds == 1) {
            scanf("%d%d%lld", &x, &y, &val);
            // ��Ϊ BIT ������ǰ׺�͵�˼�룬����ֱ�ӽ���ά��������м��� 
            tree.add(x, val);
            tree.add(y + 1, -val);
        } else {
            scanf("%d", &x);
            // �����ѯ��ʱ��������ԭ����+���ֵ 
            LL ans = data[x] + tree.sum(x);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
