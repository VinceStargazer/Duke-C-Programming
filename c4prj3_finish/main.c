#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"


int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "Insufficient arguments\n");
    return EXIT_FAILURE;
  }
  if (argc > 3) {
    fprintf(stderr, "Too many arguments\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Can not open file '%s'\n", argv[1]);
    return EXIT_FAILURE;
  }
  size_t n_hands = 0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc -> decks = NULL;
  fc -> n_decks = 0;
  deck_t ** hands = read_input(f, &n_hands, fc);
  deck_t * remains = build_remaining_deck(hands, n_hands);
  int count[(int) n_hands + 1];
  for (int i = 0; i <= n_hands; i++) count[i] = 0;
  int num_trials = 10000;
  if (argc == 3) num_trials = atoi(argv[2]);
  for (int i = 0; i < num_trials; i++) {
    shuffle(remains);
    future_cards_from_deck(remains, fc);
    size_t best = 0;
    int is_tie = 0;
    for (size_t j = 1; j < n_hands; j++) {
      int cmp = compare_hands(hands[j], hands[best]);
      if (cmp > 0) {
	best = j;
	is_tie = 0;
      } else if (cmp == 0) {
	is_tie = 1;
      }
    }
    if (is_tie == 1) count[n_hands]++;
    else count[best]++;
  }

  for (size_t i = 0; i < n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, count[i], num_trials, (float) 100 * count[i] / num_trials);
  }
  printf("And there were %u ties\n", count[n_hands]);

  free_hands(hands, n_hands);
  free_deck(remains);
  free_future_cards(fc);
  
  if (fclose(f) != 0) {
    fprintf(stderr, "Can not close file '%s'\n", argv[1]);
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
