#ifndef CARD_H
#define CARD_H

enum Card {
    ERROR = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

Card cardFromCharacter(const char& cardCharacter);
char getCardCharacter(Card card);