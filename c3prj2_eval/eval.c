#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;
  const card_t * c1 = *cp1, * c2 = *cp2;
  if (c1 -> value == c2 -> value) return c2 -> suit - c1 -> suit;
  return c2 -> value - c1 -> value;
}

suit_t flush_suit(deck_t * hand) {
  int count[4] = {0};
  card_t ** cards = hand -> cards;
  size_t size = hand -> n_cards;
  for (size_t i = 0; i < size; i++) {
    card_t c = *cards[i];
    count[c.suit]++;
    if (count[c.suit] == 5)
      return c.suit;
  }
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned max = 0;
  for (size_t i = 0; i < n; i++)
    if (arr[i] > max) max = arr[i];
  return max;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for (size_t i = 0; i < n; i++)
    if (match_counts[i] == n_of_akind)
      return i;
  return EXIT_FAILURE;
}

size_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  card_t ** cards = hand -> cards;
  size_t size = hand -> n_cards;
  unsigned val = cards[match_idx] -> value;
  for (size_t i = 0; i < size; i++) {
    card_t c = *cards[i];
    if (c.value != val && match_counts[i] > 1)
      return i;
  }
  return -1;
}

int is_n_length_at(deck_t * hand, size_t index, suit_t fs, int n) {
  card_t ** cards = hand -> cards;
  size_t size = hand -> n_cards;
  int count = 0;
  unsigned prev = 0;
  if (fs != NUM_SUITS && cards[index] -> suit != fs)
    return 0;
  for (size_t i = index; i < size; i++) {
    card_t c = *cards[i];
    if (c.value == prev) continue;
    if (prev == 0 || c.value == prev - 1) {
      if (fs == NUM_SUITS || c.suit == fs) {
	count++;
	if (count == n) return 1;
	prev = c.value;
      }
    } else {
      break;
    }
  }
  return 0;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  card_t ** cards = hand -> cards;
  size_t size = hand -> n_cards;
  if (fs != NUM_SUITS && cards[index] -> suit != fs)
    return 0;
  if (is_n_length_at(hand, index, fs, 5) == 1) return 1;
  if (cards[index] -> value == VALUE_ACE)
    for (size_t i = index + 1; i < size; i++)
      if (cards[i] -> value == 5 && is_n_length_at(hand, i, fs, 4) == 1)
	  return -1;

  return 0;
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  assert(n < 5);
  hand_eval_t ans;
  ans.ranking = what;
  card_t ** cards = hand -> cards;
  for (size_t i = 0; i < n; i++)
    ans.cards[i] = cards[idx + i];
  size_t j = 0, k = n;
  if (k == 0) {
    ans.cards[k] = cards[k];
    k++;
  }
  for (size_t i = k; i < 5; i++) {
    while (cards[j] -> value == cards[idx] -> value) {
      assert(j < hand -> n_cards);
      j++;
    }
    ans.cards[i] = cards[j++];
  }  
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  card_t ** cards1 = hand1 -> cards, ** cards2 = hand2 -> cards;
  size_t size1 = hand1 -> n_cards, size2 = hand2 -> n_cards;
  qsort(cards1, size1, sizeof(const void *), card_ptr_comp);
  qsort(cards2, size2, sizeof(const void *), card_ptr_comp);
  hand_eval_t eval1 = evaluate_hand(hand1), eval2 = evaluate_hand(hand2);
  if (eval1.ranking != eval2.ranking) return eval2.ranking - eval1.ranking;
  for (size_t i = 0; i < 5; i++) {
    card_t c1 = *eval1.cards[i], c2 = *eval2.cards[i];
    if (c1.value != c2.value) return c1.value - c2.value;
  }
  return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) {
  card_t ** cards = hand -> cards;
  unsigned * res = malloc(hand -> n_cards * sizeof(*res));
  int count[15] = {0};
  for (size_t i = 0; i < hand -> n_cards; i++)
    count[cards[i] -> value]++;
  for (size_t i = 0; i < hand -> n_cards; i++)
    res[i] = count[cards[i] -> value];
  return res;
}

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
