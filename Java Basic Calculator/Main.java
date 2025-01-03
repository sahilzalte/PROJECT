import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        float Number_1, Number_2;

        System.out.println();
        System.out.println("===== Basic Functionality Calculator =====");
        System.out.print("Enter First Number:");
        Scanner scan1 = new Scanner(System.in);
        Number_1 = scan1.nextFloat();

        System.out.print("Enter Secound Number:");
        Number_2 = scan1.nextFloat();
        System.out.println();

        System.out.print("You Have Enter : ");
        System.out.print(Number_1 + " And ");
        System.out.println(Number_2);
        System.out.println();

        System.out.println("******Menu******");
        String prompt = "Enter 1 For Addition:\n" +
                "Enter 2 For Subtraction:\n" +
                "Enter 3 For Multiplication:\n" +
                "Enter 4 For Division:\n";

        System.out.print(prompt);
        System.out.println();
        System.out.print("Enter Option :");
        int input = scan1.nextInt();

        switch (input) {
            case 1:
                System.out.println("The Addition is :" + (Number_1 + Number_2));
                break;

            case 2:
                System.out.println("The Subtractin is :" + (Number_1 - Number_2));

                break;

            case 3:
                System.out.println("The Multiplication is :" + (Number_1 * Number_2));

                break;

            case 4:
                if (Number_2 != 0) {
                    System.out.println("The Division result is: " + (Number_1 / Number_2));
                } else {
                    System.out.println("Error: Division by zero is not allowed.");
                }
                break;

            default:
                System.out.println("Plealse Enter Valid Option");
                break;

        }
        scan1.close();
    }

}
