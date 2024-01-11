//Bibliotecas
#include <iostream>
#include <vector>
#include <climits>
#include <C:\Users\UFSCar\Documents\Codigos\AEDD\func.hpp>
using namespace std;

//Função main
int main() {
    Board board;
    bool playerTurn = true;

    //Loop do jogo até o jogador ou computador vencer
    while (!board.isWinner('X') && !board.isWinner('O') && !board.isFull()) {
        //Desenha o tabuleiro
        board.drawBoard();

        if (playerTurn) {                               //Se for o turno do jogador
            Move playerMove = getPlayerMove(board);     //Obtém a jogado do jogador
            board.makeMove(playerMove, 'X');            //Realiza a jogada
        } else {                                        //Se não for o turno do jogador
            Move computerMove = getBestMove(board, 9);  //Obtém a jogado do computador
            board.makeMove(computerMove, 'O');          //Realiza a jogada
            cout << endl << "Jogada do Computador:" << endl << endl;
        }

        //Alterna entre a jogada do computador e do jogador
        playerTurn = !playerTurn;
    }

    //Exibe o resultado final
    board.drawBoard();
    if (board.isWinner('X')) {              //Se o jogador venceu
        cout << "Voce venceu!\n";       
    } else if (board.isWinner('O')) {       //Se o computador venceu
        cout << "O computador venceu!\n";
    } else {                                
        cout << "Empate!\n";                //Se foi empate
    }

    //Finalização do programa
    return 0;
}
