public class LuckyNines {

    public static void main(String[] args){
        int lowerEnd = IO.readInt();
        int upperEnd = IO.readInt();
        IO.outputIntAnswer(countLuckyNines(lowerEnd,upperEnd));
    }

    public static int countLuckyNines(int lowerEnd, int upperEnd){
        int count = 0;
        String temp;

        if(lowerEnd > upperEnd){
            return -1;
        }

        for(; lowerEnd<=upperEnd;lowerEnd++) {
            temp = String.valueOf(lowerEnd);
            for (int i = 0; i < temp.length(); i++) {
                if (temp.charAt(i) == '9')
                    count++;
            }
        }
        return count;
    }

}
