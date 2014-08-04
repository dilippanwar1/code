package question9;

import CtCILibrary.TreeNode;


/**
 * Given an integer N, find next large value in a binary search tree.
 */
public class Question {

	public static int find(TreeNode root, int N) {
		if (root == null) return Integer.MIN_VALUE;

		if (N >= root.data && root.right == null)
			return Integer.MIN_VALUE;
		else if (N >= root.data)
			return find(root.right, N);
		else if (N < root.data && root.left == null)
			return root.data;
		else if (N < root.data && root.left.data < N)
			return root.data;
		else
			return find(root.left, N);
	}

	public static void main(String[] args) {

		int[] array = {3, 5, 6, 10, 13, 15};
		TreeNode node = TreeNode.createMinimalBST(array);
		node.print();

		System.out.println(find(node, 1));
	}
}
