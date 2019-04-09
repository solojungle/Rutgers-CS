public class SmallestLargest {
    public static void main(String[] args) {

        double largestNumber, smallestNumber;
        double terminator = IO.readDouble();
        double userInput = IO.readDouble();
        largestNumber = smallestNumber = userInput;

        if(userInput == terminator){
            IO.reportBadInput();
            return;
        }

        do{
            userInput = IO.readDouble();

            if(userInput!=terminator && userInput < smallestNumber){
                smallestNumber = userInput;
            } else if(userInput!=terminator && userInput > largestNumber){
                largestNumber = userInput;
            }

        }while(userInput != terminator);

        IO.outputDoubleAnswer(smallestNumber);
        IO.outputDoubleAnswer(largestNumber);

    }
}