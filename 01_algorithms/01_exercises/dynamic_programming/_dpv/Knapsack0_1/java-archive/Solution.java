package dynamic_programming._dpv.Knapsack0_1;

public class Solution {

    public static int maxTotalValue(int totalAllowedWeight, int[] itemWeights, int[] itemValues) {
//        // without memory-saving
//        int[][] maxTotalValue = new int[itemWeights.length][totalAllowedWeight+1];
//        for (int w = 1; w < totalAllowedWeight+1; w++) {
//            if (w - itemWeights[0] >= 0) {
//                maxTotalValue[0][w] = itemValues[0];
//            }
//        }
//        for (int j = 1; j < itemWeights.length; j++) {
//            for (int w = 1; w < totalAllowedWeight+1; w++) {
//                if (w - itemWeights[j] >= 0) {
//                    maxTotalValue[j][w] = itemValues[j] + maxTotalValue[j-1][w - itemWeights[j]];
//                }
//                maxTotalValue[j][w] = Math.max(maxTotalValue[j][w], maxTotalValue[j-1][w]);
//            }
//        }
//        print2DArray(maxTotalValue);
//        return maxTotalValue[itemWeights.length-1][totalAllowedWeight];


        int[] maxTotalValuePrevRow = new int[totalAllowedWeight+1];
        int[] maxTotalValueCurrRow = new int[totalAllowedWeight+1];
        for (int j = 0; j < itemWeights.length; j++) {
            for (int w = 1; w < totalAllowedWeight+1; w++) {
                if (w - itemWeights[j] >= 0) {
                    maxTotalValueCurrRow[w] = itemValues[j] + maxTotalValuePrevRow[w - itemWeights[j]];
                }
                maxTotalValueCurrRow[w] = Math.max(maxTotalValueCurrRow[w], maxTotalValuePrevRow[w]);
            }
            maxTotalValuePrevRow = maxTotalValueCurrRow;
            maxTotalValueCurrRow = new int[totalAllowedWeight+1];
        }
        return maxTotalValuePrevRow[totalAllowedWeight];
    }

    public static void printArray(int[] arr) {
        System.out.print("{");
        for (int item : arr) {
            System.out.print(" " + item + ",");
        }
        System.out.println("}");
    }

    public static void print2DArray(int[][] mat) {
        System.out.print("{");
        for (int[] row : mat) {
            printArray(row);
        }
        System.out.println("}");
    }

    public static void main(String[] args) {
        int[] itemWeights = new int[]{6, 3, 4, 2};
        int[] itemValues = new int[]{30, 14, 16, 9};
        System.out.println(maxTotalValue(10, itemWeights, itemValues));
        System.out.println();

        // simple test to check that
        // - you don't take repeats of the same item.
        // - you don't just always take the first item you see, leaving no room for other potentially more valuable items.
        itemWeights = new int[]{2, 3};
        itemValues = new int[]{2, 3};
        System.out.println(maxTotalValue(4, itemWeights, itemValues));
        System.out.println();
    }

}
