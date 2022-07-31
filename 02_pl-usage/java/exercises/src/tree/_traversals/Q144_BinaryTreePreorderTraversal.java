package tree._traversals;

import tree.TreeNode;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

class Q144_BinaryTreePreorderTraversal {

    // Recursive solution
//     public List<Integer> preorderTraversal(TreeNode root) {
//         List<Integer> result = new ArrayList<>();
//         preorderTraversalHelper(root, result);
//         return result;
//     }

//     private void preorderTraversalHelper(TreeNode node, List<Integer> result) {
//         if (node == null) {
//             return;
//         }

//         // visit node
//         result.add(node.val);

//         // recurse on left child
//         preorderTraversalHelper(node.left, result);

//         // recurse on right child
//         preorderTraversalHelper(node.right, result);
//     }

    // Iterative solution
    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();

        Deque<TreeNode> stack = new ArrayDeque<>();
        if (root != null) {
            stack.push(root);
        }
        while (!stack.isEmpty()) {
            TreeNode node = stack.pop();

            // visit node
            result.add(node.val);

            // note that we push the right child before the left, so the left gets popped/visited next
            if (node.right != null) {
                stack.push(node.right);
            }
            if (node.left != null) {
                stack.push(node.left);
            }
        }

        return result;
    }
}
