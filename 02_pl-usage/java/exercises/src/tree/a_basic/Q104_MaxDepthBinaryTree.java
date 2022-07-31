package tree.a_basic;

import tree.TreeNode;

public class Q104_MaxDepthBinaryTree {

    // Naive solution
    // public int maxDepth(TreeNode root) {
    //     if (root == null) {
    //         return 0;
    //     }
    //     return maxDepthHelper(root, 1);
    // }

    // // Notice the return value and the second parameter are the same thing, so the design of this helper
    // // function signature is not optimal. In fact, you don't need a helper. Trust the recursive leap of faith!
    // private int maxDepthHelper(TreeNode node, int depthSoFar) {
    //
    //     // This entire if/else clause shows bad practice: "arms-length" recursion
    //
    //     if (node.left == null && node.right == null) {
    //         return depthSoFar;
    //     } else if (node.left == null) {
    //         return maxDepthHelper(node.right, depthSoFar + 1);
    //     } else if (node.right == null) {
    //         return maxDepthHelper(node.left, depthSoFar + 1);
    //     }
    //     return Math.max(maxDepthHelper(node.left, depthSoFar+1), maxDepthHelper(node.right, depthSoFar+1));
    // }

    public int maxDepth(TreeNode root) {
        if (root == null) {
            return 0;
        }
        return 1 + Math.max(maxDepth(root.left), maxDepth(root.right));
    }

}
