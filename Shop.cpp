#include "Shop.h"
#include "Player.h"

void Shop::giveCard(std::unique_ptr<Card> &card, Player &player)
{
    player.addCardToHand(card);
}

unsigned int Shop::calculateGold(unsigned int turns) const
{
    // Cap it to 10 golds
    return turns > 10 ? 10 : turns + 3;
}

void Shop::createDeck()
{
    m_deck.push_back(std::make_unique<DeckSwabbie>());
    m_deck.push_back(std::make_unique<DeckSwabbie>());
    m_deck.push_back(std::make_unique<DeckSwabbie>());
    m_deck.push_back(std::make_unique<AlleyCat>());
    m_deck.push_back(std::make_unique<AlleyCat>());
    m_deck.push_back(std::make_unique<AlleyCat>());
}

void Shop::shuffleDeck()
{
    std::random_shuffle(m_deck.begin(), m_deck.end());
}

void Shop::displayCards() const
{
    std::cout << "draw cards : \n";
    for (int i = 0; i < m_choices.size(); i++)
    {
        std::cout << "Carte " << i + 1 << " : ";
        m_choices[i]->printName();
        std::cout << "\n";
    }
    std::cout << "Choisissez une carte (Entre 1 et " << m_choices.size() << ") and if you don't want to buy a card enter n : ";
}

std::vector<std::reference_wrapper<Card>> Shop::drawCards(Player &player)
{
    std::vector<std::reference_wrapper<Card>> cards;
    shuffleDeck();
    int count = 0;
    for (int i = 0; i < m_deck.size(); i++)
    {
        if (m_deck[i]->getRang() <= player.getLevel())
        {
            m_choices.push_back(std::move(m_deck[i]));
            cards.push_back(std::ref(*m_choices.back()));
            m_deck.erase(m_deck.begin() + i);
            if (++count == 3)
                break;
        }
    }
    displayCards();
    return cards;
}

void Shop::buyCard(int index, Player &player)
{
    if (index < 0 || index >= m_choices.size() || m_choices.empty())
        return;
    if (player.getGolds() >= 3)
    {
        giveGold(player, -3);
        giveCard(m_choices[index], player);
        m_choices.erase(m_choices.begin() + index);
    }
    else
    {
        std::cout << "You don't have enough golds to buy this card\n";
    }
}

void Shop::putCardBack()
{
    int size = m_choices.size();
    for (int i = 0; i < size; i++)
    {
        m_deck.push_back(std::move(m_choices[i]));
    }
    m_choices.clear();
}

void Shop::sellCard(std::unique_ptr<Card> &card, Player *player)
{
    // Add a gold to the player
    player->setGolds(player->getGolds() + 1);
    // card->setOwner(nullptr);
    //   Add the card to the shop
    m_deck.push_back(std::move(card));
}

void Shop::giveGold(Player &player, unsigned int turns) const
{
    player.m_golds += calculateGold(turns);
}

void Shop::reDrawCards(Player &player)
{
    if(player.getGolds() > 1){
        player.setGolds(player.getGolds() - 1);
        putCardBack();
        drawCards(player);
    }
}