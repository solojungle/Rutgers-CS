public class Cashier {
    public static void main(String[] args) {

        System.out.println("Enter the Price of the item:");
        double cost = IO.readDouble()*100;

        System.out.println("Enter the Amount Given:");
        double cash = IO.readDouble()*100;


            double change = (cash - cost);

                double twenties = change / 2000;
                if (twenties >= 1) {
                    change %= 2000;
                    System.out.println((int) twenties + " twenties");
                }

                double tens = change / 1000;
                if (tens >= 1) {
                    change %= 1000;
                    System.out.println((int)tens + " tens");
                }

                double fives = change / 500;
                if (fives >= 1) {
                    change %= 500;
                    System.out.println((int)fives + " fives");
                }

                double singles = change / 100;
                if (singles >= 1) {
                    change %= 100;
                    System.out.println((int)singles + " singles");
                }

    }
}