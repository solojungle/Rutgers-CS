
/**
 * An object of type Hand represents a hand of cards.  The
 * cards belong to the class Card.  A hand is empty when it
 * is created, and any number of cards can be added to it.
 */

import java.util.ArrayList;

public class Hand {

    private Card[] hand;   // The cards in the hand.
    private int count;

    /**
     * Create a hand that is initially empty.
     */
    public Hand() {
        hand = new Card[5];
        count = 0;
    }

    /**
     * Remove all cards from the hand, leaving it empty.
     */
    public void clear() {
        for(int i=0 ; i<hand.length; i++){ hand[i] = null; }
        count = 0;
    }

    /**
     * Add a card to the hand.  It is added at the end of the current hand.
     * @param c the non-null card to be added.
     * @throws NullPointerException if the parameter c is null.
     */
    public void addCard(Card c) {

        for(int i=0 ; i<hand.length; i++){
            if (hand[i] == null){
                hand[i] = c;
                count = count + 1;
                break;
            }
        }


    }

    /**
     * Remove a card from the hand, if present.
     * @param c the card to be removed.  If c is null or if the card is not in
     * the hand, then nothing is done.
     */
    public void removeCard(Card c) {

        for(int i=0 ; i<hand.length; i++){
            if (hand[i].equals(c)){
                hand[i] = null;
                count = count-1;
            }
        }

    }

    /**
     * Remove the card in a specified position from the hand.
     * @param position the position of the card that is to be removed, where
     * positions are starting from zero.
     * @throws IllegalArgumentException if the position does not exist in
     * the hand, that is if the position is less than 0 or greater than
     * or equal to the number of cards in the hand.
     */
    public void removeCard(int position) {
        if (position < 0 || position >= hand.length)
            throw new IllegalArgumentException("Position does not exist in hand: " + position);
        hand[position] = null;
    }

    /**
     * Returns the number of cards in the hand.
     */
    public int getCardCount() {
        return count;
    }

    /**
     * Gets the card in a specified position in the hand.  (Note that this card
     * is not removed from the hand!)
     * @param position the position of the card that is to be returned
     * @throws IllegalArgumentException if position does not exist in the hand
     */
    public Card getCard(int position) {
        if (position < 0 || position >= hand.length)
            throw new IllegalArgumentException("Position does not exist in hand: "
                    + position);
        return hand[position];
    }

    /**
     * Sorts the cards in the hand so that cards of the same suit are
     * grouped together, and within a suit the cards are sorted by value.
     * Note that aces are considered to have the lowest value, 1.
     */
    public void sortBySuit() {
        int size = count;
        int nonnull = 0;
        int index = 0;

        Card[] newHand = new Card[5];
        while (size > 0) {
            if (hand[nonnull] == null) { nonnull = nonnull+1; continue;}
            int pos = nonnull;  // Position of minimal card.
            Card c = hand[nonnull];  // Minimal card.

            for (int i = nonnull+1; i < hand.length; i++) {
                Card c1 = hand[i];
                if (c1 != null){
                    if ( c1.getSuit() < c.getSuit() ||
                            (c1.getSuit() == c.getSuit() && c1.getValue() < c.getValue()) ) {
                        pos = i;
                        c = c1;
                    }
                }
            }
            hand[pos] = null;
            size = size - 1;
            newHand[index++] = c;
            nonnull = 0;
        }
        hand = newHand;
    }

    /**
     * Sorts the cards in the hand so that cards of the same value are
     * grouped together.  Cards with the same value are sorted by suit.
     * Note that aces are considered to have the lowest value, 1.
     */
    public void sortByValue() {
        int size = count;
        int nonnull = 0;
        int index = 0;

        Card[] newHand = new Card[5];
        while (size > 0) {
            if (hand[nonnull] == null) { nonnull = nonnull+1; continue;}
            int pos = nonnull;  // Position of minimal card.
            Card c = hand[nonnull];  // Minimal card.

            for (int i = nonnull+1; i < hand.length; i++) {

                Card c1 = hand[i];
                if (c1 != null){
                    if ( c1.getValue() < c.getValue() ||
                            (c1.getValue() == c.getValue() && c1.getSuit() < c.getSuit()) ) {
                        pos = i;
                        c = c1;
                    }
                }
            }
            hand[pos] = null;
            size = size - 1;
            newHand[index++] = c;
            nonnull = 0;
        }
        hand = newHand;
    }

    public void printHand(){

        for(int i=0; i<hand.length; i++){
            if (hand[i] != null){
                System.out.println(hand[i]);
            }
        }
        System.out.println();
    }


    /******************************** Implement your methods here ****************************************/
    public int numPairs(){
        sortByValue();
        int pairCount=0;
        int lastPair=0;
        for(int i = 0;i < hand.length - 1;i++){
            if(hand[i].getValue() == hand[i+1].getValue()){
                i++;
                pairCount++;
            }
        }
        return pairCount;
    }

    public boolean hasTriplet(){
        sortByValue();
        for(int i = 0;i < hand.length - 2;i++){
            if(hand[i].getValue() == hand[i+1].getValue() && hand[i].getValue() == hand[i+2].getValue()){
                return true;
            }
        }
        return false;
    }

    public boolean hasFlush(){
        for(int i = 0;i < hand.length - 1;i++){
            if(hand[i].getSuit() != hand[i+1].getSuit()){
                return false;
            }
        }
        return true;
    }

    public boolean hasStraight(){
        sortByValue();
        if(hand[0].getValue() == 1 && hand[1].getValue() == 10 && hand[2].getValue() == 11 && hand[3].getValue() == 12 && hand[4].getValue() == 13){
            return true;
        }
        for(int i=0; i < hand.length - 1; i++){
            if(hand[i].getValue() + 1 != hand[i + 1].getValue()){
                return false;
            }
        }
        return true;
    }

    public boolean hasFullHouse(){
        if(hasTriplet() && numPairs() == 2 && !hasFourOfAKind()){return true;}
        return false;
    }

    public boolean hasFourOfAKind(){
        sortByValue();
        for (int i = 0; i < hand.length - 3; i++) {
            if(hand[i].getValue() == hand[i + 3].getValue()) {
                return true;
            }
        }
        return false;
    }

    public Card highestValue(){
        sortByValue();
        if(hand[0].getValue() == 1){return hand[0];}
        return hand[hand.length - 1];
    }

    public Card highestDuplicate(){
        sortByValue();
        if(hand[0].getValue() == hand[1].getValue() && hand[0].getValue() == 1){
            return hand[0];
        }
        for(int i = hand.length - 1; i > 0; i--){
            if(hand[i].getValue() == hand[i - 1].getValue()){
                return hand[i];
            }
        }
        return null;
    }
    public int compareTo(Hand h){
        sortByValue();
        h.sortByValue();
        int a = 0; //instance hand
        int b = 0; //argument hand

        // Find rank
        if(numPairs() == 1)a = 1;
        if(numPairs() == 2)a = 2;
        if(hasTriplet())a = 3;
        if(hasStraight())a = 4;
        if(hasFlush())a = 5;
        if(hasFullHouse())a = 6;
        if(hasFourOfAKind())a = 7;
        if(hasStraight() && hasFlush())a = 8;

        if(h.numPairs() == 1)b = 1;
        if(h.numPairs() == 2)b = 2;
        if(h.hasTriplet())b = 3;
        if(h.hasStraight())b = 4;
        if(h.hasFlush())b = 5;
        if(h.hasFullHouse())b = 6;
        if(h.hasFourOfAKind())b = 7;
        if(h.hasStraight() && h.hasFlush())b = 8;

        // Catch-all
        if(a > b) return 1;
        if(a < b) return -1;

        // High-Card
        if(a == 0 && b == 0){
            // Ace Exception
            int iHighest = highestValue().getValue();
            int hHighest = h.highestValue().getValue();
            if(iHighest == 1) iHighest = 14;
            if(hHighest == 1) hHighest = 14;

            if(iHighest > hHighest)return 1;
            else if(iHighest < hHighest)return -1;
            for(int i = hand.length - 1;i >= 0;i--){
                if(hand[i].getValue() > h.hand[i].getValue())return 1;
                else if(hand[i].getValue() < h.hand[i].getValue())return -1;
            }
            return 0;
        }
        // Pair
        if(a == 1 && b == 1){
            // Ace Exception
            int iHighPair = highestDuplicate().getValue();
            int hHighPair = h.highestDuplicate().getValue();
            if(iHighPair == 1) iHighPair = 14;
            if(hHighPair == 1) hHighPair = 14;

            if(iHighPair > hHighPair)return 1;
            else if(iHighPair < hHighPair)return -1;

            //Ace Exception
            int iKick = 0;
            int hKick = 0;
            if(hand[0].getValue() == 1){iKick = 14;}
            if(h.hand[0].getValue() == 1){hKick = 14;}

            if(iKick > hKick)return 1;
            else if(iKick < hKick)return -1;
            int i = hand.length - 1;
            boolean c = hand[i].getValue() != highestDuplicate().getValue();
            boolean d = h.hand[i].getValue() != h.highestDuplicate().getValue();
            for(;i >= 0;i--) {
                if(hand[i].getValue() > h.hand[i].getValue() && c && d)return 1;
                else if(hand[i].getValue() < h.hand[i].getValue() && c && d)return -1;
            }
            return 0;
        }

        // Two Pair
        if(a == 2 && b == 2){
            // Ace Exception
            int iHighPair = highestDuplicate().getValue();
            int hHighPair = h.highestDuplicate().getValue();
            if(iHighPair == 1) iHighPair = 14;
            if(hHighPair == 1) hHighPair = 14;

            if(iHighPair > hHighPair)return 1;
            else if(iHighPair < hHighPair)return -1;
            int i = hand.length - 1;
            boolean c = hand[i].getValue() != highestDuplicate().getValue();
            boolean d = h.hand[i].getValue() != h.highestDuplicate().getValue();
            for(;i > 0;i--) {
                if(hand[i].getValue() == hand[i - 1].getValue() && c) iHighPair = hand[i].getValue();
                if(h.hand[i].getValue() == h.hand[i - 1].getValue() && d) hHighPair = hand[i].getValue();
            }
            if(iHighPair > hHighPair)return 1;
            else if(iHighPair < hHighPair)return -1;
            int iKicker = 0;
            int hKicker = 0;
            for(i = hand.length - 1;i >= 0;i--) {
                if(hand[i].getValue() != iHighPair && hand[i].getValue() != highestDuplicate().getValue()) iKicker = hand[i].getValue();
                if(h.hand[i].getValue() != hHighPair && h.hand[i].getValue() != h.highestDuplicate().getValue()) hKicker = h.hand[i].getValue();
            }
            // Ace Exception
            if(iKicker == 1) iKicker = 14;
            if(hKicker == 1) hKicker = 14;
            if(iKicker > hKicker)return 1;
            else if(iKicker < hKicker)return -1;

            return 0;
        }

        // Three of a kind
        if(a == 3 && b == 3){
            // Ace Exception
            int iHighPair = highestDuplicate().getValue();
            int hHighPair = h.highestDuplicate().getValue();
            if(iHighPair == 1) iHighPair = 14;
            if(hHighPair == 1) hHighPair = 14;
            if(iHighPair > hHighPair)return 1;
            else if(iHighPair < hHighPair)return -1;

            int iKicker = 0;
            int hKicker = 0;
            for(int i = 0;i < hand.length;i++) {
                if(hand[i].getValue() != highestDuplicate().getValue()) iKicker = hand[i].getValue();
                if(h.hand[i].getValue() != h.highestDuplicate().getValue()) hKicker = h.hand[i].getValue();
            }

            // Ace Exception
            if(highestValue().getValue() == 1 && highestDuplicate().getValue() != 1) iKicker = 14;
            if(h.highestValue().getValue() == 1 && h.highestDuplicate().getValue() != 1) hKicker = 14;
            if(iKicker > hKicker)return 1;
            else if(iKicker < hKicker)return -1;
            if(iKicker == 14) iKicker = 1;
            if(hKicker == 14) hKicker = 1;

            int iKicker2 = 0;
            int hKicker2 = 0;
            for(int i = 0;i < hand.length;i++) {
                if(hand[i].getValue() != highestDuplicate().getValue() && hand[i].getValue() != iKicker) iKicker2 = hand[i].getValue();
                if(h.hand[i].getValue() != h.highestDuplicate().getValue() && h.hand[i].getValue() != hKicker) hKicker2 = h.hand[i].getValue();
            }
            if(iKicker2 > hKicker2)return 1;
            else if(iKicker2 < hKicker2)return -1;
            return 0;
        }

        // Straight
        if(a == 4 && b == 4){
            int iHighest = highestValue().getValue();
            int hHighest = h.highestValue().getValue();
            if(highestValue().getValue() == 1 && hand[4].getValue() == 13){iHighest = 14;}
            if(h.highestValue().getValue() == 1 && h.hand[4].getValue() == 13){hHighest = 14;}

            if(iHighest > hHighest) return 1;
            else if(iHighest < hHighest) return -1;
            return 0;
        }

        // Flush
        if(a == 5 && b == 5){
            // Ace Exception
            int iHighest = highestValue().getValue();
            int hHighest = h.highestValue().getValue();
            if(iHighest == 1) iHighest = 14;
            if(hHighest == 1) hHighest = 14;

            if(iHighest > hHighest)return 1;
            else if(iHighest < hHighest)return -1;
            for(int i = hand.length - 1;i >= 0;i--){
                if(hand[i].getValue() > h.hand[i].getValue())return 1;
                else if(hand[i].getValue() < h.hand[i].getValue())return -1;
            }
            return 0;
        }

        // Full house
        if(a == 6 && b == 6){
            int iThreePair = 0;
            int hThreePair = 0;
            for(int i = 0;i < hand.length - 2;i++){
                if(hand[i].getValue() == hand[i+1].getValue() && hand[i].getValue() == hand[i+2].getValue()) iThreePair = hand[i].getValue();
                if(h.hand[i].getValue() == h.hand[i+1].getValue() && h.hand[i].getValue() == h.hand[i+2].getValue()) hThreePair = h.hand[i].getValue();
            }
            // Ace Exception
            if(iThreePair == 1) iThreePair = 14;
            if(hThreePair == 1) hThreePair = 14;
            if(iThreePair > hThreePair) return 1;
            else if(iThreePair < hThreePair) return -1;
            if(iThreePair == 14) iThreePair = 1;
            if(hThreePair == 14) hThreePair = 1;

            int iHighPair = 0;
            int hHighPair = 0;
            for(int i = 0;i < hand.length;i++){
                if(hand[i].getValue() != iThreePair) iHighPair = hand[i].getValue();
                if(h.hand[i].getValue() != hThreePair) hHighPair = h.hand[i].getValue();
            }

            // Ace Exception
            if(iHighPair == 1) iHighPair = 14;
            if(hHighPair == 1) hHighPair = 14;
            if(iHighPair > hHighPair) return 1;
            else if(iHighPair < hHighPair) return -1;

            return 0;
        }

        // Four of a kind
        if(a == 7 && b == 7){
            // Ace Exception
            int iHighPair = highestDuplicate().getValue();
            int hHighPair = h.highestDuplicate().getValue();
            if(iHighPair == 1) iHighPair = 14;
            if(hHighPair == 1) hHighPair = 14;
            if(iHighPair > hHighPair) return 1;
            else if(iHighPair < hHighPair) return -1;
            if(iHighPair == 14) iHighPair = 1;
            if(hHighPair == 14) hHighPair = 1;

            int iKicker = 0;
            int hKicker = 0;
            for(int i = 0;i < hand.length;i++){
                if(hand[i].getValue() != iHighPair) iKicker = hand[i].getValue();
                if(h.hand[i].getValue() != hHighPair) hKicker = h.hand[i].getValue();
            }

            // Ace Exception
            if(iKicker == 1) iKicker = 14;
            if(hKicker == 1) hKicker = 14;

            if(iKicker > hKicker) return 1;
            else if(iKicker < hKicker) return -1;
            return 0;
        }

        // Straight flush
        if(a == 8 && b == 8){
            // Ace Exception
            int iHighest = highestValue().getValue();
            int hHighest = h.highestValue().getValue();
            if(highestValue().getValue() == 1 && hand[4].getValue() == 13){iHighest = 14;}
            if(h.highestValue().getValue() == 1 && h.hand[4].getValue() == 13){hHighest = 14;}

            if(iHighest > hHighest) return 1;
            else if(iHighest < hHighest) return -1;
            return 0;
        }

        System.out.println("Reached End");
        return 0;
    }
}
