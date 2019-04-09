public class Poker {
    public static void main(String[] args) {
        Hand c = new Hand();
        c.addCard(new Card(1,1));
        c.addCard(new Card(1,2));
        c.addCard(new Card(1,2));
        c.addCard(new Card(1,1));
        c.addCard(new Card(5,1));

        Hand d = new Hand();
        d.addCard(new Card(2,1));
        d.addCard(new Card(2,2));
        d.addCard(new Card(2,2));
        d.addCard(new Card(5,1));
        d.addCard(new Card(5,1));

        System.out.println("1 " +c.numPairs());
        System.out.println("2 " +c.hasTriplet());
        System.out.println("3 " +c.hasFlush());
        System.out.println("4 " +c.hasStraight());
        System.out.println("5 " +c.hasFullHouse());
        System.out.println("6 " +c.hasFourOfAKind());
        System.out.println("7 " +c.highestValue());
        System.out.println("8 " +c.highestDuplicate());
        System.out.println("9 " +c.compareTo(d));
    }
}
