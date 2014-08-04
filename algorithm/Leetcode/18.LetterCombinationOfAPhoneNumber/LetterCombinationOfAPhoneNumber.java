// Given a digit string, return all possible letter combinations that the number
// could represent.

// Input:  Digit string "23"
// Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

// Note: Although the above answer is in lexicographical order, your answer
// could be in any order you want.

import java.util.*;


public class LetterCombinationOfAPhoneNumber {

    public ArrayList<String> letterCombinations(String digits) {

        ArrayList<String> result = new ArrayList<String>();
        if (digits == null || digits.isEmpty()) {
            result.add("");
            return result;
        }

        int total = 1;          // total size of result
        int n = digits.length();
        // sizes of the combination of the chars preceding char index i
        int[] sizes = new int[n];
        for (int i = 0; i < n; ++i) {
            String val = getValue(digits.charAt(i));
            sizes[i] = total;
            total *= val.length();
        }
        for (int i = 0; i < total; ++i) {
            char[] temp = new char[n];
            for (int j = 0; j < n; ++j) {
                String val = getValue(digits.charAt(j));
                temp[j] = val.charAt((i / sizes[j]) % val.length());
            }
            result.add(new String(temp));
        }
        return result;
    }

    private String getValue(char c) {
        String[] numToLetter =
            {"","","abc","def","ghi","jkl","mno","qprs","tuv","wxyz"};
        return numToLetter[c-'0'];
    }


    public static void main(String[] args) {
        LetterCombinationOfAPhoneNumber lc = new LetterCombinationOfAPhoneNumber();
        System.out.println(lc.letterCombinations("235"));
    }
}
