public class PayFee {
    public static void main(String[] args) {

        double balance = IO.readDouble();

        if(15000 <= balance) {
            double newBalance = (balance - 15000);
            IO.outputDoubleAnswer((newBalance*.04)+350);

            //15,000 and above

        } else if(10000 <= balance) {
            double newBalance = (balance - 10000);
            IO.outputDoubleAnswer((newBalance*.03)+200);

            //10,000 through 14,999

        } else if(5000 <= balance) {
            if((balance*.02)<120){
                IO.outputDoubleAnswer(120);
            } else {
                IO.outputDoubleAnswer(balance*.02);
            }

            //5,000 through 9,999

        } else if(500 <= balance) {

            if((balance*.01)<20) {
                IO.outputDoubleAnswer(20);
            } else {
                IO.outputDoubleAnswer(balance*.01);
            }

            //500 through 4,999

        } else if(0 < balance) {
            IO.outputDoubleAnswer(10);

            //0 through 499

        } else if(0 >= balance){
            IO.outputDoubleAnswer(0);

            //0

        }
    }
}
