//Bilbiotecas
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//Estrtutura para armazenar uma jogada
struct Move {
    //Atributos linha e coluna
    int row, col;
};

//Árvore de decisão do minimax
struct Node {
    Move move; //Atributo jogada
    int score; //Atributo de pontos para essa jogada
    vector<Node> children; //Atributo de possíveis jogadas a serem calculadas
};

//Classe tabuleiro
class Board {
    public:
        //Atributos
        char tab[3][3];

        //Construtor
        Board();

        //Métodos
        void drawBoard() const;
        bool isFull() const;
        bool isWinner(char player) const;
        bool isValidMove(int row, int col) const;
        void makeMove(Move move, char player);
        int evaluate(char player);
};

//Construtor
Board::Board() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            tab[i][j] = ' ';
}

/*
# drawBoard #
Função: Desenha um tabuleiro na tela
Parâmetros: 
    Nenhum
Valores de Retorno:
    Nenhum
*/
void Board::drawBoard() const {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << " " <<tab[i][j];
            if (j < 2) cout << " |";
        }
        cout << "\n";
        if (i < 2) cout << "-----------\n";
    }
}

/*
# isFull #
Função: Verifica se o tabuleiro já está totalmente preenchido
Parâmetros: 
    Nenhum
Valores de Retorno:
    bool true - Se o tabuleiro estiver totalmente preenchido
    bool false - Se o tabuleiro não estiver totalmente preenchido
*/
bool Board::isFull() const {
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            if (tab[i][j] == ' '){
                return false;           //Retorno se não estiver vazio
            }
        }
    }

    return true;                        //Retorno se estiver vazio
}

/*
# isWinner #
Função: Verifica se o jogador venceu
Parâmetros: 
    char player - Jogador a ser conferido se ganhou
Valores de Retorno:
    bool true - Se o jogador ganhou
    bool false - Se o jogador não ganhou
*/
bool Board::isWinner(char player) const {
    for(int i = 0; i < 3; i++){
        if( (tab[i][0] == player && tab[i][1] == player && tab[i][2] == player) |
            (tab[0][i] == player && tab[1][i] == player && tab[2][i] == player) |
            (tab[0][0] == player && tab[1][1] == player && tab[2][2] == player) |
            (tab[0][2] == player && tab[1][1] == player && tab[2][0] == player)){
            return true;
        }
    }

    //Se o jogador não tiver ganho
    return false;     
}

/*
# isValidMove #
Função: Verifica se uma jogada é possível
Parâmetros: 
    int row - Linha a ser feita a jogada
    int col - Coluna a ser feita a jogada
Valores de Retorno:
    bool true - Se a jogada é válida
    bool false - Se a jogada não é válida
*/
bool Board::isValidMove(int row, int col) const {
    //Verifica se a posição da jogada é válida através da linha e da coluna
    return row >= 0 && row < 3 && col >= 0 && col < 3 && tab[row][col] == ' ';
}

/*
# makeMove #
Função: Executa uma jogada
Parâmetros: 
    Move move - A jogada a ser feita
    char player - O jogador que está realizando a jogada
Valores de Retorno:
    Nenhum
*/
void Board::makeMove(Move move, char player) {
    tab[move.row][move.col] = player;
}

/*
# evaluate #
Função: Avalia o estado do tabuleiro para um jogador
Parâmetros: 
    char player - Jogador a ser avaliado
Valores de Retorno:
    int - Resultado númerico da avaliação
*/
int Board::evaluate(char player) {
    if (isWinner(player)) return player == 'O' ? 10 : -10;
    return 0;
}

//Função minimax
int minimax(Board board, int depth, bool maximizingPlayer, Node& node) {
    //Avalia o estado do jogo
    if (depth == 0 || board.isFull()) {
        //Calcula o estado do tabuleio dos jogadores
        node.score = board.evaluate(maximizingPlayer ? 'O' : 'X');
        //Retorno da avaliação
        return node.score;
    }

    if (maximizingPlayer) {                                                     //Se for o turno do jogador
        int maxScore = INT_MIN;
        //Teste de todas as jogadas possíveis
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.isValidMove(i, j)) {                                  //Se a jogada for válida             
                    Node childNode;                                             //Cria um nó filho
                    childNode.move = {i, j};                                    //O nó passa ter o movimento
                    board.makeMove(childNode.move, 'O');                        //Realiza uma jogada
                    int score = minimax(board, depth - 1, false, childNode);    //Faz uma avaliação
                    board.makeMove(childNode.move, ' ');                        //Desfaz a jogada
                    if (score > maxScore) {                                     //Se a pontuação obtida for maior
                        maxScore = score;                                       //Armazena a nova avaliação
                        node.children.push_back(childNode);                     //Desfaz a última jogada
                    }
                }
            }
        }
        node.score = maxScore;      //Armazena a avaliação       
        return maxScore;            //Retorno da avaliação
    } else {                                                                    //Se não for o turno do jogador
        int minScore = INT_MAX;
        // Testa todas as jogadas possíveis
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.isValidMove(i, j)) {                                  //Se a jogada for válida
                    Node childNode;                                             //Cria um nó filho
                    childNode.move = {i, j};                                    //O nó passa ter o movimento
                    board.makeMove(childNode.move, 'X');                        //Realiza uma jogada
                    int score = minimax(board, depth - 1, true, childNode);     //Faz uma avaliação
                    board.makeMove(childNode.move, ' ');                        //Desfaz a jogada
                    if (score < minScore) {                                     //Se a pontuação obtida for maior
                        minScore = score;                                       //Armazena a nova avaliação
                        node.children.push_back(childNode);                     //Desfaz a última jogada
                    }   
                }
            }
        }
        node.score = minScore;  //Armazena a avaliação 
        return minScore;        //Retorno da avaliação
    }
}

/*
# getBestMove #
Função: Encontra a melhor jogada usando minimax
Parâmetros: 
    Board& board - Tabuleiro atual
    int depth - Tamanho do tabuleiro
Valores de Retorno:
    Move - A melhor jogada
*/
Move getBestMove(Board& board, int depth) {
    //Cria uma árvore para permitir as verificações
    Node rootNode;

    //Uso da função minimax
    minimax(board, depth, true, rootNode);


    int bestScore = INT_MIN;
    Move bestMove = {-1, -1};
    //Escolhe a jogada com a melhor pontuação
    for (const Node& child : rootNode.children) {
        //Se a jogada sendo verificada possuir uma pontuação maior
        if (child.score > bestScore) {
            bestScore = child.score;    //Anota a pontuação do nó filho
            bestMove = child.move;      //Anota a jogada do nó filho
        }
    }
    //Retorna a melhor jogada
    return bestMove;
}

/*
# getPlayerMove #
Função: Obtém a jogada do jogador humano
Parâmetros: 
    const Board& board - O tabuleiro atual
Valores de Retorno:
    Move - A jogada do jogador
*/
Move getPlayerMove(const Board& board) {
    //Criação de linha e coluna
    int row, col;

    //Coleta da jogada
    cout << endl << "Digite uma linha e uma coluna (0-2): ";
    cin >> row >> col;
    //Enquanto a jogada não for válida
    while (!board.isValidMove(row, col)){
        cout << "Realize uma jogada valida: ";
        cout << endl << "Digite uma linha e uma coluna (0-2): ";
        //Coleta uma nova jogada
        cin >> row >> col;
    }

    //Retorno da jogada
    return {row, col};
}