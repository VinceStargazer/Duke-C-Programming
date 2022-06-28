#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int main(int argc, char ** argv) {
  FILE * f = fopen(argv[1], "r");
  size_t sz = 0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc -> decks = NULL;
  fc -> n_decks = 0;
  
  deck_t ** decks = read_input(f, &sz, fc);
  for (size_t i = 0; i < sz; i++) {
    print_hand(decks[i]);
    free_deck(decks[i]);
    printf("\n");
  }
  free(decks);
  free(fc);
  if (fclose(f) != 0) {
    fprintf(stderr, "Can not close file '%s'\n", argv[1]);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
