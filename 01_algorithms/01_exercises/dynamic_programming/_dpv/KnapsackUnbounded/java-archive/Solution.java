package dynamic_programming._dpv.KnapsackUnbounded;

public class Solution {

    public static int maxTotalValue(int totalAllowedWeight, int[] itemWeights, int[] itemValues) {
        int[] maxTotalValueTable = new int[totalAllowedWeight+1];
        for (int w = 1; w < totalAllowedWeight+1; w++) {
            for (int i = 0; i < itemWeights.length; i++) {
                if (itemWeights[i] <= w) {
                    maxTotalValueTable[w] = Math.max(maxTotalValueTable[w], itemValues[i] + maxTotalValueTable[w - itemWeights[i]]);
                }
            }
        }
        printArray(maxTotalValueTable);
        return maxTotalValueTable[totalAllowedWeight];
    }

    public static void printArray(int[] arr) {
        System.out.print("{");
        for (int item : arr) {
            System.out.print(" " + item + ",");
        }
        System.out.println("}");
    }

    public static void main(String[] args) {
        int[] itemWeights = new int[]{6, 3, 4, 2};
        int[] itemValues = new int[]{30, 14, 16, 9};
        System.out.println(maxTotalValue(10, itemWeights, itemValues));
        System.out.println();

        // simple test to check that
        // - you allow repeats of the same item.
        // - you optimize for the total value of items, not the total quantity of items.
        // - you calculate the correct maxTotalValue at various intermediate totalAllowedWeights (specifically at 8, 9, 10, 11, 14, 15, 16).
        itemWeights = new int[]{4, 5};
        itemValues = new int[]{1, 10};
        System.out.println(maxTotalValue(16, itemWeights, itemValues));
        System.out.println();
    }

}
