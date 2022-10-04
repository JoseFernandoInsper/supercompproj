#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

struct cidade {
  int id;
  double x, y;
  bool pass = false;
  double distancia;
};

struct solucao {
  int id;
  double size;
  vector<int> sequencia;
};

double calcula_distancias(vector<cidade> &rand_ordem, int N) {
  double dist_total = 0;
  double dx, dy;
  for(int i = 0; i < N; i++){
    if(i == N-1){
      dx = rand_ordem[N-1].x - rand_ordem[0].x;
      dy = rand_ordem[N-1].y - rand_ordem[0].y;
      dist_total += sqrt(dx*dx + dy*dy);
    } else{
      dx = rand_ordem[i].x - rand_ordem[i+1].x;
      dy = rand_ordem[i].y - rand_ordem[i+1].y;
      dist_total += sqrt(dx*dx + dy*dy);
    }
  }
  return dist_total;
}

bool menor_tour(solucao a, solucao b){
  return (a.size < b.size);
}

int main() {

  int N, O;
  double x, y, L;

  cin >> N;
  O = 0;
  L = 0;
  int seed = 10;

  vector<cidade> estado;
  vector<solucao> solucoes;
  estado.reserve(N);
  solucoes.reserve(10*N);

  for (int i =0; i<N ; i++) {
    cin >> x >> y;
    estado.push_back({i, x, y});
  }
  
  default_random_engine generator (seed);
  uniform_real_distribution<double> distribution(0.0,1.0);

  for(int sol = 0; sol<10*N; sol++){
    int c = 0;
    double novo_L;
    vector<cidade> rand_ordem;
    vector<int> tour;
    tour.reserve(N);
    rand_ordem.reserve(N);

    //aleatorização
    while(c< N){
      for(int i = 0; i < N; i++){
        double rand = distribution(generator);
        if(rand >= 0.5 && !estado[i].pass){
          tour.push_back(estado[i].id);
          rand_ordem.push_back(estado[i]);
          estado[i].pass = true;
          c++;
        }
      }
    }

    //troca de ordem
    for(int i = 0; i<N; i++){
      for(int j = 0; j<N; j++){
        if(i != j){
          vector<cidade> nova_ordem;
          nova_ordem = rand_ordem;

          nova_ordem[i] = rand_ordem[j];
          nova_ordem[j] = rand_ordem[i];

          L = calcula_distancias(rand_ordem, N);
          novo_L = calcula_distancias(nova_ordem, N);
          if(novo_L < L){
            rand_ordem[i] = nova_ordem[i];
            rand_ordem[j] = nova_ordem[j];
            tour[i] = rand_ordem[i].id;
            tour[j] = rand_ordem[j].id;
            L = novo_L;
          }
        }
      }
    }
    solucao s;
    s.id = sol;
    s.size = L;
    s.sequencia = tour;
    solucoes.push_back(s);

    //check em saida de erro
    cerr << L << " " << O << endl;
    for(int p : tour){
      cerr << p << " ";
    }
    cerr << endl;

    //reset estado
    for(auto &q : estado){
      q.pass = false;
    }
    rand_ordem.clear();
    tour.clear();
  }
  sort(solucoes.begin(), solucoes.end(), menor_tour);
  
  L = solucoes[0].size;
  vector<int> sec;
  sec = solucoes[0].sequencia;

  cout << L << " " << O << endl;
  for(int c : sec){
    cout << c << " ";
  }
  cout << endl;

  return 0;
}
