#include <iostream>
using namespace std;
const int MOD = (1<<10) | (1<<3) | 1;
int degree(int x){
    int d=-1;
    while(x){
        x>>=1;
        d++;
    }
    return d;
}
int polyMul(int a,int b){
    int res=0;
    while(b){
        if(b&1) res^=a;
        a<<=1;
        b>>=1;
    }
    return res;
}

int polyMod(int a,int b){
    while(degree(a)>=degree(b)){
        int shift=degree(a)-degree(b);
        a ^= (b<<shift);
    }
    return a;
}

int polyModMul(int a,int b){
    return polyMod(polyMul(a,b),MOD);
}

int inverseGF(int a){

    int r0=MOD;
    int r1=a;

    int s0=0;
    int s1=1;

    int step=0;

    while(r1!=0){

        int q=0;
        int temp=r0;

        while(degree(temp)>=degree(r1)){
            int shift=degree(temp)-degree(r1);
            q ^= (1<<shift);
            temp ^= (r1<<shift);
        }

        cout<<"Step "<<step<<endl;
        cout<<"q = "<<q<<endl;
        cout<<"r0 = "<<r0<<" r1 = "<<r1<<endl;
        cout<<"remainder = "<<temp<<endl;

        r0=r1;
        r1=temp;

        int newS = s0 ^ polyModMul(q,s1);

        s0=s1;
        s1=newS;

        cout<<"s0 = "<<s0<<" s1 = "<<s1<<endl;
        cout<<"-------------------"<<endl;

        step++;
    }

    return s0;
}

int main(){

    int a=523;
    int b=1015;

    cout<<"Inverse of a"<<endl;
    cout<<"a^-1 = "<<inverseGF(a)<<endl;

    cout<<endl;

    cout<<"Inverse of b"<<endl;
    cout<<"b^-1 = "<<inverseGF(b)<<endl;

}
