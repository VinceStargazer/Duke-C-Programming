#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * d = malloc(sizeof(*d));
  d -> cards = NULL;
  d -> n_cards = 0;
  for (size_t i = 0; str[i] != '\n'; i++) {
    if (str[i] == '?') {
      size_t num = str[i + 1] - '0';
      if (isdigit(str[i + 2])) {
	num = 10 * num + str[i + 2] - '0';
	i++;
      }
      add_future_card(fc, num, add_empty_card(d));
    } else {
      card_t c = card_from_letters(str[i], str[i + 1]);
      add_card_to(d, c);
    }
    i++;
    while (isspace(str[i + 1]) && str[i + 1] != '\n') i++;
  }
  return d;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** res = NULL;
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    res = realloc(res, ((*n_hands) + 1) * sizeof(*res));
    deck_t * d = hand_from_string(line, fc);
    if (d -> n_cards < 5) {
      for (size_t i = 0; i < *n_hands; i++) free_deck(res[i]);
      free(line);
      fprintf(stderr, "Less than 5 cards\n");
      assert(d -> n_cards >= 5);
      return NULL;
    }
    res[*n_hands] = d;
    (*n_hands)++;
  }
  free(line);
  return res;
}
