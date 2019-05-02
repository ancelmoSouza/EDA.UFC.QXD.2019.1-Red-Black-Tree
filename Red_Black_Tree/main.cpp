#include <iostream>
#include <cstdlib>

using namespace std;

//Defien a cor do nó como Vermelha(RED) ou Preta(BLACK)
enum Cor{
    RED =  false,
    BLACK = true

};

//Struct para definir os nós
struct Node{
    int value;
    struct Node * left;
    struct Node * rigth;
    struct Node * pai;
    Cor cor;
};

//Classe que refine a Árvore Rubro-Negra
class RBTree{
public:
    RBTree();
    Node * rb_search(int value);
    void insert(int value);   // Método de chamada da inserção
    void insertFixup(Node * z); // Método para correção da árvore após a inserção de um nó

    void heigth();  //Exibe a alturaa da árvore
    void rbDeleteAux(Node * z); //Executa a remoção de um nó da árvore rubro-negra
    void deleteFixup(Node * x);

    void leftRotate(Node * x); // Rotação esquerda
    void rigthRotate(Node * x);   //Rotação direita

    void preOrder(); //Percurso em pre-ordem da árvore rubro negra
    void preOrderAux(Node * r); // Método auxiliar que realiza p percurso pre-ordem

    Node * getRoot();   //Retorna um ponteiro para a raiz da árvore
    void setRoot(Node * r); //Atribui um no à raiz da árvore

    Node * getNil(); //Retorna um ponteiro para o nó sentinela
    void setNil(Node * r);  //Atribui um nó para a sentinela

private:
    void insertAux(Node * z); // Método auxiliar que realiza
                                //inserção propiamente dita
    Node * minimun(Node * r);
    void transplant(Node * u, Node * v); //Transplanta um nó em outro
    int heigthAux(Node * r);

    Node * root; // Raiz da Árvore Rubro-Negra
    Node * nil;  //Nó sentinela da árvore rubro-negra
};


//Construtor
RBTree::RBTree(){
    this->nil = new Node;
    nil->cor = BLACK;
    nil->pai = nil;
    nil->left = nil;
    nil->rigth = nil;
    this->root = nil;
}

// Percuso Pré-Ordem
void RBTree::preOrder(){
    preOrderAux(getRoot());
}

//Método Auxiliar para calcular a altura
int RBTree::heigthAux(Node *r){
    int maior = 0;

    if(r == getNil())
        return 0;

    int hLeft = this->heigthAux(r->left);
    int hRigth = this->heigthAux(r->rigth);

    if(hLeft >= hRigth)
        maior = hLeft;
    else
        maior = hRigth;

    return (1 + maior);
}

//Método que exibe o valor da altura da árvore
void RBTree::heigth(){
      cout << "Altura da árvore: " << this->heigthAux(getRoot()) << endl;
}

//Algorítmo auxiliar para o percurso em pre-ordem(pré-ordem propiamente dita
void RBTree::preOrderAux(Node *r){
    if(r != nil){
        cout << "[" << r->value << ":";
        if(r->cor == BLACK)
            cout << "BLACk]" << endl;
         else
            cout << "RED]" << endl;

        preOrderAux(r->left);
        preOrderAux(r->rigth);
    }
}


//Rotaçaõ esquerda
void RBTree::leftRotate(Node * x)
{
    Node * y = new Node;
    y = x->rigth;
    x->rigth = y->left;

    if(y->left != nil)
        y->left->pai = x;
    y->pai = x->pai;

    if(x->pai == nil)
        root = y;
    else if(x == x->pai->left)
        x->pai->left = y;
    else
        x->pai->rigth = y;

    y->left = x;
    x->pai = y;
}

//Rotação direita
void RBTree::rigthRotate(Node * x)
{
    Node * y = new Node;
    y = x->left;
    x->left = y->rigth;

    if(y->rigth != nil)
        y->rigth->pai = x;
    y->pai = x->pai;

    if(x->pai == nil)
        root = y;
    else if(x == x->pai->left)
        x->pai->left = y;
    else
        x->pai->rigth = y;
    y->rigth = x;
    x->pai = y;

}

//Método para buscar um nó na árvore baseado na sua chave
Node * RBTree::rb_search(int value){
    Node * x = this->getRoot();
    Node * pai = this->getNil();

    while(x != nil && x->value != value){
        pai = x;
        if(value < x->value)
            x = x->left;
        else{   x = x->rigth; }
    }

    return x;
}

//Cria e chama a inserção para um valor específico
void RBTree::insert(int value){
    Node * z = new Node;
    z->left = nil;
    z->rigth = nil;
    z->pai = nil;
    z->value = value;
    z->cor = RED;
    insertAux(z);
}

//Realiza a inserção de um nó na árvore
void RBTree::insertAux(Node * z){
    Node * y = this->getNil();
    Node * x = this->getRoot();

    while (x != this->getNil()) {
        y = x;
        if(z->value < x->value)
            x = x->left;
        else
            x = x->rigth;
    }

    z->pai = y;

    if(y == nil)
        root = z;
    else if(z->value < y->value)
        y->left = z;
    else y->rigth = z;

    z->cor = RED;
    this->insertFixup(z);
}

//Rebalanceia a árvore após a inserção de um nó
void RBTree::insertFixup(Node *z){
    Node * y = new Node;
    while(z->pai->cor == RED){
        if(z->pai == z->pai->pai->left){
            y = z->pai->pai->rigth;

            if(y->cor == RED){
                z->pai->cor = BLACK;
                y->cor = BLACK;
                z->pai->pai->cor = RED;
                z = z->pai->pai;            }
            else{
                if(z == z->pai->rigth){
                    z = z->pai;
                    leftRotate(z);
                }else{
                    z->pai->cor = BLACK;
                    z->pai->pai->cor = RED;
                    rigthRotate(z->pai->pai);
                }
            }
        }
        else {
            y = z->pai->pai->left;
            if(y->cor == RED){
                z->pai->cor = BLACK;
                y->cor = BLACK;
                z->pai->pai->cor = RED;
                z = z->pai->pai;
            }
            else{
                if(z == z->pai->left){
                    z = z->pai;
                    rigthRotate(z);
                }else{
                    z->pai->cor = BLACK;
                    z->pai->pai->cor = RED;
                    leftRotate(z->pai->pai);
                }
            }
        }
    }
    this->root->cor = BLACK;
}

//Calcula o menor valor em m subárvore enraizada no Node * r
Node * RBTree::minimun(Node *r){
    Node * aux = r;
    if(r == this->getNil())
        return getNil();
    while (aux->left != getNil()) {
        aux = aux->left;
    }

    return aux;
}

//Métodos para realizar a remoção de um nó da
// árvore rubro-negra
void RBTree::transplant(Node *u, Node *v){

    if(u->pai == this->getNil())
        root = v;
    else if(u == u->pai->left)
        u->pai->left = v;
    else
        u->pai->rigth = v;
    v->pai = u->pai;
}


//Realiza a remoção de um nó
void RBTree::rbDeleteAux(Node *z){
    Node * y = z;
    Cor originalCorY = y->cor;
    Node * aux;

    if(z->left == getNil()){
        aux = z->rigth;
        transplant(z, z->rigth);
    }else if(z->rigth == getNil()){
        aux = z->left;
        transplant(z, z->left);
    }
    else{
        y = minimun(z->rigth);
        originalCorY = y->cor;
        aux = y->rigth;

        if(y->pai == z){
            aux->pai = y;
        }else{
            transplant(y, y->rigth);
            y->rigth = z->rigth;
            y->rigth->pai = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->pai = y;
        y->cor = z->cor;

        if(originalCorY == BLACK)
            deleteFixup(aux);
    }
}

//Rebalanceia a ávore após a remoção de um nó que faça-a violar as propiedades rubro-negras
void RBTree::deleteFixup(Node * x){
    while(x != getRoot() && x->cor == BLACK){
        if(x == x->pai->left){
            Node * w = x->pai->rigth;

            if(w->cor == RED){
                w->cor = BLACK;
                x->pai->cor = RED;
                leftRotate(x->pai);
                w = x->pai->rigth;
            }
            if(w->left->cor == BLACK && w->rigth->cor == BLACK){
                w->cor = RED;
                x = x->pai;
            }
            else{
                if(w->rigth->cor == BLACK){
                    w->left->cor = BLACK;
                    w->cor = RED;
                    rigthRotate(w);
                    w = x->pai->rigth;
                }
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                w->rigth->cor = BLACK;
                leftRotate(x->pai);
                this->setRoot(x);
            }
        }
        else{
            Node * w = x->pai->left;

            if(w->cor == RED){
                w->cor = BLACK;
                x->pai->cor = RED;
                rigthRotate(x->pai);
                w = x->pai->left;
            }
            if(w->left->cor == BLACK && w->rigth->cor == BLACK){
                w->cor = RED;
                x = x->pai;
            }
            else{
                if(w->left->cor == BLACK){
                    w->rigth->cor = BLACK;
                    w->cor = RED;
                    leftRotate(w);
                    w = x->pai->left;
                }
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                w->left->cor = BLACK;
                rigthRotate(x->pai);
                this->setRoot(x);
            }
        }
    }
    x->cor = BLACK;
}

/* Getters e Setters*/
Node * RBTree::getRoot()
{
    return root;
}

void RBTree::setRoot(Node * r)
{
    this->root = r;
}

Node * RBTree::getNil()
{
    return  nil;
}

void RBTree::setNil(Node * r)
{
    this->nil = r;
}


int main(){
    RBTree redBlackTree = RBTree();
    char option;
    Node * aux;
    int value;

    while (true) {
        cout << "------------------------ MENU ---------------------" << endl;
        cout << "(1) Inserir chave" << endl <<
                "(2) Remover chave" << endl <<
                "(3) Imprimir chaves(Pré-Ordem)" << endl <<
                "(4) Calcular altura" << endl <<
                "(5) Sair" << endl;
        cout << "--------------------------------------------------" << endl;

        cout << endl;
        cout << endl;

        cout << "Qual operação deseja realizar: ";
        cin >> option;

        switch (option) {
        case '1':
            cout << "Digite o valor: ";
            cin >> value;
            redBlackTree.insert(value);
            aux = redBlackTree.rb_search(value);

            cout << aux->value << endl;
            cin.get();

            break;
        case '2':
            cout << "Digite o valor: ";
            cin >> value;

            aux = redBlackTree.rb_search(value);
            if(aux == redBlackTree.getNil()){
                cout << "Erro: Não constam registros do valor escolhido" << endl <<
                        "Insira um valor válido" << endl;
            }
            else {
                redBlackTree.rbDeleteAux(aux);
            }

            cin.get();
            break;
        case '3':
            redBlackTree.preOrder();
            cin.get();
            break;
        case '4':
            redBlackTree.heigth();
            cin.get();
            break;
        case '5':
            cout << "Até mais..." << endl;
            return 0;
        default:
            cout << "Erro: Operação não disponível" << endl;
            cout << "Tente novamente" << endl;
            cin.get();
        }

        cout << "Pressiione <<-- Enter -->> para sair" << endl;
        cin.get();
        system("clear");
    }
}


