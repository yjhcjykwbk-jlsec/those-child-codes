int f(int n,int k)
{
  if(n==1||k==0) return 1;
    if(n>k) return f(k,k);
    else return f(n-1,k)+f(n,k-n); //k-n����ÿ������Ԥװһ����������
}                                                                     
  
  //��n��ƻ���ŵ�k��������