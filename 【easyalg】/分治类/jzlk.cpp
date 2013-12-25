#include<iostream>
using namespace std;
struct dt
{
       int left;
       int right;
       int height;
};
void merge(dt *a,dt *temp,int left,int middle,int right)
{
     int l=left,r=middle+1,pointer=l-1,i,j,k;
     while(i<=middle&&r<=right)
     {//横线段不交叉 
         if(a[l].height<0||a[r].height<0) break;//归并到头 
         else
         {
              if((a[l].left-a[r].right>0)||(a[l].right-a[r].left<0))
              {
                  if(a[l].left<a[r].left){j=l;l++;}
                  else {j=r;r++;}
                  temp[++pointer]=a[j];
              }
              else 
              {//j在左 
                   if(a[l].left<=a[r].left){j=l,k=r;}
                   else if(a[l].left>=a[r].left)
                   {
                      j=r,k=l;
                   }
                   if(a[k].height>a[j].height)
                   {
                      if(a[j].left!=a[k].left) 
                      {
                         temp[++pointer].left=a[j].left;temp[pointer].right=a[k].left;temp[pointer].height=a[j].height;
                      }
                      if(a[k].right>=a[j].right)
                      {
                           if(j==l) l++;
                           else r++;
                      }
                      else 
                      {
                           temp[++pointer]=a[k];
                           a[j].left=a[k].right;
                           if(k==l) l++;
                           else r++;
                      }
                   }
                   else
                   {
                       if(a[k].right<=a[j].right) 
                       {
                           if(k==l) l++;
                           else r++;
                       }
                       else
                       {//高度不等：
                          if(a[k].height!=a[j].height) 
                          { 
                             temp[++pointer]=a[j];
                             a[k].left=a[j].right;
                             if(j==l) l++;
                             else r++;
                          }
                          else 
                          {
                             a[k].left=a[j].left;
                             if(j==l) l++;
                             else r++;
                          }    
                       }
                   }
              } 
         }         
    }
    while(pointer<r){
                          while(l<=middle){ temp[++pointer]=a[l];l++;}
                          while(r<=right){temp[++pointer]=a[r];r++;}
                    }
    for(i=l;i<=r;i++)a[i]=temp[i];
}
void f(dt *a,dt *temp,int l,int r)
{
    if(l>=r)return;
    int middle=(l+r)/2;
    f(a,temp,l,middle);
    f(a,temp,(middle+1),r);
    merge(a,temp,2*l,2*middle,2*r);////////////
}
int main()
{
    dt a[10000];
    dt temp[10000];
    int pointer=0;
    while(true)
    {
                cin>>a[pointer].left>>a[pointer].right>>a[pointer].height;
                ++pointer;
                a[pointer].height=-1;
    }
    f(a,temp,0,pointer/2);
    for(int i=0;a[i].height>0;i++)
    {
            cout<<a[i].left<<" "<<a[i].right<<" "<<a[i].height<<endl;
    }
} 
