public class TwoLargest {
    public static void main(String[] args) {

        double terminator = IO.readDouble();
        double userInput = IO.readDouble();
        double largestNumber = userInput;
        double secondLargestNumber = Double.NEGATIVE_INFINITY;
        int count = 0;

        while (terminator == userInput) {
            IO.reportBadInput();
            terminator = IO.readDouble();
            userInput = IO.readDouble();
        }

        while(userInput != terminator){
            userInput = IO.readDouble();

            if(userInput != terminator){
                count++;
            }

            if(terminator == userInput && count < 1){
                count=0;
                while(terminator == userInput){
                    IO.reportBadInput();
                    terminator = IO.readDouble();
                    userInput = IO.readDouble();
                }
            }

            if(userInput >= largestNumber && userInput != terminator){
                secondLargestNumber = largestNumber;
                largestNumber = userInput;
            }

            else if(userInput < largestNumber && userInput > secondLargestNumber && userInput != terminator){
                secondLargestNumber = userInput;
            }

        }

        IO.outputDoubleAnswer(largestNumber);
        IO.outputDoubleAnswer(secondLargestNumber);

    }
}






