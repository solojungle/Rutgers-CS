public class Party {
    public static void main(String[] args) {

        int numPerson = IO.readInt();
        int numSlicesPerson = IO.readInt();
        int numCansPerson = IO.readInt();
        double costPie = IO.readDouble();
        int numPizzaInPie = IO.readInt();
        double costCase = IO.readDouble();
        int numCansInCase = IO.readInt();

        int slicesPerPerson = numPerson * numSlicesPerson;
        int cansPerPerson = numPerson * numCansPerson;
        int numOfPiesNeeded = (slicesPerPerson/numPizzaInPie) + ((slicesPerPerson%numPizzaInPie==0)?0:1);
        int numOfCasesNeeded = (cansPerPerson/numCansInCase) + ((cansPerPerson%numCansInCase==0)?0:1);
        double costOfPies = numOfPiesNeeded*costPie;
        double costOfCans = numOfCasesNeeded*costCase;
        double total = costOfCans + costOfPies;
        IO.outputDoubleAnswer(total);
    }
}