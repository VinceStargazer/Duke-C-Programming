#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"

int main(void) {
  future_cards_t * fc = malloc(sizeof(*fc));
  fc -> decks = NULL;
  fc -> n_decks = 0;
  
  deck_t * d = malloc(sizeof(*d));
  d -> cards = NULL;
  d -> n_cards = 0;
  char vals[] = "KKQQ0999", suits[] = "shshsdch";
  for (size_t i = 0; i < 8; i++) 
    add_card_to(d, card_from_letters(vals[i], suits[i]));
  add_future_card(fc, 0, add_empty_card(d));
  add_future_card(fc, 1, add_empty_card(d));

  deck_t * d2 = malloc(sizeof(*d2));
  d2 -> cards = NULL;
  d2 -> n_cards = 0;
  char vals2[] = "AA987653", suits2[] = "shshsdch";
  for (size_t i = 0; i < 8; i++) 
    add_card_to(d2, card_from_letters(vals2[i], suits2[i]));
  add_future_card(fc, 0, add_empty_card(d2));
  add_future_card(fc, 2, add_empty_card(d2));

  deck_t * d3 = malloc(sizeof(*d3));
  d3 -> cards = NULL;
  d3 -> n_cards = 0;
  char vals3[] = "AK8", suits3[] = "shc";
  for (size_t i = 0; i < 3; i++) 
    add_card_to(d3, card_from_letters(vals3[i], suits3[i]));
  future_cards_from_deck(d3, fc);

  print_hand(d);
  printf("\n");
  print_hand(d2);
  printf("\n");
  print_hand(d3);

  free_deck(d);
  free_deck(d2);
  free_deck(d3);
  free(fc);
  return EXIT_SUCCESS;
}
