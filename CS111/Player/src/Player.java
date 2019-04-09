public class Player {
    private double balance;
    private Hand hand = new Hand();

    public Player(double balance){
        this.balance = balance;
    }

    public void deal(Card c){ hand.addCard(c); }

    public Card[] discard(){
        System.out.println("This is your hand:");
        hand.printHand();
        System.out.println("How many cards would you like to discard?");
        int x = IO.readInt();
        while(x < 0 || x > 5){
            System.out.println("Re-enter valid number");
            x = IO.readInt();
        }
        Card[] cards = new Card[x];
        System.out.println("Enter the indices of the cards you want to discard:");
        for(int i = 0;i < x;i++){
            int y = IO.readInt();
            while(hand.getCard(y) == null || y < 0 || y > 5){
                System.out.println("That index is null.");
                y = IO.readInt();
            }
            cards[i] = hand.getCard(y);

            // NOT REMOVING COUNT WTF.
            hand.removeCard(y);
        }
        return cards;
    }

    public double wager(double min){
        if(min > balance){return -1;}
        System.out.println("How much do you want to wager?");
        double x = IO.readDouble();
        while(x < -1 || balance - x < 0 || min > x){
            System.out.println("Invalid wager.");
            x = IO.readDouble();
        }
        if(x == -1){return -1;}
        System.out.println("This will result in this player's balance reduced by " + x);
        balance -= x;
        return x;
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