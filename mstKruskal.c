#include <stdio.h>
#include <stdbool.h>
//KRUSKAL
//union find
//struktura danych przechowujaca wskaźnika na samego siebie i ranking wierzchołka
struct UnionFind{
        struct UnionFind *parrent;
        int rng;
 };
 struct rankKraw{
        int val;
        int a;
        int b;
        };
//funkcja zwracająca korzen struktury
struct UnionFind *rootf(struct UnionFind *el);
//funkcja lącząca dwa elementy w jeden
void Union(struct UnionFind *tab,struct UnionFind *tab2);
//funkcja sprawdzajaca czy dwa zbiory sa w zbiorze
bool check(struct UnionFind *el,struct UnionFind *el2);

//funkcja zwracająca korzen struktury
struct UnionFind *rootf(struct UnionFind *el);
//funkcja lącząca dwa elementy w jeden
void Union(struct UnionFind *tab,struct UnionFind *tab2);
//funkcja sprawdzajaca czy dwa zbiory sa w zbiorze
bool check(struct UnionFind *el,struct UnionFind *el2);

//funkcja odpowiedzialna za przesowanie w dol elementow w drzewie krawedzi
void down(struct rankKraw *wsk,int i,int n);
//funkcja odpowiedzialna za przesowanie el, w gore
void up(struct rankKraw *wsk,int i,int n);
int main(){
int l_pushow=0,i=0,iloscDrzewek=0,iloscKrawedzi=0,n=0,c=0,l1,l2,sum=0,rozmiar=1000;
int a=0,b=0;

    scanf("%d %d",&iloscDrzewek,&iloscKrawedzi);
   // struct UnionFind *mst=malloc(iloscDrzewek*sizeof(struct UnionFind));
    //struct rankKraw *kraw=malloc(iloscKrawedzi*sizeof(struct rankKraw));
    //struct rankKraw *tmp;
    //struct UnionFind wsk[iloscDrzewek+2];
    struct UnionFind mst[iloscDrzewek];
    struct rankKraw kraw[iloscKrawedzi];

/*if (!kraw)
    {
        perror("malloc");
        return 0;
    }
if (!mst)
    {
        perror("malloc");
        return 0;
    }*/
//inicjujemy zbior ktory bedzie przechowywal najmniejsze drzewo rozpinajace
for(i=0;i<=iloscDrzewek;i++)
    {
        mst[i].parrent=&mst[i];
        mst[i].rng=0;}
//pobieramy dane wejsciowe i ukladamy je na stercie
while(n<iloscKrawedzi){

        scanf("%d %d %d",&a,&b,&c);
        kraw[l_pushow].val=c;
        kraw[l_pushow].a=a;
        kraw[l_pushow].b=b;
        l_pushow++;
        up(kraw,l_pushow-1,l_pushow-1);
        /* if(l_pushow==rozmiar){
            if( (tmp = realloc(kraw, (rozmiar=rozmiar+1) * sizeof(struct rankKraw))) == NULL ){
                  break;}
            else{
            kraw = tmp;}
            }*/
        n++;
}
n=0;
//sciagamy ze szczytu najmniejszy element, i sprawdzamy czy jest juz w zbiorze roziazań. Jesli nie to go dodajemy bo najmniejszy
//jesli tak, nic nie robimy
while(l_pushow>0){
        l1=kraw[0].a;
        l2=kraw[0].b;
     if(check(&mst[l1],&mst[l2])){
        Union(&mst[l1],&mst[l2]);
        sum+=kraw[0].val;
     }
         //przypisujemy ostatni element do korzenia
        kraw[0]=kraw[l_pushow-1];
            //zmniejszamy ilosc el
        l_pushow--;
            //porzadkujemy
        down(kraw,0,l_pushow-1);

    //n++;
}
printf("%d",sum);
//free(kraw);
//free(mst);
return 0;
}
//przeszukuję stertę od góry i kieruję sie w stronę ostatniego, najmniejszego liscia
//az funkcja nie bedzie miala co robic
void down(struct rankKraw *wsk,int i,int n){
    struct rankKraw tmp;
    //lewy syn
    int l=(2*(i+1))-1;
    //prawy syn
    int r=2*(i+1);
    int m=i;
     //jesli lewy indeks syna jest mniejszy, rowny od rozmiaru i lewy syn jest
    //mniejszy od ojca to przypisuje indeks do syna do m
    if((l<=n)&&(wsk[l].val<wsk[i].val)){
        m=l;
    }
    //jak wyzej
    if((r<=n)&&(wsk[r].val<wsk[m].val)){
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
void up(struct rankKraw *wsk,int i,int n){
    //znajdujemy ojca danego liscia
    int o=(i-1)/2;
    if(o<0) return 0;
    //lapiemy lewego syna
    int l=(2*(o+1))-1;
    //i prawego
    int r=2*(o+1);
    int m=o;
    struct rankKraw tmp;
    //jesli lewy indeks syna jest mniejszy, rowny od rozmiaru i lewy syn jest
    //mniejszy od ojca to przypisuje indeks do syna do m
    //printf("%d",wsk[0].val);
    if((l<=n)&&(wsk[l].val<wsk[o].val)){
        m=l;
    }
    //jak wyżej tylko prawy syn
    if((r<=n)&&(wsk[r].val<wsk[m].val)){
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


