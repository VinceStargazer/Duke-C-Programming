#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  card_t ** cards = hand -> cards;
  size_t size = hand -> n_cards;
  for (int i = 0; i < size; i++) {
    print_card(*cards[i]);
    if (i < size - 1)  printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t ** cards = d -> cards;
  size_t size = d -> n_cards;
  for (int i = 0; i < size; i++) {
    card_t card = *cards[i];
    if (card.value == c.value && card.suit == c.suit)
      return 1;
  }
  return 0;
}

void shuffle(deck_t * d){
  card_t ** cards = d -> cards;
  size_t size = d -> n_cards;
  for (int i = size; i > 1; i--) {
    int idx = rand() % i;
    card_t temp = *cards[idx];
    *cards[idx] = *cards[i - 1];
    *cards[i - 1] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  card_t ** cards = d -> cards;
  size_t size = d -> n_cards;
  for (int i = 0; i < size; i++) {
    card_t c1 = *cards[i];
    for (int j = i + 1; j < size; j++) {
      card_t c2 = *cards[j];
      assert(c1.value != c2.value || c1.suit != c2.suit);
    }
  }   
}

void add_card_to(deck_t * deck, card_t c) {
  card_t ** cards = deck -> cards;
  size_t size = deck -> n_cards;
  deck -> cards = realloc(deck -> cards, (size + 1) * sizeof(*cards));
  deck -> cards[size] = malloc(sizeof(**cards));
  deck -> cards[size] -> value = c.value;
  deck -> cards[size] -> suit = c.suit;
  deck -> n_cards++;
}

card_t * add_empty_card(deck_t * deck) {
  card_t unknown = {0, NUM_SUITS};
  size_t size = deck -> n_cards;
  add_card_to(deck, unknown);
  return deck -> cards[size];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * d = malloc(sizeof(*d));
  d -> cards = NULL;
  d -> n_cards = 0;
  for (size_t i = 0; i < 52; i++) {
    card_t c = card_from_num(i);
    if (deck_contains(excluded_cards, c) == 0)
      add_card_to(d, c);
  }
  return d;
}

void free_deck(deck_t * deck) {
  for (size_t i = 0; i < deck -> n_cards; i++)
    free(deck -> cards[i]);
  free(deck -> cards);
  free(deck);
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * excluded = malloc(sizeof(*excluded));
  excluded -> cards = NULL;
  excluded -> n_cards = 0;
  for (size_t i = 0; i < n_hands; i++) {
    deck_t * hand = hands[i];
    for (size_t j = 0; j < hand -> n_cards; j++) {
      card_t c = *(hand -> cards[j]);
      if (c.value >= 2) add_card_to(excluded, c);
    }
  }
  deck_t * res = make_deck_exclude(excluded);
  free_deck(excluded);
  return res;
}

void free_hands(deck_t ** hands, size_t n_hands) {
  for (size_t i = 0; i < n_hands; i++)
    free_deck(hands[i]);
  free(hands);
}
