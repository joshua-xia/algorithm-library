#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;

const int MAXN = 500050;

/**
* ֧�������޸ĵ���״���� (1)
* ����汾���������������һ��Ч�ʱȽϸߵİ汾������ԭ�����ӽ� BIT �� 
* @date 2017/11/3 11:14
*/
struct IntervalBIT {
    int n;
    
    LL a[MAXN], c[MAXN];    // c[] �� a[] �Ĳ������ 
    
    // ��ʼ�� 
    void init(int t) {
        n = t;
        memset(a, 0, sizeof a);
        memset(c, 0, sizeof c);
    }
    
    // ��״���� lowbit() ���� 
    int lowbit(int x)
    {
        return x & (-x);
    }
    
    /**
    * �޸����� 
    * @param long long* arr Ҫ�޸ĵ����� 
    * @param int pos �޸ĵ�λ��
    * @param long long addVal �޸ĵ�ֵ 
    */ 
    void add(LL* arr, int pos, LL addVal) {
        while (pos <= n)
        {
            arr[pos] += addVal;
            pos += lowbit(pos);
        }
    }
    
    /**
    * ��ĳһ���������Ͳ��� 
    * @param long long* arr Ҫ��͵����� 
    * @param int pos ǰ׺�͵��յ�
    * @return long long �������� arr ������� [1, pos] �Ľ�� 
    */ 
    LL sum(LL* arr, int pos) {
      LL res = 0;
      while (pos > 0)
      {
          res += arr[pos];
          pos -= lowbit(pos);
      }
      return res;
    }
    
    /**
    * ������������в�ּ���� 
    * @param int pos λ�� 
    * @return long long  
    */
    LL sigma(int pos) {
        LL sum1 = pos * sum(a, pos),
           sum2 = sum(c, pos);
        return sum1 - sum2;
    }
    
    /**
    * �����ѯ 
    * @param int x �½� 
    * @param int y �Ͻ�
    * @return long long ���ز�ѯ�Ľ�� 
    */
    LL query(int x, int y) {
        return sigma(y) - sigma(x - 1);
    }
};

/*
ʳ�÷�����
(1)�����޸ģ�tree.add(tree.a, pos, data[pos] - data[pos-1], tree.add(tree.c, pos, (i-1)*(data[i] - data[i-1]);
(2)�����޸�[x, y] + k��
    tree.add(tree.a, x, k), tree.add(tree.a, y+1, -k);
    tree.add(tree.c, x, (x-1) * k), tree.add(tree.c, y+1, -y*k);
(3)�����ѯ[x, y]: tree.query(x, y);
(4)�����ѯ x: tree.query(x, x);
*/ 

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
        tree.add(tree.a, i, data[i] - data[i-1]);
        tree.add(tree.c, i, (i - 1) * (data[i] - data[i-1]));
    }
    for (int i = 1; i <= m; i++)
    {
        int x, y, cmds;
        LL val;
        
        scanf("%d", &cmds);
        if (cmds == 1) {
            scanf("%d%d%lld", &x, &y, &val);
            tree.add(tree.a, x, val);
            tree.add(tree.a, y + 1, -val);
            tree.add(tree.c, x, (x - 1) * val);
            tree.add(tree.c, y + 1, -(y * val));
        } else {
            scanf("%d", &x);
            LL ans = tree.query(x, x);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
