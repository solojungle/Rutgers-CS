public class LongestRepeatingSubstring {
    public static void main(String[] args) {
        System.out.println(LongestRepeatingSubstring("absdgytgunasdadddddd"));
    }

    public static String LongestRepeatingSubstring(String original){
        int letterCount=1;
        int index = 0;
        int largest = 0;

        for(int i=0;i < original.length();i++){
            if(i+1 < original.length()){
                if(original.charAt(i)!=original.charAt(i+1)){
                    if(letterCount > largest){
                        largest = letterCount;
                        index = i;
                    }
                    letterCount = 1;
                }else letterCount++;
            }else{
                if(original.charAt(i)==original.charAt(i-1)){
                    if(letterCount > largest){
                        largest = letterCount;
                        index = i;
                    }
                }
            }
        }
        return String.valueOf(largest)+original.charAt(index);
    }


}
