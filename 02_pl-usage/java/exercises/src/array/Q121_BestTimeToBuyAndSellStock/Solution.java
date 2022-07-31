package array.Q121_BestTimeToBuyAndSellStock;

public class Solution {

    public int maxProfit(int[] prices) {
        int maxProfit = 0;
        int minPriceSoFar = prices[0];
        for (int i = 0; i < prices.length; i++) {
            // "prices[i] - minPriceSoFar" gives us the (local) max profit with i as the "sell" point
            maxProfit = Math.max(maxProfit, prices[i] - minPriceSoFar);
            minPriceSoFar = Math.min(minPriceSoFar, prices[i]);
        }
        return maxProfit;
    }

}
