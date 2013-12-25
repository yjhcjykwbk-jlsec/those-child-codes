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
     while(l<=middle&&r<=right)
     {
         if(a[l].height<0)l++;
         else if(a[r].height<0) r++; 
         else
         {
              if(a[l].left>a[r].right||a[l].right<a[r].left)
              {
                  if(a[l].left<a[r].left){j=l;l++;}
                  else {j=r;r++;}
                  temp[++pointer]=a[j];
              }
              else 
              {//jÔÚ×ó 
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
                       {
                          if(a[k].height!=a[j].height) 
                          { 
                             temp[++pointer]=a[j];
                             a[k].left=a[j].right;
                             if(j==l) l++;
                             else r++;
                          }
                          else 
                          {//a[k].height<a[j].height
                             a[k].left=a[j].left;
                             if(j==l) l++;
                             else r++;
                          }    
                       }
                   }
              } 
         }         
    }
    if(pointer<right){
                          while(l<=middle){ temp[++pointer]=a[l];l++; }
                          while(r<=right){temp[++pointer]=a[r];r++; }
                          while(pointer<right){temp[++pointer].height=-1;}
                    }
    for(i=left;i<=right;i++)a[i]=temp[i];
}
void f(dt *a,dt *temp,int l,int r)
{
    if(l>=r)return;
    int middle=(l+r)/2;
    f(a,temp,l,middle);
    f(a,temp,(middle+1),r);
    merge(a,temp,2*l,2*middle+1,2*r+1);
}
int main()
{
    dt a[200000];
    dt temp[200000];
    int pointer=-1;
    int n;
    cin>>n;
    while(pointer<2*n-1)
    {
                ++pointer;
                cin>>a[pointer].left>>a[pointer].right>>a[pointer].height;
                ++pointer;
                a[pointer].height=-1;
    }
    f(a,temp,0,pointer/2);
    int lastheight=0;
    int lastpoint=0;
    int dheight=0; 
    int dpoint=0;
    for(int i=0;i<2*n&&a[i].height>0;i++)
    {
            dheight=a[i].height-lastheight;
            dpoint=a[i].left-lastpoint;
            if(dpoint>0&&i>0) 
            {
                         printf("D %d\n",lastheight);
                         printf("R %d\n",dpoint);
                         dheight=a[i].height;
            }
            if(dheight>0) printf("U %d\n",dheight);
            else printf("D %d\n",-dheight);
            printf("R %d\n",a[i].right-a[i].left);
            lastheight=a[i].height;
            lastpoint=a[i].right;
    }
    printf("D %d\n",lastheight);
} 

