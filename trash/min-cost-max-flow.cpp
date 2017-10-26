#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int MAXN = 2333;
 
struct Edge {
  int u, v;       // ����ߵ������յ�
  int cap;        // �ߵ�������
  int flow;       // �ߵ���������
  int cost;       // ��λ������
  Edge& reverse;  // ���������еķ����
  
  Edge(
    int tu = 0, int tv = 0, int tcap = 0,
    int tcost = 0, int tflow = 0
  ) {
    u = tu, v = tv, cap = tcap,
    cost = tcost, flow = tflow;
  }
};

vector<Edge> G[MAXN];

/**
 * ����ĳһ�ߵ�ʣ������
 * @param  e ������� Edge
 * @return   ���ؼ�����ʣ������
 */
int getResidual(Edge e)
{
  return e.cap - e.flow;
}

/**
 * ���һ���ߣ���������ͷ���
 * @param u    ���
 * @param v    �յ�
 * @param cap  ����
 * @param cost ����
 */
void addEdge(int u, int v, int cap, int cost)
{
  // ����� 
  Edge pos = Edge(u, v, cap, cost, 0, ++cnt);
  // ����� 
  Edge rev = Edge(u, v, cap, -cost, cap, -1 + cnt++);
  
  pos.reverse = &rev;
  rev.reverse = &pos;
  
  G[u].push_back(pos);
  G[v].push_back(rev)
}

int main()
{
  return 0;
}
