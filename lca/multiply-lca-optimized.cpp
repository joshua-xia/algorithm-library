/**
* ���ñ���˼���� LCA(Lowest Common Ancestor, �����������) 
* https://www.luogu.org/problem/show?pid=3379
*/ 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 * 5 + 10;
const int MAXLOG = 19;            // ���ݷ�Χ 50w, 2^19 ���� 

// �ִ��ڽӱ���Ϊ�� vector ����̫��ᳬʱ qwq 
struct Edge {
  int last;     // last ��ʾ�� u ���������һ����
  int next;     // next ��ʾ u �����ӵ���һ���� v 
};
Edge e[MAXN << 1];  // ����˫��ģ���������Ҫ����һ�� 

int n, m, s, cnt = 0;
int depth[MAXN];                  // depth[i] ��ʾ�ڵ� i ����� 
int G[MAXN];                      // G[i] ��ʾ�� i ���������һ���ߵ� index 
int ancestor[MAXN][MAXLOG + 5];   // ancestor[i][j] ��ʾ�� i ����ĵ� 2^j �����ȵı�� 
bool vis[MAXN];                   // DFS ���� 

/**
 * ��ߣ�ڽӱ�ӱ߲��� 
 * @param int u ��� 
 * @param int v �յ� 
 */ 
void addEdge(int u, int v)
{
  e[++cnt].next = v;
  e[cnt].last = G[u];
  G[u] = cnt;
}

/**
 * DFS Ԥ��������ÿһ����� ancestor[] ���飬��� depth[] ���� 
 * @param int root   ���
 * @param int dep    ��ǰ�ڵ����
 * @param int father ��ǰ�ڵ㸸�� 
 */ 
void dfs(int root, int dep, int father)
{
  ancestor[root][0] = father;       // i �ڵ�ĵ� 2^0 �����ȼ�Ϊ�丸�� 
  depth[root] = dep;
  vis[root] = 1;
  /* i �ڵ�ĵ� 2^j ������ = **i �ڵ�ĵ� 2^(j-1) ������** �ĵ� 2^(j-1) ������ */ 
  for (int i = 1; (1 << i) <= dep; i++)
  {
    ancestor[root][i] = ancestor[ancestor[root][i-1]][i-1];
  }
  
  // ���ڴӽڵ� root ������ÿ���ߣ��ݹ���� depth ���顢Ԥ���� ancestor 
  for (int i = G[root]; i; i = e[i].last)
  {
    int next = e[i].next;
    if (!vis[next]) {
      dfs(next, dep + 1, root);
    }
  }
}

/**
 * ��� LCA 
 * @param int x
 * @param int y
 */
int lca(int x, int y)
{
  // ����Լ�� x �ǽ������һ���ڵ㣬��� x �����С�� y �ͽ��� x, y 
  if (depth[x] < depth[y]) {
    swap(x, y);
  }
  
  // ������Ҫ�� x �ڵ������� y �ڵ�ͬһ���߶ȵĵط� 
  // �� delta ��ʾ x �� y ����Ȳ�� 0 ѭ���� MAXLOG 
  int delta = depth[x] - depth[y];
  for (int i = 0; i <= MAXLOG; i++)
  {
    if (delta & (1 << i)) {
      x = ancestor[x][i];
    }
  }
  
  /*
  // ����Ĵ���Ҳ�ǿ��Եģ����һ�������һЩ 
  for (int i = MAXLOG; i >= 0; i--)
  {
    if (depth[y] <= depth[ancestor[x][i]]) {    // ע������������� ���С�� <= ��ȴ�ĵ����ȵ���� 
      x = ancestor[x][i];
    }
  }
  */  
  
  // ����Ѿ���ͬһ���߶ȶ��� x, y ��ȣ�˵�� y �� x �����ȣ����� y 
  if (x == y) {
    return y;
  }
  // ���򣬾�����һ����������������ʱ��Ӧ�ô� MAXLOG �������� 0 
  for (int i = MAXLOG; i >= 0; i--)
  {
    // x �ĵ� 2^i �������� y �ĵ� 2^i �����Ȳ�ͬʱ������ x,y �ֱ���������ȣ����������� 
    if (ancestor[x][i] != ancestor[y][i]) {
      x = ancestor[x][i], y = ancestor[y][i];
    }
  }
  // ��󣬷����乫������ ancestor[x][0]
  return ancestor[x][0];
}

int main()
{
  scanf("%d%d%d", &n ,&m, &s);
  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    addEdge(u, v);
    addEdge(v, u);
  }
  
  dfs(s, 1, s);             // ���Ӧ�ô� 1 ��ʼ~ 
  
  for (int i = 0; i < m; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", lca(a, b));
  }
  
  return 0;
}
