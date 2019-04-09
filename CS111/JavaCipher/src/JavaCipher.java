public class JavaCipher {

    public static void main(String[] args) {
        System.out.println(javaCipher("NFFU NF BU 23 JO UIF CFMM UPXFS"));
    }
    public static String javaCipher(String encoded){
    char letter = encoded.charAt(0);
    int characterValue = letter;
    String before = String.valueOf((char)(characterValue - 1));
    if(encoded.length() == 1) return before;
    if(letter != ' '){
        if(letter == 'a' || letter == 'A'){return "Z" + javaCipher(encoded.substring(1));}
        return before + javaCipher(encoded.substring(1));
    }
    else {return letter + javaCipher(encoded.substring(1));}
    }
}
