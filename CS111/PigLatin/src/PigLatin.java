public class PigLatin {
    public static String translate (String original){
        switch(original.charAt(0)) {
            case 'a':
            case 'A':
            case 'e':
            case 'E':
            case 'i':
            case 'I':
            case 'o':
            case 'O':
            case 'u':
            case 'U':
                return original+"vai";
            default:
                return original.substring(1)+original.toLowerCase().charAt(0)+"ai";
        }
    }
}