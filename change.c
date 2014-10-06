#include <stdio.h>
#include <stdbool.h>
#define MAX 2147483647



int liczba_nominalow=0,i=0,kwota_do_wydania=0,j=0,obecna_wartosc=0,l_pushow=0;
int main(){

    scanf("%d",&liczba_nominalow);
    int wartosc_monet_nieposortowanych[liczba_nominalow+1];
    int wartosc_monet[liczba_nominalow+1];

    while(i<liczba_nominalow){
        scanf("%d",&obecna_wartosc);
        wartosc_monet_nieposortowanych[i]=obecna_wartosc;
        l_pushow++;
        up(wartosc_monet_nieposortowanych,l_pushow-1,l_pushow-1);

        i++;
}
l_pushow=liczba_nominalow;
i=1;
    while(i<=liczba_nominalow){
    wartosc_monet[i]=wartosc_monet_nieposortowanych[0];
    wartosc_monet_nieposortowanych[0]=wartosc_monet_nieposortowanych[l_pushow-1];
    l_pushow--;
    down(wartosc_monet_nieposortowanych,0,l_pushow-1);
    i++;
    }


    i=1;
    scanf("%d",&kwota_do_wydania);
    int wartosc_monet_pomocnicze[kwota_do_wydania+1];
     wartosc_monet_pomocnicze[0]=0;
    while(i<=kwota_do_wydania){
            wartosc_monet_pomocnicze[i]=MAX;
            i++;
    }



    i=1;
    j=0;
    int i;
    int n;
    int    k=kwota_do_wydania;
   int a=liczba_nominalow;
   for (i=1;i<=a;++i)           // dla każdego nominału wykonuj:
   {
     int n=wartosc_monet[i];                     // n – aktualnie analizowany nominał
                       // wczytaj nominał
     for (int j=0;j<=k-n;++j)   // dla j=0 do k-n wykonuj:
       if (wartosc_monet_pomocnicze[j] < MAX)     // jeżeli T[j] już ma przypisaną wartość i jeżeli
         if (wartosc_monet_pomocnicze[j]+1 < wartosc_monet_pomocnicze[j+n])   // dodanie monety zmniejszy liczbę monet dla kwoty j+n,
           wartosc_monet_pomocnicze[j+n] = wartosc_monet_pomocnicze[j]+1;     // to zapisz nową liczbę monet dla zwiększonej kwoty.
   }
    if(wartosc_monet_pomocnicze[kwota_do_wydania]<=kwota_do_wydania){
     printf("%d\n",wartosc_monet_pomocnicze[kwota_do_wydania]);}
     else{
     printf("NIE");}


    return 0;}
void up(int *wsk,int i,int n){
    //znajdujemy ojca danego liscia
    int o=(i-1)/2;
    if(o<0) return 0;
    //lapiemy lewego syna
    int l=(2*(o+1))-1;
    //i prawego
    int r=2*(o+1);
    int m=o;
    int tmp;
    //jesli lewy indeks syna jest mniejszy, rowny od rozmiaru i lewy syn jest
    //mniejszy od ojca to przypisuje indeks do syna do m
    if((l<=n)&&(wsk[l]<wsk[o])){
        m=l;
    }
    //jak wyżej tylko prawy syn
    if((r<=n)&&(wsk[r]<wsk[m])){
    m=r;
    }
    tmp=wsk[o];
    wsk[o]=wsk[m];
    wsk[m]=tmp;
    if(o<1)return 0;
    //wchodzimy wyzej
    up(wsk,m,n);
}
void down(int *wsk,int i,int n){
    //lewy syn
    int l=(2*(i+1))-1;
    //prawy syn
    int r=2*(i+1);
    int m=i;
     //jesli lewy indeks syna jest mniejszy, rowny od rozmiaru i lewy syn jest
    //mniejszy od ojca to przypisuje indeks do syna do m
    if((l<=n)&&(wsk[l]<wsk[i])){
        m=l;
    }
    //jak wyzej
    if((r<=n)&&(wsk[r]<wsk[m])){
        m=r;
    }
    if(m==i)return 0;
    //zamieniam miejscami
    wsk[i]^=wsk[m];
    wsk[m]^=wsk[i];
    wsk[i]^=wsk[m];
    //schodze nizej
    down(wsk,m,n);
}
