#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"

void free_future_cards(future_cards_t * fc) {
  for (size_t i = 0; i < fc -> n_decks; i++)
    free(fc -> decks[i].cards);
  free(fc -> decks);
  free(fc);
}

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  size_t size_d = fc -> n_decks;
  if (size_d <= index) {
    fc -> decks = realloc(fc -> decks, (index + 1) * sizeof(*(fc -> decks)));
    for (size_t i = size_d; i <= index; i++) {
      fc -> decks[i].cards = NULL;
      fc -> decks[i].n_cards = 0;
    }
    fc -> n_decks = index + 1;
  }
  deck_t * deck = fc -> decks + index;
  size_t size_c = deck -> n_cards;
  deck -> cards = realloc(deck -> cards, (size_c + 1) * sizeof(*(deck -> cards)));
  deck -> cards[size_c] = ptr;
  deck -> n_cards++;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  if (deck -> n_cards < fc -> n_decks)
    fprintf(stderr, "Deck size too small");
  for (size_t i = 0, k = 0; i < fc -> n_decks; i++) {
    deck_t * slots = fc -> decks + i;
    if (slots -> n_cards == 0) continue;
    for (size_t j = 0; j < slots -> n_cards; j++) {
      slots -> cards[j] -> value = deck -> cards[k] -> value;
      slots -> cards[j] -> suit = deck -> cards[k] -> suit;
    }
    k++;
  }
}
