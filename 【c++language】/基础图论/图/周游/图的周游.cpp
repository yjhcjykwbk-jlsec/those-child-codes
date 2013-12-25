#include <iostream>
#include <cassert>
#include <stack>
#include <queue>
using namespace std;
typedef  bool * gg;
template<int T>
class Graph
{
    private:
        bool (*G)[T];
        const int numOfVertice;
        bool visited[T];
        short degree[T];
    public:
        Graph(bool (*data)[T]):numOfVertice(T),G(data)
    {
        for(int i=0;i<numOfVertice;i++)
        {
            degree[i]=0;
        }
        for(int i=0;i<numOfVertice;i++)
        {
            for(int j=0;j<numOfVertice;j++)
            {
                degree[j]+=G[i][j];
            }
        }
    }
        void Func(short &vertex)
        {
            cout<<vertex<<" visited"<<endl;
        }  

        //ÍØÆËÅÅÐò 
        void Sort()
        {
            cout<<"sort:"<<endl;
            queue<short> Q;
            short i;
            for(i=0;i<numOfVertice;i++)
            {
                if(degree[i]==0)
                    Q.push(i);
            }
            while(!Q.empty())
            {
                i=Q.front();
                Q.pop();
                Func(i);
                for(int j=0;j<numOfVertice;j++)
                {
                    if(G[i][j])
                    {
                        degree[j]--;
                        if(degree[j]==0)
                            Q.push(j);
                    }
                }
            }  
        } 

        void DFS ()
        {
            short start=0;
            int i;
            for(i=0;i<numOfVertice;i++)
                visited[i]=false;
            std::stack<short> S;
            S.push(start);
            visited[start]=true;
            cout<<"DFS:"<<endl;
            while (!S.empty())
            {
                start=S.top();
                S.pop();
                Func(start);
                for (i=0; i<numOfVertice; ++i)
                {
                    if (G[start][i] && (visited[i]==false))
                    {
                        visited[i]=true;
                        S.push(i);
                    }
                }
            }
        }
        void BFS ()
        {
            short start=0;
            int i;
            for(i=0;i<numOfVertice;i++)
                visited[i]=false;
            std::queue<short> S;
            S.push(start);
            visited[start]=true;
            cout<<"BFS:"<<endl;
            while (!S.empty())
            {
                start=S.front();
                S.pop();
                Func(start);
                for (i=0; i<numOfVertice; ++i)
                {
                    if (G[start][i] && !visited[i])
                    {
                        visited[i]=true;
                        S.push(i);
                    }
                }
            }
        }

};


static bool data[9][9]=
{
    {0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

bool (*d)[9]=data;
static bool old[9];

int main()
{
    Graph<9> g(d);

    g.DFS();
    g.BFS();
    g.Sort();
    int a;
    cin>>a;
    return 1;
}

