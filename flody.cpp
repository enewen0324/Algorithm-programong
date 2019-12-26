typedef struct          
{        
    char vertex[VertexNum];                                //??��         
    int edges[VertexNum][VertexNum];                       //?���x?,�i�ݰ�?��         
    int n,e;                                               //?��?�e��???�M??         
}MGraph; 

void Floyd(MGraph g)
{
 �@�@int A[MAXV][MAXV];
 �@�@int path[MAXV][MAXV];
 �@�@int i,j,k,n=g.n;
 �@�@for(i=0;i<n;i++)
    �@�@for(j=0;j<n;j++)
    �@�@{ �@�@
             A[i][j]=g.edges[i][j];
         �@�@ path[i][j]=-1;
     �@ }
 �@�@for(k=0;k<n;k++)
 �@�@{ 
      �@�@for(i=0;i<n;i++)
         �@�@for(j=0;j<n;j++)
             �@�@if(A[i][j]>(A[i][k]+A[k][j]))
             �@�@{
                   �@�@A[i][j]=A[i][k]+A[k][j];
                   �@�@path[i][j]=k;
              �@ } 
    �@} 
}
