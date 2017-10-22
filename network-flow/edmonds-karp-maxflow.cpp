// Edmonds-Karp �������� 
// ǿ��������ƪ���£� 
// http://www.cnblogs.com/ZJUT-jiangnan/p/3632525.html

int pre[MAXN], visited[MAXN];

/**
 * ���²������� 
 * @param int u    ��� 
 * @param int flow ���µ����� 
 */
void update_residual_network(int u, int flow) 
{
  while (pre[u] != -1)
  {
    map[pre[u]][u] -= flow;     // ����߼�ȥ���� 
    map[u][pre[u]] += flow;     // ����߼�������
    u = pre[u];
  }
}

/**
 * Ѱ�ҿ��е�����· 
 * @param int start     ��� 
 * @param int terminal  �յ� 
 */
int find_path(int start, int terminal)
{
  // ��ʼ���������
  memset(visited, 0, sizeof visited);
  memset(pre, -1, sizeof pre);
  visited[start] = 1;
   
  // BFS
  int min = INF;
  queue<int> Q;
  Q.push(start);
  
  while (!Q.empty())
  {
    int cur = Q.front();
    Q.pop();
    // �����ǰ���Ѿ����յ��ˣ��˳� 
    if (cur == terminal) {
      break;
    }
    // ���򣬶��ڸõ����ӵ���һ���ڵ㣬�������� 
    for (int i = 0; i < m; i++)
    {
      if (!visited[i] && map[cur][i] != 0) {
        Q.push(i);             // �ѵ�ǰ����� BFS ���� 
        min = min < map[cur][i] ? min : map[cur][i];     // ���� delta ����Сֵ 
        pre[i] = cur;          // ��������·��·��
        visited[i] = 1;        // ��ǽڵ��ѷ��� 
      }
    } // for
  } // while
  // �Ҳ������������·�� 
  if (pre[terminal] == -1) {
    return 0;
  }
  // ����ҵ��ˣ���������·����Сֵ
  return min;    
}

/**
 * Edmonds Karp �㷨������ 
 * @param int start     ��� 
 * @param int terminal  �յ� 
 */
int edmonds_karp(int start, int terminal)
{
  int newFlow = 0, maxFlow = 0;
  // �����ڿ�������ʱ�򣬲������� 
  do {
    newFlow = find_path(start, terminal);
    update_residual_network(terminal, newFlow);
    maxFlow += newFlow;
  } while (newFlow != 0);
  
  return maxFlow;
}
