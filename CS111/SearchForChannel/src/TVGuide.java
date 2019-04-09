public class TVGuide {


    public static String findNetwork(int input, int[] channels, String[] networks) {
        for (int i = 0; i < channels.length; i++) {
            if (input == channels[i]) {
                return networks[i];
            }
        }
        return "Not here";
    }

    public static void main(String[] args) {
        int[] channels = {2, 4, 5, 7, 9, 11, 13};
        String[] networks = {"CBS", "NBC", "FOX", "ABC", "My9", "CW", "PBS"};
        System.out.println(findNetwork(IO.readInt(), channels, networks));

    }
}