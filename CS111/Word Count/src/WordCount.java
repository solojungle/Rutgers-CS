public class WordCount {
    public static int countWords(String original, int maxLength){
        String[] temp = original.split(" ");
        int count = 0;
        for(int i = 0;i < temp.length;i++){
            if(temp[i].replaceAll("[^A-Za-z]+", "").length()<=maxLength){
                count++;
            }
        }
        return count;
    }
}
