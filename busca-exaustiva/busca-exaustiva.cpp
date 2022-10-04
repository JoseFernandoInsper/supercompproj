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
  long double size;
  vector<int> sequencia;
  vector<bool> pass;
};

double calcula_distancias(cidade a, cidade b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}

double busca_exaustiva(int N, int i, long long int &num_leaf, solucao &melhor_solucao, solucao &solucao_atual, vector<cidade> &estado);

int main(){
  int N, O;
  double x, y, L;
  cin >> N;
  L = 0;
  O = 1;

  vector<cidade> estado;
  solucao melhor_solucao;
  solucao solucao_atual;
  melhor_solucao.size = 9999.0;
  melhor_solucao.pass = vector<bool> (N, false);
  solucao_atual.size = 9999.0;
  solucao_atual.pass = vector<bool> (N, false);
  long long int num_leaf = 0;

  for (int i =0; i<N ; i++) {
    cin >> x >> y;
    estado.push_back({i, x, y});
  }

  L  = busca_exaustiva(N, 0, num_leaf, melhor_solucao, solucao_atual, estado);

  cerr << "num_leaf " << num_leaf << endl;
  cout << L << " " << O << endl;
  for(auto & c : melhor_solucao.sequencia){
    cout << c << " ";
  }
  cout << endl;

  return 0;
}

double busca_exaustiva(int N, int i, long long int &num_leaf, solucao &melhor_solucao, solucao &solucao_atual, vector<cidade> &estado){

  //encontrou uma solução valida
  if(solucao_atual.sequencia.size() == N){
    solucao_atual.size += calcula_distancias(estado[0], estado[i]);
    num_leaf += 1;
    if(solucao_atual.size < melhor_solucao.size){
      melhor_solucao = solucao_atual;

    }
    return melhor_solucao.size;
  }

  //sequencia incompleta
  if(solucao_atual.sequencia.empty()){
    solucao_atual.size = 0;
    solucao_atual.sequencia.push_back(i);
    solucao_atual.pass[i] = true;
  } else {
    solucao_atual.size += calcula_distancias(estado[i], estado[i+1]);
    solucao_atual.sequencia.push_back(i);
    solucao_atual.pass[i] = true;
  }
  if(solucao_atual.pass[i] == true){
    busca_exaustiva(N, i+1, num_leaf, melhor_solucao, solucao_atual, estado);
  }

  if(solucao_atual.sequencia.size() == N){
    busca_exaustiva(N, i, num_leaf, melhor_solucao, solucao_atual, estado);
  }
}
