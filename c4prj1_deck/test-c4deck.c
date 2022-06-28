#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"

int main(void) {
  deck_t * d = malloc(sizeof(*d));
  d -> cards = NULL;
  d -> n_cards = 0;
  char vals[] = "KKQQ0999", suits[] = "shshsdch";
  for (size_t i = 0; i < 8; i++) 
    add_card_to(d, card_from_letters(vals[i], suits[i]));
  print_hand(d);
  printf("\n");
  
  unsigned * res = get_match_counts(d);
  for (size_t i = 0; i < 8; i++)
    printf("%d", res[i]);
  printf("\n");
  
  deck_t * other = make_deck_exclude(d);
  print_hand(other);
  printf("\n");
  
  deck_t * remain = build_remaining_deck(&other, 1);
  print_hand(remain);
  
  free_deck(d);
  free_deck(other);
  free_deck(remain);
  free(res);
 }
