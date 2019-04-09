public class ReverseRecursion {
    public static void main(String[] args) {
        System.out.println(reverse("first second third fourth."));
    }
    public static String reverse(String str){
        if(str.indexOf(' ') == -1) {return (str.substring(0, 1)).toUpperCase() + str.substring(1, str.indexOf('.'));}
        else {
            return reverse(str.substring(str.indexOf(' ') + 1))+" "+ str.substring(0, str.indexOf(' '));
        }
    }
}