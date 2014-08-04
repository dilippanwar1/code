package question7;

import java.util.ArrayList;
import java.util.HashMap;

public class Question {

	private static int M;
	private static int N;

	private static boolean[][] visited;
	private static boolean[][] colored;
	private static ArrayList<Character> colors;
	private static HashMap<Character, Character> mapChar2Color;
	private static HashMap<Character, Character> mapColor2Char;


	public static void mapColor(char[][] array, int i, int j) {

		if (!validIndex(i, j)) return;

		System.out.println(i + " " + j);

		visited[i][j] = true;

		if (i-1 >= 0 && visited[i-1][j] == false)
			mapColor(array, i-1, j);
		if (j-1 >= 0 && visited[i][j-1] == false)
			mapColor(array, i, j-1);
		if (i+1 < M && visited[i+1][j] == false)
			mapColor(array, i+1, j);
		if (j+1 < N && visited[i][j+1] == false)
			mapColor(array, i, j+1);

		ArrayList<Character> list = new ArrayList<Character>();
		list.addAll(colors);

		colored[i][j] = true;
		if (mapChar2Color.containsKey(array[i][j])) return;

		if (validIndex(i-1, j) && colored[i-1][j]) {
			list.remove(mapChar2Color.get(array[i-1][j]));
		}
		if (validIndex(i, j-1) && colored[i][j-1]) {
			list.remove(mapChar2Color.get(array[i][j-1]));
		}
		if (validIndex(i+1, j) && colored[i+1][j]) {
			list.remove(mapChar2Color.get(array[i+1][j]));
		}
		if (validIndex(i, j+1) && colored[i][j+1]) {
			list.remove(mapChar2Color.get(array[i][j+1]));
		}

		char choose = list.get(0);
		for (char ch : list) {
			if (!mapColor2Char.containsKey(ch)) {
				choose = ch;
				break;
			}
		}
		mapChar2Color.put(array[i][j], choose);
		mapColor2Char.put(choose, array[i][j]);
	}

	private static boolean validIndex(int i, int j) {
		if (i < 0 || j < 0 || i >= M || j >= N) return false;
		return true;
	}


	public static void main(String[] args) {
		char[][] array = new char[][]
            {
                {'a', 'a', 'a', 'a', 'd'},
                {'b', 'a', 'b', 'c', 'd'},
                {'a', 'b', 'b', 'c', 'd'},
            };

		M = array.length;
		N = array[0].length;

		visited = new boolean[M][N];
		colored = new boolean[M][N];
		colors = new ArrayList<Character>();
		colors.add('G'); colors.add('R'); colors.add('Y'); colors.add('B');
		mapChar2Color = new HashMap<Character, Character>();
		mapColor2Char = new HashMap<Character, Character>();
		mapColor(array, M-1, N-1);

		char[][] out = new char[M][N];
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				out[i][j] = mapChar2Color.get(array[i][j]);

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				System.out.print(array[i][j] + " ");
			}
			System.out.println();
		}

		System.out.println();

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				System.out.print(out[i][j] + " ");
			}
			System.out.println();
		}
	}

}
