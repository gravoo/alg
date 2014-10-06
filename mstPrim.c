#include <stdio.h>
#include <stdbool.h>
//Prim
//union find
//struktura danych przechowujaca wskaźnika na samego siebie i ranking wierzchołka
struct UnionFind{
        struct UnionFind *parrent;
        int rng;
 };
 //struct rankKraw{
   //     int val;
    //    int a;
     //   };
struct wierzcholek{
        int ja;
        struct sasiad *sasiad;
        int counter;
        };
struct sasiad{
    struct wierzcholek *ss;
    int waga;};
//funkcja dokleja tablice
void add(struct sasiad *wsk,struct sasiad *wsk2,int pocza,int koniecb);
//funkcja zwracająca korzen struktury
struct UnionFind *rootf(struct UnionFind *el);
//funkcja lącząca dwa elementy w jeden
void Union(struct UnionFind *tab,struct UnionFind *tab2);
//funkcja sprawdzajaca czy dwa zbiory sa w zbiorze
bool check(struct UnionFind *el,struct UnionFind *el2);
//funkcja odpowiedzialna za przesowanie w dol elementow w drzewie krawedzi
void down(struct sasiad *wsk,int i,int n);
//funkcja odpowiedzialna za przesowanie el, w gore
void up(struct sasiad *wsk,int i,int n);
int main(){
int l_pushow=0,i=0,iloscDrzewek=6,iloscKrawedzi=12,n=0,c=0,l1,l2,sum=0,rozmiar=5,countera,counterb,countersum,partsum;
int a=0,b=0;
//int aa[12]={4,2,3,5,2,4,3,2,3,1,1,2};int bb[12]={5,5,5,6,6,6,4,4,6,3,6,3};int cc[12]={5,21,29,7,4,5,16,2,1,12,29,2};
struct sasiad *tmp;
struct sasiad *tmp2;

    scanf("%d %d",&iloscDrzewek,&iloscKrawedzi);
   // struct UnionFind *mst=malloc(iloscDrzewek*sizeof(struct UnionFind));
    //struct rankKraw *kraw=malloc(iloscKrawedzi*sizeof(struct rankKraw));
    //struct rankKraw *tmp;
    //struct UnionFind wsk[iloscDrzewek+2];
    struct UnionFind mst[iloscDrzewek+1];
    struct wierzcholek kraw[iloscDrzewek+1];

//inicjujemy zbior ktory bedzie przechowywal najmniejsze drzewo rozpinajace
for(i=0;i<=iloscDrzewek;i++)
    {
        mst[i].parrent=&mst[i];
        mst[i].rng=0;}
for(i=0;i<=iloscDrzewek;i++)
    {   kraw[i].sasiad=malloc(rozmiar*sizeof(struct sasiad));
        kraw[i].counter=0;
        kraw[i].ja=i;}
//pobieramy dane wejsciowe i ukladamy je na stercie

while(n<iloscKrawedzi){

       scanf("%d %d %d",&a,&b,&c);
       //a=aa[n];b=bb[n];c=cc[n];
        countera=kraw[a].counter;
        counterb=kraw[b].counter;
        kraw[a].sasiad[countera].ss=&kraw[b];
        kraw[b].sasiad[counterb].ss=&kraw[a];
        kraw[a].sasiad[countera].waga=c;
        kraw[b].sasiad[counterb].waga=c;
        kraw[a].counter+=1;
        kraw[b].counter+=1;
        up(kraw[a].sasiad,countera-1,countera-1);
        up(kraw[b].sasiad,counterb-1,counterb-1);


         if(kraw[a].counter>=rozmiar){
            if( (tmp2 = realloc(kraw[a].sasiad, ( kraw[a].counter+2) * sizeof(struct sasiad))) == NULL ){
                  break;}
            else{
            kraw[a].sasiad = tmp2;
            tmp2=NULL;}
            }


            if(kraw[b].counter>=rozmiar){
            if( (tmp2 = realloc(kraw[b].sasiad, ( kraw[b].counter+2) * sizeof(struct sasiad))) == NULL ){
                  break;}
            else{
            kraw[b].sasiad = tmp2;
            tmp2=NULL;}
            }
        n++;
}
tmp2=NULL;
//printf("%d",(kraw[0].sasiad[0].ss->ja));
i=0;
while(kraw[1].counter>0){

       // up(kraw[1].sasiad,kraw[1].counter-1,kraw[1].counter-1);
       // l1=kraw[1].ja;
        l2=kraw[1].sasiad[0].ss->ja;

        tmp=kraw[1].sasiad[0].ss->sasiad;
        counterb=kraw[1].sasiad[0].ss->counter;
        partsum=kraw[1].sasiad[0].waga;
    //    for(int z=0;z<kraw[1].counter;z++){
      //      printf("%d ",kraw[1].sasiad[z].ss->ja);
       // }

        //printf("\n");
        kraw[1].counter--;
        kraw[1].sasiad[0]=kraw[1].sasiad[kraw[1].counter];
        down(kraw[1].sasiad,0,kraw[1].counter);
       // for(int z=0;z<kraw[1].counter;z++){
        //    printf("%d ",kraw[1].sasiad[z].ss->ja);
        //}
        //printf("%d ",partsum);
        //printf("\n");

       if(check(&mst[1],&mst[l2])){

        Union(&mst[1],&mst[l2]);
        sum+=partsum;
        l_pushow=kraw[1].counter+counterb;

        if(l_pushow>=rozmiar){
            if( (tmp2 = realloc(kraw[1].sasiad, (l_pushow) * sizeof(struct sasiad))) == NULL ){
                  break;}
            else{
            kraw[1].sasiad = tmp2;}
            }

        add(kraw[1].sasiad,tmp,kraw[1].counter,counterb);
        kraw[1].counter=l_pushow;
        }


       i++;

}
printf("%d ",sum);
return 0;
}
//przeszukuję stertę od góry i kieruję sie w stronę ostatniego, najmniejszego liscia
//az funkcja nie bedzie miala co robic
void down(struct sasiad *wsk,int i,int n){
    struct sasiad tmp;
    //lewy syn
    int l=(2*(i+1))-1;
    //prawy syn
    int r=2*(i+1);
    int m=i;
     //jesli lewy indeks syna jest mniejszy, rowny od rozmiaru i lewy syn jest
    //mniejszy od ojca to przypisuje indeks do syna do m
    if((l<=n)&&(wsk[l].waga<wsk[i].waga)){
        m=l;
    }
    //jak wyzej
    if((r<=n)&&(wsk[r].waga<wsk[m].waga)){
        m=r;
    }
    if(m==i)return 0;
    //zamieniam miejscami
    tmp=wsk[i];
    wsk[i]=wsk[m];
    wsk[m]=tmp;
    //schodze nizej
    down(wsk,m,n);
}
//przydatna przy wstawianiu, sprawdzam nowo dodany element i jade w gore az do szczytu
void up(struct sasiad *wsk,int i,int n){
    //znajdujemy ojca danego liscia
    int o=(i-1)/2;
    if(o<0) return 0;
    //lapiemy lewego syna
    int l=(2*(o+1))-1;
    //i prawego
    int r=2*(o+1);
    int m=o;
    struct sasiad tmp;
    //jesli lewy indeks syna jest mniejszy, rowny od rozmiaru i lewy syn jest
    //mniejszy od ojca to przypisuje indeks do syna do m
    //printf("%d",wsk[0].val);
    if((l<=n)&&(wsk[l].waga<wsk[o].waga)){
        m=l;
    }
    //jak wyżej tylko prawy syn
    if((r<=n)&&(wsk[r].waga<wsk[m].waga)){
    m=r;
    }
    tmp=wsk[o];
    wsk[o]=wsk[m];
    wsk[m]=tmp;
    if(o<1)return 0;
    //wchodzimy wyzej
    up(wsk,m,n);
}
void Union(struct UnionFind *tab,struct UnionFind *tab2){

    //znajdujemy korzenie dwoch elementow

    tab = rootf(tab);
    tab2 = rootf(tab2);
    //jesli sa takie same, to znaczy ze sa w tym samym zbiorze
    if((tab)==(tab2)) return 0;
    //jesli ranking pierwszego jest wiekszy od drugiego to pierwszy zostaje rodzicem drugiego
    if((tab->rng)>(tab2->rng)){
        tab2->parrent=tab;
    }
    //i odwrotnie
    else if((tab->rng)<(tab2->rng)){
        tab->parrent=tab2;
    }
    //jesli jednak nic z powyzszych a adresy nadal sa rozne to doklejamy do pierwszego
    else if( tab!=tab2){
        tab2->parrent=tab;
        tab->rng+=1;
}
}

struct UnionFind *rootf(struct UnionFind *el){
    //jesli rodzic elementu jest innym elementem to schodzimy w dol
    if((el->parrent)!=el){
         el->parrent=rootf(el->parrent);
        }
    //jesli tak to zwracamy rodzica
  return el->parrent;

};
bool check(struct UnionFind *el,struct UnionFind *el2){
    //sprawdzamy czy dwa elementy sa w tym samym zbiorze szukajac po korzeniu do gory
    el=rootf(el);
    el2=rootf(el2);
    if(el==el2) return 0;
    else return 1;
}
void add(struct sasiad *wsk,struct sasiad *wsk2,int pocza,int koniecb){
    int j=pocza;
    for(int i=0;i<koniecb;i++){
        wsk[j]=wsk2[i];
        up(wsk,pocza+i-1,pocza+i-1);
        j++;
    }




}


