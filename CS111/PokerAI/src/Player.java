public class Player {
        private double balance;
        private Hand hand = new Hand();

        public Player(double balance){
            this.balance = balance;
        }

        public void deal(Card c){ hand.addCard(c); }

        public Card[] discard(){
            hand.printHand();
            Card[] cards = new Card[0];
            return cards;
        }

        public double wager(double min){
            if(min > balance){ return -1; }

            if(min == 0){
                min = balance/2;
            }

            int a = 0;
            if(hand.numPairs() == 1)a = 1;
            if(hand.numPairs() == 2)a = 2;
            if(hand.hasTriplet())a = 3;
            if(hand.hasStraight())a = 4;
            if(hand.hasFlush())a = 5;
            if(hand.hasFullHouse())a = 6;
            if(hand.hasFourOfAKind())a = 7;
            if(hand.hasStraight() && hand.hasFlush())a = 8;

            if(a >= 4){
                double x = balance;
                balance -= x;
                return x;
            } else if(a >= 2){
                if(min == balance){ return -1; }
                else {
                    balance -= min;
                    return min;
                }
            } else {
                return -1;
            }
        }

        public Hand showHand(){ return hand; }

        public double getBalance(){
            return balance;
        }

        public void winnings(double amount){
            balance += amount;
            hand.clear();
        }
}