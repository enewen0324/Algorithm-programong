const int  MAXINT = 32767;
const int MAXNUM = 10;
int dist[MAXNUM];
int prev[MAXNUM];

int A[MAXUNM][MAXNUM];

void Dijkstra(int v0)
{
  �@�@bool S[MAXNUM];                                  // �P?�O�_�w�s�J??��S���X��
      int n=MAXNUM;
  �@�@for(int i=1; i<=n; ++i)
 �@�@ {
      �@�@dist[i] = A[v0][i];
      �@�@S[i] = false;                                // ��l������???
      �@�@if(dist[i] == MAXINT)    
            �@�@prev[i] = -1;
 �@�@     else 
            �@�@prev[i] = v0;
   �@�@}
   �@ dist[v0] = 0;
   �@ S[v0] = true; �@�@
 �@�@ for(int i=2; i<=n; i++)
 �@�@ {
       �@�@int mindist = MAXINT;
       �@�@int u = v0; �@�@                            // ��X?�e���ϥΪ�?j��dist[j]�̤p��
      �@�@ for(int j=1; j<=n; ++j)
      �@�@    if((!S[j]) && dist[j]<mindist)
      �@�@    {
         �@�@       u = j;                             // u�O�s?�e?��?���Z�ó̤p��?��?? 
         �@ �@      mindist = dist[j];
       �@�@   }
       �@�@S[u] = true; 
       �@�@for(int j=1; j<=n; j++)
       �@�@    if((!S[j]) && A[u][j]<MAXINT)
       �@�@    {
           �@    �@if(dist[u] + A[u][j] < dist[j])     //�b�q?�s�[�J��u?��?�����v0?��u����?  
           �@    �@{
                   �@�@dist[j] = dist[u] + A[u][j];    //��sdist 
                   �@�@prev[j] = u;                    //??�e??? 
            �@�@    }
        �@    �@}
   �@�@}
}
