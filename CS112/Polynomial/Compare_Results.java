import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

public class Compare_Results {
	public static void main(String [] args) {
		try {
			String file1, file2;
			Scanner input = new Scanner(System.in);
			System.out.println("Enter your file name: ");
			file1 = input.nextLine();
			System.out.println("Enter the other file name: ");
			file2 = input.nextLine();
			Scanner input2 = new Scanner(new FileReader(new File(file1)));
			Scanner input3 = new Scanner(new FileReader(new File(file2)));
			int lineNum = 1;
			while(input2.hasNext()) {
				if(!input2.nextLine().equals(input3.nextLine())) {
					System.out.println("Mismatch at line number: " + lineNum);
				}
				lineNum++;
			}
			System.out.println("Finished Comparing.");
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
