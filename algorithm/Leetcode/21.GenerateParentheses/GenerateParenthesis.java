// Given n pairs of parentheses, write a function to generate all combinations
// of well-formed parentheses.

// For example, given n = 3, a solution set is:
//    "((()))", "(()())", "(())()", "()(())", "()()()"

import java.util.*;


public class GenerateParenthesis {

    public ArrayList<String> generateParenthesis(int n) {
        // Start typing your Java solution below
        // DO NOT write main() function
		ArrayList<String> list = new ArrayList<String>();
		char[] str = new char[n*2];

        generateParenthesisHelper(list, str, 0, n, n);

        return list;
    }

    private void generateParenthesisHelper(ArrayList<String> list, char[] str,
                                           int index, int left, int right) {
        // if both left parenthesis and right parenthesis are 0, we have
        // a valid parenthesis combination
        if (left == 0 && right == 0) {
            list.add(String.valueOf(str));
            return;
        } else if (left < 0 || right < 0 || left > right) {
            return;             // invalid case
        }

        str[index] = '(';
        generateParenthesisHelper(list, str, index+1, left-1, right);
        str[index] = ')';
        generateParenthesisHelper(list, str, index+1, left, right-1);
    }

    public static void main(String[] args) {

        GenerateParenthesis gen = new GenerateParenthesis();
        ArrayList<String> res = gen.generateParenthesis(4);
        System.out.println(res);
    }
}
