#include "card.h"

Card cardFromCharacter(const char& cardCharacter) {
    Card card;
    switch (cardCharacter) {
        case '2': card = TWO; break;
        case '3': card = THREE; break;
        case '4': card = FOUR; break;
        case '5': card = FIVE; break;
        case '6': card = SIX; break;
        case '7': card = SEVEN; break;
        case '8': card = EIGHT; break;
        case '9': card = NINE; break;
        case 'T': card = TEN; break;
        case 'J': card = JACK; break;
        case 'Q': card = QUEEN; break;
        case 'K': card = KING; break;
        case 'A': card = ACE; break;
        default: card = ERROR;
    }
    return card;
}

char getCardCharacter(Card card) {
    switch (card) {
        case TWO:   return '2';
        case THREE: return '3';
        case FOUR:  return '4';
        case FIVE:  return '5';
        case SIX:   return '6';
        case SEVEN: return '7';
        case EIGHT: return '8';
        case NINE:  return '9';
        case TEN:   return 'T';
        case JACK:  return 'J';
        case QUEEN: return 'Q';
        case KING:  return 'K';
        case ACE:   return 'A';
        default:    return '_';
    }
}
