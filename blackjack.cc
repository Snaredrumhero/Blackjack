/**
 *   @file: blackjack.cc
 * @author: Drew Mullett
 *   @date: 02/19/2022
 *  @brief: Uses functions to draw
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>

using namespace std;

string draw_card(int card_number, int &player_total, int &dealer_total, bool player_or_dealer);
bool dealer_redraw(int dealer_total);
void who_won(int player_total, int dealer_total);

int main()
{
    char play_again;
    do
    {
        int random_number, card, card_two, player_total = 0, dealer_total = 0;
        bool player_or_dealer = true, keep_going = true, skip_dealer = true;
        char hit_stand;

        srand(time(nullptr));
        random_number = rand();
        card = random_number % 13 + 1;
        random_number = rand();
        card_two = random_number % 13 + 1;

        cout << "Player: " << draw_card(card, player_total, dealer_total, player_or_dealer) << " ";
        cout << draw_card(card_two, player_total, dealer_total, player_or_dealer) << endl;
        cout << "Player total: " << player_total << "\n"
             << endl;

        player_or_dealer = false;
        random_number = rand();
        card = random_number % 13 + 1;
        cout << "Dealer: " << draw_card(card, player_total, dealer_total, player_or_dealer) << endl;
        cout << dealer_total << endl;

        do
        {
            cout << "Hit or stand? ";
            cin >> hit_stand;
            hit_stand = toupper(hit_stand);
            cout << endl;

            if (hit_stand != 'S' && hit_stand != 'H')
            {
                cout << "Error, please enter h or s" << endl;
            }
            if (hit_stand == 'H')
            {
                player_or_dealer = true;
                random_number = rand();
                card = random_number % 13 + 1;
                cout << draw_card(card, player_total, dealer_total, player_or_dealer) << endl;
                cout << "Player total: " << player_total << endl;
                if (player_total > 21)
                {
                    cout << "Busted! Dealer wins" << endl;
                    skip_dealer = false;
                    keep_going = false;
                }
                if (player_total == 21)
                {
                    cout << "Blackjack!" << endl;
                    keep_going = false;
                }
            }

        } while (hit_stand != 'S' && keep_going);

        while (skip_dealer)
        {
            player_or_dealer = false;
            if (dealer_redraw(dealer_total))
            {
                random_number = rand();
                card = random_number % 13 + 1;
                cout << "Dealer: " << draw_card(card, player_total, dealer_total, player_or_dealer) << endl;
                cout << "Dealer total: " << dealer_total << endl
                     << endl;
                if (dealer_total > 21)
                {
                    cout << "Busted! Player wins" << endl;
                    skip_dealer = false;
                }
                if (player_total == 21)
                {
                    cout << "Blackjack!" << endl;
                    skip_dealer = false;
                }
            }
            else
            {
                skip_dealer = false;
            }
        }
        who_won(player_total, dealer_total);

        cout << "Good game! \nPlay again (y/n)? ";
        cin >> play_again;
        cout << endl;
        play_again = toupper(play_again);
    } while (play_again != 'N');

    return 0;
}

string draw_card(int card_number, int &player_total, int &dealer_total, bool player_or_dealer)
{
    string card;
    switch (card_number)
    {
    case 1:
        card = "Ace";
        break;
    case 2:
        card = "Two";
        break;
    case 3:
        card = "Three";
        break;
    case 4:
        card = "Four";
        break;
    case 5:
        card = "Five";
        break;
    case 6:
        card = "Six";
        break;
    case 7:
        card = "Seven";
        break;
    case 8:
        card = "Eight";
        break;
    case 9:
        card = "Nine";
        break;
    case 10:
        card = "Ten";
        break;
    case 11:
        card = "Jack";
        break;
    case 12:
        card = "Queen";
        break;
    case 13:
        card = "King";
        break;
    default:
        card = "Error when drawing card";
    }
    if (card_number >= 10)
    {
        card_number = 10;
    }
    if (player_or_dealer)
    {
        player_total += card_number;
    }
    else
    {
        dealer_total += card_number;
    }
    return card;
}

bool dealer_redraw(int dealer_total)
{
    if (dealer_total < 17)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void who_won(int player_total, int dealer_total)
{
    if (player_total <= 21 && dealer_total <= 21)
    {
        if (player_total < dealer_total)
        {
            cout << "Dealer wins" << endl;
        }
        else if (dealer_total < player_total)
        {
            cout << "Player wins!" << endl;
        }

        else if (player_total == dealer_total)
        {
            cout << "Push! Everyone loses!" << endl;
        }
    }
}