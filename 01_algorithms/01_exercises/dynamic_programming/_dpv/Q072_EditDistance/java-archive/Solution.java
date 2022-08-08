package dynamic_programming._dpv.Q072_EditDistance;

import java.util.Arrays;

public class Solution {

/*
    Recursive step:
        minDistance(word1, word2)
            = min {
                1 + minDistance(word1[:-2], word2);     (deletion)
                1 + minDistance(word1, word2[:-2]);     (insertion)
                if word1[-1] == word2[-1], then consider minDistance(word1[:-2], word2[:-2])      (no-edit)
                    else consider 1 + minDistance(word1[:-2], word2[:-2]);      (replacement)
            }

    Recursive base cases:
        if word1.length == 0, then return word2.length;     (insertion)
        if word2.length == 0, then return word1.length;     (deletion)

    Avoid string copying by letting `i, j := current word1, word2 substring lengths`.
    Note that letting `i, j := current word1, word2 indices being considered` results in messy base cases.
        Recursive step:
            minDistance(word1, word2, i, j)
                = min {
                    1 + minDistance(word1, word2, i-1, j);     (deletion)
                    1 + minDistance(word1, word2, i, j-1);     (insertion)
                    if word1[i-1] == word2[j-1], then consider minDistance(word1, word2, i-1, j-1)      (no-edit)
                        else consider 1 + minDistance(word1, word2, i-1, j-1);      (replacement)
                }
        Recursive base cases:
            if i == 0, then return j;     (insertion of all that's left of word2)
            if j == 0, then return i;     (deletion of all that's left of word1)
 */

    public int minDistance(String word1, String word2) {
//        return minDistMemo(word1, word2);
        return minDistDP(word1, word2);
    }

    private int minDistMemo(String word1, String word2) {
        int[][] minDistTable = new int[word1.length()+1][word2.length()+1];
        for (int[] row: minDistTable) {
            Arrays.fill(row, -1);
        }
        return minDistMemoHelper(word1, word2, word1.length(), word2.length(), minDistTable);
    }

    private int minDistMemoHelper(String word1, String word2, int i, int j, int[][] minDistTable) {
        if (i == 0) return j;
        if (j == 0) return i;

        if (minDistTable[i-1][j] == -1) {
            minDistTable[i-1][j] = minDistMemoHelper(word1, word2, i-1, j, minDistTable);
        }
        if (minDistTable[i][j-1] == -1) {
            minDistTable[i][j-1] = minDistMemoHelper(word1, word2, i, j-1, minDistTable);
        }
        if (minDistTable[i-1][j-1] == -1) {
            minDistTable[i-1][j-1] = minDistMemoHelper(word1, word2, i-1, j-1, minDistTable);
        }

        int diffIJ = (word1.charAt(i-1) == word2.charAt(j-1)) ? 0 : 1;
        return Math.min(Math.min(1 + minDistTable[i-1][j], 1 + minDistTable[i][j-1]),
                        diffIJ + minDistTable[i-1][j-1]);
    }

    private int minDistDP(String word1, String word2) {
        int[] prevTableRow = new int[word2.length()+1];
        int[] currTableRow = new int[word2.length()+1];
        for (int j = 0; j < word2.length()+1; j++) {
            prevTableRow[j] = j;
        }
        for (int i = 1; i < word1.length()+1; i++) {
            currTableRow[0] = i;
            for (int j = 1; j < word2.length() + 1; j++) {
                int diffIJ = (word1.charAt(i - 1) == word2.charAt(j - 1)) ? 0 : 1;
                currTableRow[j] = Math.min(Math.min(1 + prevTableRow[j], 1 + currTableRow[j - 1]),
                        diffIJ + prevTableRow[j - 1]);
            }
            prevTableRow = currTableRow;
            currTableRow = new int[word2.length()+1];
        }
        return prevTableRow[word2.length()];
    }
}
