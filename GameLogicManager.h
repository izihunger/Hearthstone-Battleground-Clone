#include <memory>
#include "Player.h"
#include "Board.h"
#include "Shop.h"

class GameLogicManager
{
private:
    // Manage which player is playing
    bool m_player1Turn = true;
    std::unique_ptr<Player> m_player1;
    std::unique_ptr<Player> m_player2;
    std::shared_ptr<Board> m_board;
    std::unique_ptr<Shop> m_shop;

    // Number of turns
    size_t m_turn = 0;

public:
    GameLogicManager()
    {
        createPlayers();
        createBoard();
        createShop();
    }

    void createPlayers();
    void createBoard();
    void createShop();

    Board &getBoard() const { return *m_board; }
    Shop &getShop() const { return *m_shop; }
    Player &getPlayer1() const { return *m_player1; }
    Player &getPlayer2() const { return *m_player2; }

    //void startGame();
    void recruitementPhase();
    void battlePhase();
    void endPhase();
};
