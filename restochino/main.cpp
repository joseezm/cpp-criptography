#include <iostream>

using namespace std;

int modulo(int x, int y)
        {
            x=x-(x/y)*y;
            if(x<0)
                return x+y;
            return x;
        }

int eucE(int n1, int n2,int i){
            int res[3],x=0,y=0,d=0,x2=1,x1=0,y2=0,y1=1,q=0,r=0;
            int auxn2=n2;
            if(n2==0){
                res[0]=n1;
                res[1]=1;
                res[2]=0;
            }
            else{
                while(n2>0){
                    q=(n1/n2);
                    r= n1-(q*n2);
                    x= x2-(q*x1);
                    y= y2 - (q*y1);
                    n1= n2;
                    n2 = r;
                    x2= x1;
                    x1 = x;
                    y2 = y1;
                    y1 =y;
                }
                res[0]=n1;
                res[1]=x2;
                res[2]=y2;

                while(res[1]<0)
                    res[1]=res[1]+auxn2;
            }
            if(i==1) return res[0];
            else if (i==2) return res[1];
            else if (i==3) return res[2];
        }


int teoremachino(int n){
    int a[n];
    int p[n];
    int q[n];
    int P=1;
    int Pi[n];

    for(int i=0; i<n; i++){
        cout << "a"<<i<<": ";
        cin >> a[i];
        cout << "p" << i <<": ";
        cin >> p[i];

        P=P*p[i];
    }


    for (int i=0;i<n;i++){
       Pi[i]=P/p[i];
       q[i] = eucE(Pi[i],p[i],2);
    }

    int xo=0;

    for(int i=0; i<n;i++)
        xo= xo + (a[i]*Pi[i]*q[i]);

    xo=modulo(xo,P);

    cout << "Las soluciones del sistema son: X = " << xo << " + " << P <<"k" << endl;

}


int main()
{

    teoremachino(4);

    return 0;
}
