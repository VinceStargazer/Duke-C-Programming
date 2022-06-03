#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r) {
  case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
  case FULL_HOUSE: return "FULL_HOUSE";
  case FLUSH: return "FLUSH";
  case STRAIGHT: return "STRAIGHT";
  case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
  case TWO_PAIR: return "TWO_PAIR";
  case PAIR: return "PAIR";
  case NOTHING: return "NOTHING";
  default: return "INVALID";
  }
}

char value_letter(card_t c) {
  assert_card_valid(c);
  if (c.value <= 9) return c.value + '0';
  switch(c.value) {
  case 10: return '0';
  case VALUE_JACK: return 'J';
  case VALUE_QUEEN: return 'Q';
  case VALUE_KING: return 'K';
  case VALUE_ACE: return 'A';
  default: return 'N';
  }
}


char suit_letter(card_t c) {
  assert_card_valid(c);
  switch(c.suit) {
  case SPADES: return 's';
  case HEARTS: return 'h';
  case DIAMONDS: return 'd';
  case CLUBS: return 'c';
  default: return 'n';
  }
}

void print_card(card_t c) {
  printf("%c", value_letter(c));
  printf("%c", suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t c;
  if (value_let >= '2' && value_let <= '9')
    c.value = value_let - '0';
  else {
    switch(value_let) {
    case '0': c.value = 10; break;
    case 'J': c.value = VALUE_JACK; break;
    case 'Q': c.value = VALUE_QUEEN; break;
    case 'K': c.value = VALUE_KING; break;
    case 'A': c.value = VALUE_ACE; break;
    default: c.value = -1; break;
    }
  }
  
  switch(suit_let) {
  case 's': c.suit = SPADES; break;
  case 'h': c.suit = HEARTS; break;
  case 'd': c.suit = DIAMONDS; break;
  case 'c': c.suit = CLUBS; break;
  default: c.suit = NUM_SUITS; break;
  }
    
  assert_card_valid(c);
  return c;
}

card_t card_from_num(unsigned num) {
  card_t c;
  c.value = num % 13 + 2;
  c.suit = num / 13;
  assert_card_valid(c);
  return c;
}
