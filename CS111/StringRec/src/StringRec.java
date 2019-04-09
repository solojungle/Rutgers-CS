public class StringRec {
    public static String decompress(String compressedText){
        String newCompressedString = "";
        if(compressedText.length() == 1){return compressedText.charAt(0) + "";}
        if(Character.isDigit(compressedText.charAt(0))){
            if(compressedText.charAt(0) != '1'){
                int number = (compressedText.charAt(0) - '0') - 1;
                newCompressedString = "" + number + compressedText.charAt(1) + compressedText.substring(2);
                return compressedText.charAt(1) + decompress(newCompressedString);
            }
            else {
                if(compressedText.length() == 2){return compressedText.charAt(1) + "";}
                return compressedText.charAt(1) + decompress(compressedText.substring(2));
            }
        }
        else {return compressedText.charAt(0) + decompress(compressedText.substring(1));}
    }
}