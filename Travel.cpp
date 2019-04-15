#include <bits/stdc++.h>
using namespace std;

const int N = 20; // Algoritmo O(n!) portanto n não pode ser muito grande
const int INF = 1000000007;
using ll = long long;

int V, E;
int currentInitial;

vector<pair<int,int>> graph[N];

int distances[N][N];

// Um bfs para definir a menor distância entre current u -> v
// Poderiamos usar também o algoritmo de warshall
void Dijkstra(int Initial){

    // Definimos como infinita a distances de todo current ligado ao 'incial'

    for(int i = 0; i < V; i++)
        distances[Initial][i] = INF;

    // Criamos uma PQ para os elementos (para impedir a inclusão do mesmo elemento duas vezes)

    priority_queue<int> linec;

    linec.push(Initial);

    distances[Initial][Initial] = 0;

    while(!linec.empty()){ // Enquanto nao linec vazia

        int u = linec.top();

        linec.pop();

        for(auto v: graph[u]){ // Visitamos seus vizinhos

            // Se a distances do current atual pro vizinho for menor que a do Initial pro vizinho, atualizar

            if(v.first + distances[Initial][u] < distances[Initial][v.second]){

                distances[Initial][v.second] = distances[Initial][u] + v.first;

                linec.push(v.second); // E botar na linec
            }
        }
    }
}

pair<ll, vector<int>> TravellingSalesman(int current, ll bitmask){

    // Input = current atual e bitmask representando elementos visitados

    // Se estamos no current incial e bitmask NÃO é nula

    if(current == currentInitial and bitmask == (1<<V) - 1){

        // Se bitmask estiver preenchida temos um resultado válido (1<<V - 1 == 2^v - 1)

        vector<int> encontrado;
        encontrado.push_back(currentInitial);
        return make_pair(0, encontrado);

    }else if(current == currentInitial and (bitmask>>currentInitial & 1)){

        // Caso não esteja preenchida, resultado inválido (0 < bitmask < 2^v - 1)

        return make_pair((ll)INF*(ll)INF, vector<int>());

    }

    bitmask = bitmask + (1<<current); // Marcamos na bitmask que current atual foi visitado

    ll valor = (ll)INF * (ll)INF; // Declaramos valor infinito para Path atual
    vector<int> Path; // E declaramos a array de retorno

    for(int i = 0; i < V; i++){ // Para cada current ligado ao 'current'

        // Se não for igual ao próprio current e (não foi visito ou liga para o current Initial)

        if(i != current and (!((bitmask>>i) & 1) or i == currentInitial)){

            // Rodamos o caixeiro viajante recursivamente

            pair<ll, vector<int>> resultado = TravellingSalesman(i, bitmask);

            // Se o Path gerado pelo caixeiro for menor menor que o Path atualmente registrado

            if(resultado.first + distances[current][i] < valor){

                // Tomamos esse Path como a melhor resposta

                valor = resultado.first + distances[current][i];
                Path = resultado.second;

            }

        }

    }

    Path.push_back(current);

    return make_pair(valor, Path); // Retornando par de vector Path + valor do Path

}

int main(){

    std::cin>>V>>E;

    for(int i = 0; i < E; i++){

        int dist, u, v;

        std::cin>>u>>v>>dist;

        graph[u - 1].emplace_back(dist, v - 1); // Emplace_back já faz o par pra você

    }

    for(int i = 0; i < V; i++){
        Dijkstra(i);
    }

    std::cin>>currentInitial;

    currentInitial--;

    // Chamamos a DP no current Initial com bitmask zerada

    auto BestPath = TravellingSalesman(currentInitial, 0LL);

    // Se o Path deu maior que INF, esse Path passa por arestas notadas como inexistente
    // Portanto não existe

    if(BestPath.first >= INF)

        std::cout<<"Não existe Path do caixeiro viajante no graph dado\n";

    else{ // Mas caso exista, é retornado o par do valor e Path

        //std::cout<<"Tamanho do percurso do Path mais curto = "<<BestPath.first<<std::endl;

        auto vectorpath = BestPath.second;
        reverse(vectorpath.begin(), vectorpath.end());


        int a = 0;
        for(auto index: vectorpath)a++;
        std::cout<<(a-1)<<std::endl;
        for (int i = 0; i < (a-1); ++i){
            if (i<(a-1)){
                std::cout<<vectorpath[i]<<" "<<vectorpath[i+1]<<std::endl;
            }
            else{
                std::cout<<vectorpath[i]<<" "<<vectorpath[0]<<std::endl;
            }
        }

        //std::cout<<std::endl;
    }
}
