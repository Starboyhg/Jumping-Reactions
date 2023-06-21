/*
Jumping-Reactions.cpp
V 2.3 Junio 2023
Autores:
Equipo Las Divinas

Programa que resuelve mediante Segment Tree el problema de Jumping Reactions

Orden de complejidad:
Temporal: O(nlog2n)
Espacial: O(2n)
Compilación 
Linux: gpp Jumping-Reactions.cpp -o Jumping-Reactions.exe
Ejecución
Linux: ./Jumping-Reactions.exe 
Windows: Jumping-Reactions.exe 
*/
////*************************Librerias***********************////
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie (0);
#define ll long long
#define mod 1000000007

/*
void build(vector<pair< ll, ll> > &tree,int n)
Recibe:vector<pair< ll, ll>> vector de pares de tipo long long, int tamaño del arreglo
Devuelve: void (No retorna valor explicito)
Observaciones: Funcion que contruye el Segment Tree iterativamente a partir de un arreglo de pares de
tipo long long, ademas de guardar los elementos del arreglo en las hojas del arbol, guarda la suma 
de los elementos en el primer elemento del par y la suma de los cuadrados en el segundo elemento del par
*/
void build(vector<pair< ll, ll> > &tree,int n){
    for (int i = n - 1; i > 0; --i)
    { 
        tree[i].first = tree[i<<1].first + tree[i<<1|1].first;
        tree[i].second = (tree[i<<1].first * tree[i<<1|1].first)+tree[i<<1].second + tree[i<<1|1].second;
    }
    return;
}

/*
int query(int n, int l, int r, vector<pair< ll, ll> > &tree,)
Recibe: int tamaño del arreglo, int indice izq, int indice der, vector<pair< ll, ll>> vector de pares de tipo long long
Devuelve: int el valor resultando de una consulta en el Segment Tree en el rango [l,r]
Observaciones: Funcion que recibe un rango de busqueda [l,r] y devuelve el resultado de la consulta en el Segment Tree
si el rango de consulta no esta calculado lo recalcula iterativamente, haciendo busqueda binaria en el arbol
*/
int query(int n,int l, int r,vector<pair< ll, ll> > &tree) { 
  pair<ll,ll> resL=make_pair(0,0),resR=make_pair(0,0);
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) 
  {
    if (l&1){
        resL.second=(resL.second+tree[l].second+tree[l].first*resL.first)%mod;
        resL.first+=tree[l].first;
        l++;
    }
    if (r&1){ 
        r--;
        resR.second=(resR.second+tree[r].second+tree[r].first*resR.first)%mod;
        resR.first +=tree[r].first;
        
    }
  }
  return (resL.second+resR.second+resL.first*resR.first)%mod;
}

////*************************Funcion Principal***********************////
int main() {
    fastio
    int n, q;
    int l,r,res;
    cin >> n >> q;
    vector<int> A(n);
    vector<pair< ll, ll> > SegmentTree(2*n,make_pair(0,0));

    for(auto i=n;i<2*n;i++){
        cin>>SegmentTree[i].first;
    }
    build(SegmentTree,n);
    while(q--){
        cin>>l>>r;
        res=query(n,l-1,r,SegmentTree);
        cout<<res<<endl;
    }
    return 0;
}