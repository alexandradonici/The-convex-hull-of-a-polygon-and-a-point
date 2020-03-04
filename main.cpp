#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

typedef struct
{
    int x;
    int y;
}punct;

int orientare(punct p, punct q, punct r)
{
    int x;
    x=p.y*(r.x-q.x)+q.y*(p.x-r.x)+r.y*(q.x-p.x);

    if(x==0)
        return 0; ///coliniare
    else
        if(x>0)
            return 1; ///sens trigonometric
        else
            return 2; ///sens orar
}


int verificare_tangenta(punct P, punct Q, vector<punct> poligon, int n)
{
    int i,v=-1,j=0;;

    ///gasim primul punct diferit de Q si salvam in v
    ///directia de orientare fata de PQ
   while(j<n && v==-1)
   {
        if(Q.x!=poligon[j].x && Q.y!=poligon[j].y)
           {
               v=orientare(P,Q,poligon[j]);
           }
        j++;
   }

   ///verificam daca toate punctele sunt de aceeasi parte
   ///fata de dreapta PQ
   ///in caz afirmativ, PQ este tangenta
    for(i=0;i<n;i++)
        if(!(Q.x==poligon[i].x && Q.y==poligon[i].y))
    {
        if(orientare(P,Q,poligon[i])!=v)
        {
            return 0;
        }

    }

    return 1;
}

void tangente(punct P, int n, vector<punct>poligon, punct &A, punct &B)
{
    int i,ok=0;
    ///gasim cele doua tangente: PA si PB
    for(i=0;i<n;i++)
        if(verificare_tangenta(P, poligon[i],poligon,n)==1)
            {

                if(ok==0)
            {
                A=poligon[i];
                ok=1;
            }
            else
                B=poligon[i];


            }

}

///calculam determinantul
/// xA yA 1
/// xB yB 1
/// xC yC 1
int determinant(punct A, punct B, punct C)
{
    return A.x*B.y+B.x*C.y+C.x*A.y-C.x*B.y-A.x*C.y-B.x*A.y;
}

/// vectorii (PA, AX), (AB, BX), (BP, PX)
/// vor realiza intotdeauna aceeasi intoarcere daca
///punctul X este in interioru triunghiului ABP
/// de aceea, determinantii d1,d2,d3
///trebuie sa aiba acelasi semn
int punct_int_triunghi(punct P, punct A, punct B, punct X)
{
    int d1,d2,d3;
    d1=determinant(P,A,X);
    d2=determinant(B,P,X);
    d3=determinant(A,B,X);

    if(!((d1>0&&d2>0&&d3>0)||(d1<0&&d2<0&&d3<0)))
        return 0;
    return 1;

}

void acoperire_convexa(int n, vector<punct> poligon, punct P, punct A, punct B, vector<punct> &Ac_convex)
{
    int j;

    for(j=0;j<n;j++)
        Ac_convex.push_back(poligon[j]);

    for(auto i=Ac_convex.begin(); i<Ac_convex.end();i++)
    {

            if(punct_int_triunghi(P,A,B,*i)!=0)
               {
                   Ac_convex.erase(i);
                    i--;
               }


    }
     for(auto i=Ac_convex.begin(); i<Ac_convex.end();i++)
     {

        auto j=i+1;
            if(((*i).x==A.x && (*i).y==A.y && (*j).x==B.x && (*j).y==B.y ) || ((*i).x==B.x && (*i).y==B.y && (*j).x==A.x && (*j).y==A.y ))
            {
                Ac_convex.insert(j,P);
                j++;
                i=j;
                return;
            }

     }
        Ac_convex.insert(Ac_convex.begin(), P);
}


int main()
{
    vector<punct> poligon, Ac_convex;
    int i,n;
    punct P;
    fin>>n;

    for(i=0;i<n;i++)
    {
        punct A;
        fin>>A.x>>A.y;
        poligon.push_back(A);
    }
    fin>>P.x>>P.y;

    punct A,B;
    tangente(P,n,poligon,A,B);

    acoperire_convexa(n,poligon,P,A,B,Ac_convex);


    fout<<"Acoperirea convexa este formata din punctele: "<<endl;
     for(unsigned int i=0;i<Ac_convex.size();i++)
    {
        fout<<"("<<Ac_convex[i].x<<","<<Ac_convex[i].y<<")"<<endl;
    }


    return 0;
}
