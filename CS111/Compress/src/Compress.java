public class Compress {
    public static String compress (String original){
        int letterCount = 1;
        String compressed = "";
        for(int i = 0;i < original.length();i++){
            if((i+1 < original.length())){
                if(original.charAt(i) != original.charAt(i+1)){
                    if(letterCount<2) compressed += original.charAt(i);
                    else{ compressed += String.valueOf(letterCount)+original.charAt(i);}
                    letterCount = 1;
                } else{
                    letterCount++;
                }
            } else {
                if(original.charAt(i)==original.charAt(i-1)){
                    compressed += String.valueOf(letterCount)+original.charAt(i);
                } else {
                    compressed += original.charAt(i);
                }
            }
        }
        return compressed;
    }
}


/*
for loop
    checks for i+1 null error
        does i to i+1
            not first
                if <2   || adds single char
                else    || adds char + number
            true next
    does last number comparison
        if last equals i-1 || char + number
        else just char, adding last char was done in previous loop so no need to be redundant




*/