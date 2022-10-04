#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

struct cidade {
  int id;
  double x, y;
  bool pass = false;
  double distancia;
};


double calcula_distancias(cidade a, cidade b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}

double mais_perto(cidade a, cidade b){
  return (a.distancia < b.distancia);
}

int main() {

  int N, O;
  double x, y, L;

  cin >> N;
  O = 0;
  L = 0;

  vector<cidade> estado;
  vector<int> tour;
  estado.reserve(N);
  tour.reserve(N);

  for (int i =0; i<N ; i++) {
    cin >> x >> y;
    estado.push_back({i, x, y});
  }
  
  cidade cidade_inicial = estado[0];
  cidade cidade_atual = cidade_inicial;
  estado[0].pass = true;

  tour.push_back(cidade_inicial.id);

  for(int i = 1; i<N; i++){
    for(int j = 0; j<N; j++){
      if(estado[j].pass == false){
        double distancia = calcula_distancias(cidade_atual, estado[j]);
        estado[j].distancia = distancia;
      }
    }
    sort(estado.begin(), estado.end(), mais_perto);

    int count = 0;
    for(cidade c : estado){
      if(c.pass == false){
        cidade_atual = c;
        break;
      }
      count++;
    }
    tour.push_back(cidade_atual.id);
    L = L + cidade_atual.distancia;
    estado[count].pass = true;
  }

  L = L + calcula_distancias(cidade_inicial, cidade_atual);

  cout << L << " " << O << endl;
  for(int c : tour){
    cout << c << " ";
  }
  cout << endl;

  return 0;
}
