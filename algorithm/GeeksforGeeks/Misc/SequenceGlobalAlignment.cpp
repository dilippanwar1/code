// Dynamic programming for sequence alignment
// Coursera bioinformatics

#include <iostream>
#include <string>
using namespace std;

// A at index 0;
// C at index 1;
// G at index 2;
// T at index 3;
const int substitution[4][4] = {
  {2, -7, -5, -7}, {-7, 2, -7, -5},
  {-5, -7, 2, -7}, {-7, -5, -7, 2}
};
// Gap penalty (constant penalty, not linear).
const int penalty = -5;

int getIndex(char ch) {
  switch (ch) {
  case 'A':
    return 0;
  case 'C':
    return 1;
  case 'G':
    return 2;
  case 'T':
    return 3;
  }
  return 0;
}

int scoreFunc(string seq1, string seq2) {
  // Suppose length equal
  int len = seq1.length();
  int score[len+1][len+1];

  for (int i = 0; i <= len; i++) {
    score[i][0] = i * penalty;
  }
  for (int i = 0; i <= len; i++) {
    score[0][i] = i * penalty;
  }

  for (int i = 1; i <= len; i++) {
    for (int j = 1; j <= len; j++) {
      char char1 = seq1[i-1];
      char char2 = seq2[j-1];
      int current_score = substitution[getIndex(char1)][getIndex(char2)];
      int max1 = score[i-1][j] + penalty;
      int max2 = score[i][j-1] + penalty;
      int max3 = score[i-1][j-1] + current_score;
      score[i][j] = max(max(max1, max2), max3);
    }
  }

  for (int i = 0; i <= len; i++) {
    for (int j = 0; j <= len; j++) {
      cout << "score[" << i << "][" << j << "]: " << score[i][j] << endl;
    }
  }

  return score[len][len];
}

int main() {
  string seq1 = "AGCT";
  string seq2 = "AAGT";

  // string seq1 = "GACAT";
  // string seq2 = "CACAT";

  cout << scoreFunc(seq1, seq2) << endl;
}
