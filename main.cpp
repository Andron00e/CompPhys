#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <iterator>

using namespace ::std;

class bus{
public:
    double pass;
    int coord;
    int spd;
    int ttstay;
};

class ostanovka{
public:
    double pop;
    const int coord;
    int ttstay;
};


int main() {
    int N = 8; // число автобусов
    int M = 10; // число остановок
    int S = 30000; // длина круга
    int V = 40; // скорость
    int K = 10000; //

    // int timer = 0;
    // const double a = 1;
    // const double b = 1;
    // длина маршрута S

    std::vector<bus> buses;
    std::vector<ostanovka> osts;

    for (int i = 0; i < N; i++){ // создаем вектор автобусов
        bus bus{0, 3200*(N - i), V, 0};
        buses.push_back(bus);
        cout << buses[i].coord << " ";
    }
    cout << endl;
     for (int i = 0; i<M; i++){ // создаем вектор остановки
        ostanovka ost{0, i * 2800, 0};
        osts.push_back(ost);
        cout << osts[i].coord << " ";
    }
    cout << endl;
    vector<int> glob_dist;

    for (int i=0; i<4000; i++ ){ // на каждый тик
        /* Для каждой остановки популяция увеличивается на рандомное число
            Автобус двигается на spd вперед. Затем если координата совпадает с координатой остановки, spd == 0.
            Популяция остановки до 0, популяция автобуса уменьшается на 1/14 * rand, увеличивается на популяцию остановки.
            ttstay увеличивается до a(выходящие + популяция остановки). Если ttstay != 0, уменьшается на 1.
        */
        if ((i % 10) == 0){
            int R = 0;
            int matrix[8][8];
            for (int m = 0; m<N; m++){
                for (int l = 0; l<N; l++){
                    matrix[m][l] = 30000;
                }
                cout << endl;
            }

            // engage distance calculation
            for (int ita = 0; ita<N; ita++){
                for (int kta = N-1; kta>ita; kta--){
                    double p = min(abs(buses[ita].coord - buses[kta].coord), S - abs(buses[ita].coord - buses[kta].coord));
                    matrix[ita][kta] = p; matrix[kta][ita] = p;
                }
            }

            for (int m = 0; m<N; m++){
                int min_el = matrix[m][0];
                for (int l = 0; l<N; l++){
                    if (matrix[m][l] < min_el)
                        min_el = matrix[m][l];
                }
                cout << min_el << " ";
                R += min_el;
            }
            glob_dist.push_back(R/N);
        }


        for (int i = 0; i<N; i++){ // на каждый автобус

            if ((buses[i].ttstay == 0) or (buses[i].ttstay == 1)){
                buses[i].coord = (buses[i].coord + buses[i].spd) % S;
                buses[i].ttstay = 0; // автобус двигается, если не на остановке
            } else {
                buses[i].ttstay -= 1;
                }


            for (int j = 0; j<M; j++){
                if (buses[i].coord == osts[j].coord){

                    if (osts[j].ttstay == 0){
                        double v2 = rand() % 3;
                        int out = v2 * int(buses[i].pass / M); // сколько народу выходит?
                        int in = int(osts[j].pop); // заходят все

                        buses[i].ttstay = (in + out);
                        //buses[i].ttstay = osts[j].pop;
                        osts[j].ttstay = buses[i].ttstay;


                        buses[i].pass -= out;
                        buses[i].pass += in;
                        osts[j].pop = 0;
                } else if ((buses[i].ttstay == 0) and (osts[j].ttstay != 0)){buses[i].ttstay = K; }

                }
            }
        }

        for (int k=0; k<M; k++){
            std::srand(std::time(nullptr));
            double v1 = rand() % 2 + 1;
            osts[k].pop += 0.1 * v1; // популяция остановок увеличивается
            if (osts[k].ttstay != 0){
                osts[k].ttstay -= 1;
            }
        }
        
        //cout << osts[0].pop << endl;
        //for (int i=0; i<N; i++){
        //    cout << buses[i].coord << " " ;
        //}
        cout << endl;
    }

    for (int i=0; i<glob_dist.size(); i++){
        cout << glob_dist[i] << endl;
    }

    return 0;
}

