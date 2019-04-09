public class TwoLarge {
    public static void main(String[] args){

        System.out.println("Terminator");
        double terminator = IO.readDouble();
        double userInput;
        double large, secLarge;
        large = secLarge = terminator;

        while(true){
            System.out.println("Enter Input");
            userInput = IO.readDouble();
            while (terminator==userInput){
                if(large == terminator || secLarge == terminator){
                IO.reportBadInput();
                break;
                } else {
                    System.out.println("The largest value is " + large);
                    System.out.println("The second largest is " + secLarge);
                    break;
                }
            }
            if (userInput > large) {
                secLarge = large;
                large = userInput;
            }
            else if (userInput > secLarge) {
                secLarge = userInput;
            }
        }
    }
}
