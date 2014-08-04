// Given an integer, convert it to a roman numeral.

// Input is guaranteed to be within the range from 1 to 3999.


public class IntegerToRoman {

    public String intToRoman(int num) {

        int i = 0;
        int[] nums = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        String[] symbols = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X",
                            "IX", "V", "IV", "I"};
        StringBuilder result = new StringBuilder();

        while (num > 0 && i < nums.length) {
            int times = num / nums[i];
            for (int k = 0; k < times; k++) {
                result.append(symbols[i]);
                num -= nums[i];
            }
            i++;
        }

        return result.toString();
    }

    public static void main(String[] args) {
        IntegerToRoman itr = new IntegerToRoman();
        System.out.println(itr.intToRoman(223));
    }
}
