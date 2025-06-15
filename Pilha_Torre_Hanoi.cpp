#include <iostream>
#include <stdexcept>
using namespace std;

class pilha {
private:
    int* elementos;
    int tamanho_lista;
    int topo;

public:
    pilha(int tamanho) {
        tamanho_lista = tamanho;
        elementos = new int[tamanho_lista];
        topo = -1;
    }

    ~pilha() {
        delete[] elementos;
    }

    void empilha(int elemento) {
        if (topo != tamanho_lista - 1) {
            topo++;
            elementos[topo] = elemento;
        } else {
            cout << "Pilha cheia!" << endl;
            throw overflow_error("Pilha cheia!");
        }
    }

    int desempilha() {
        if (topo == -1) {
            cout << "Pilha vazia!" << endl;
            throw out_of_range("Pilha vazia!");
        }
        return elementos[topo--];
    }

    int ler_topo() {
        if (topo == -1) {
            cout << "Pilha vazia!" << endl;
            throw out_of_range("Pilha vazia!");
        }
        return elementos[topo];
    }

    bool pilha_esta_vazia() {
        return topo == -1;
    }

    bool pilha_esta_cheia() {
        return topo == tamanho_lista - 1;
    }

    void troca() {
        if (topo < 1) {
            cout << "Não é possível trocar, pilha vazia ou com apenas um elemento!" << endl;
            throw out_of_range("Pilha vazia ou com apenas um elemento!");
        }
        int temp = elementos[topo];
        elementos[topo] = elementos[topo - 1];
        elementos[topo - 1] = temp;
    }

    int tamanho() {
        return topo + 1;
    }
};

string repetir_string(const string& s, int n) {
    string resultado;
    for (int i = 0; i < n; ++i) {
        resultado += s;
    }
    return resultado;
}

void imprimir_pilhas (pilha& A, pilha& B, pilha& C, int altura_max = 3, int intervalo_impressao = 1) {
    static int contador = 1;
    contador++;
    if (contador % intervalo_impressao != 0) {
        return; // Não imprimir se não for o intervalo correto
    }
    cout << intervalo_impressao-1 << " Intervalo(s) pulado(s)" << endl;
    auto print_disco = [](int tamanho, int largura_espaco) {   // Faz a impressão de um disco e o espaço ao redor dele
        cout << repetir_string(" ", largura_espaco);
        for (int i = 0; i < tamanho; ++i) cout << "#";
        cout << "|";
        for (int i = 0; i < tamanho; ++i) cout << "#";
        cout << repetir_string(" ", largura_espaco);
    };

    // Imprimir de cima para baixo
    pilha A2(altura_max);
    pilha B2(altura_max);
    pilha C2(altura_max);
    cout << endl;
    for (int i = altura_max ; i >= 0; --i) {
        // Torre A
        if (i < A.tamanho()) {
            int topo = A.ler_topo();
            A2.empilha(topo);
            print_disco(A.desempilha(), altura_max - topo);
        }
        else cout << repetir_string(" ", altura_max) << "|" << repetir_string(" ", altura_max);

        cout << " ";
        // Torre B
        if (i < B.tamanho()) {
            int topo = B.ler_topo();
            B2.empilha(topo);
            print_disco(B.desempilha(), altura_max - topo);
        }
        else cout << repetir_string(" ", altura_max) << "|" << repetir_string(" ", altura_max);
        cout << " ";
        // Torre C
        if (i < C.tamanho()) {
            int topo = C.ler_topo();
            C2.empilha(topo);
            print_disco(C.desempilha(), altura_max - topo);
        }
        else cout << repetir_string(" ", altura_max) << "|" << repetir_string(" ", altura_max);
        cout << endl;
    }
    for (int i = 0; i < 3; ++i) {
        cout << repetir_string("_", altura_max) << "|" << repetir_string("_", altura_max) << " ";
    }
    cout << endl;
    cout << repetir_string(" ", altura_max)<< "A" << repetir_string(" ", 2* altura_max)<< "B" << repetir_string(" ", 2* altura_max)<< "C" << endl;
    // Restaurar as pilhas
    while (!A2.pilha_esta_vazia()) {
        A.empilha(A2.desempilha());
    }
    while (!B2.pilha_esta_vazia()) {
        B.empilha(B2.desempilha());
    }
    while (!C2.pilha_esta_vazia()) {
        C.empilha(C2.desempilha());
    }
    std::cin.ignore(); // Espera por uma entrada do usuário para continuar
}

void mover_disco(pilha& origem, pilha& destino) {
    if (origem.pilha_esta_vazia()) {
        cout << "Não é possível mover, pilha de origem vazia!" << endl;
        throw out_of_range("Pilha de origem vazia!");
    }
    int disco = origem.desempilha();
    destino.empilha(disco);
}

void resolver_torre_hanoi(int n, pilha& origem, pilha& destino, pilha& auxiliar,
     pilha& origem2, pilha& destino2, pilha& auxiliar2, int n2, int intervalo_impressao = 1) {
    // Os outros são váriaveis auxiliares que não mudam conforme a função é chamada. n2 é o tamanho da pilha original.
    if (n == 1) {
        mover_disco(origem, destino);
        imprimir_pilhas(origem2, destino2, auxiliar2, n2, intervalo_impressao);
    } else {
        resolver_torre_hanoi(n - 1, origem, auxiliar, destino, origem2, destino2, auxiliar2, n2, intervalo_impressao);
        mover_disco(origem, destino);
        imprimir_pilhas(origem2, destino2, auxiliar2, n2, intervalo_impressao);
        resolver_torre_hanoi(n - 1, auxiliar, destino, origem, origem2, destino2, auxiliar2, n2, intervalo_impressao);
    }
}
int main() {
    int n = 5;
    pilha A(n);
    pilha B(n);
    pilha C(n);
    for (int i = n; i >= 1; --i) {
        A.empilha(i);
    }

    imprimir_pilhas(A, B, C, n);
    resolver_torre_hanoi(A.tamanho(), A, C, B, A, C, B, A.tamanho(), 2);
    imprimir_pilhas(A, B, C, n);
    return 0;
}