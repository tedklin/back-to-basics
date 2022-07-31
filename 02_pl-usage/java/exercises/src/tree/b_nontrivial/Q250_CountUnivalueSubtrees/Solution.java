package tree.b_nontrivial.Q250_CountUnivalueSubtrees;

import tree.TreeNode;

import java.util.HashSet;
import java.util.Set;

public class Solution {

    public int countUnivalSubtrees(TreeNode root) {
        Set<TreeNode> univalueSubtrees = new HashSet<>();
        collectUnivalueSubtrees(root, univalueSubtrees);
        return univalueSubtrees.size();
    }

    // Adds the roots of all univalue subtrees contained within the tree rooted at node.
    public void collectUnivalueSubtrees(TreeNode node, Set<TreeNode> univalueSubtrees) {
        if (node == null) {
            return;
        }

        // a subtree rooted at node is a univalue subtree iff
        // both of node's children are univalue subtrees AND both of node's children have the same value as node

        collectUnivalueSubtrees(node.left, univalueSubtrees);
        collectUnivalueSubtrees(node.right, univalueSubtrees);

        boolean isSubtreeUnivalue = true;

        if (node.left != null && (!univalueSubtrees.contains(node.left) || node.left.val != node.val)) {
            isSubtreeUnivalue = false;
        }
        if (node.right != null && (!univalueSubtrees.contains(node.right) || node.right.val != node.val)) {
            isSubtreeUnivalue = false;
        }

        if (isSubtreeUnivalue) {
            univalueSubtrees.add(node);
        }
    }

}
