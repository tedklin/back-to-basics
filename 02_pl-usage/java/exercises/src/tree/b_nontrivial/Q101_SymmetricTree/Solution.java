package tree.b_nontrivial.Q101_SymmetricTree;

import tree.TreeNode;

public class Solution {

    // Standard recursive solution
    public boolean isSymmetric(TreeNode root) {
        return areSubtreesReflections(root.left, root.right);
    }

    private boolean areSubtreesReflections(TreeNode leftRoot, TreeNode rightRoot) {
        if (leftRoot == null && rightRoot == null) {
            return true;
        }
        if (leftRoot == null || rightRoot == null || leftRoot.val != rightRoot.val) {
            return false;
        }
        return areSubtreesReflections(leftRoot.left, rightRoot.right) && areSubtreesReflections(leftRoot.right, rightRoot.left);
    }

    // Iterative solution (DFS version)
    // public boolean isSymmetric(TreeNode root) {
    //     Deque<TreeNode> stack = new LinkedList<>();
    //     stack.push(root.right);
    //     stack.push(root.left);
    //     while (!stack.isEmpty()) {
    //         TreeNode leftMirror = stack.pop();
    //         TreeNode rightMirror = stack.pop();
    //         if (leftMirror == null && rightMirror == null) {
    //             continue;
    //         }
    //         if (leftMirror == null || rightMirror == null || leftMirror.val != rightMirror.val) {
    //             return false;
    //         }
    //         stack.push(rightMirror.right);
    //         stack.push(leftMirror.left);
    //         stack.push(rightMirror.left);
    //         stack.push(leftMirror.right);
    //     }
    //     return true;
    // }
}
