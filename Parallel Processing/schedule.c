 #include<stdio.h>
 #include<omp.h>
 #include<stdlib.h>
 int f(int a,int b){
    return a+b;
 }
 int main(){
    int m,n;
    int i,j;
    int a[m][n];
    printf("Enter the value of m::");
    scanf("%d",&m);
    printf("Enter the value of n::");
    scanf("%d",&n);
    for ( i = 0; i < m; i++)
    {
     for ( j = 0; j < n; j++)
     {
        a[i][j] = rand()%100+1;
     }
    }
    
    #pragma omp parallel for private(j) schedule(static,1)
    for ( i = 0; i < m; i++)
    {
     for ( j = 0; j < n; j++)
     {
        a[i][j] = f(i,j);
     }
    }
    for ( i = 0; i < m; i++)
    {
     for ( j = 0; j < n; j++)
     {
        printf("%6d",a[i][j]);    
     }
     printf("\n");
    }

    return 0;

 }