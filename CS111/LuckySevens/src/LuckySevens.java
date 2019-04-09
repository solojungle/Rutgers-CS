public class LuckySevens {
    public static void main(String[] args){

        int low = IO.readInt();
        int high = IO.readInt();
        int count = 0;
        String temp;

        // Checks for a high floor
        if(low > high){
            return;
        }

        // Checks for sevens in string
        for(; low<=high;low++) {
            temp = String.valueOf(low);
            for (int i = 0; i < temp.length(); i++) {
                if (temp.charAt(i) == '7')
                    count++;
            }
        }
        IO.outputIntAnswer(count);
    }
}
