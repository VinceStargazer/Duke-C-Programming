#include "cards.h"
#include "cards.c"

int main(void) {
  card_t c = card_from_letters('J', 'h');
  print_card(c);
  print_card(card_from_letters('0', 'd'));
  printf("\n");
  for (int i = 0; i < 52; i++) {
    print_card(card_from_num(i));
    printf(" ");
  }
}
