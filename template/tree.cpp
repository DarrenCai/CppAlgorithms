/**
 * 树相关
 */

/**
 * Morris遍历
 * Morris遍历的实质是避免使用栈，利用底层结点空闲的 right 指针指回上层的某个结点，从而完成下层到上层的移动。
 * 由于遍历回到某个上层结点时，又置空了底层结点的 right 指针，最终并不会改变原始树的结构。
 */
namespace morris
{
    struct node {int val; node *left, *right;};

    void morris(node* root) {
        while (root != nullptr) {
            if (root->left != nullptr) {
                node *p = root->left;
                while (p->right && p->right != root) p = p->right; // 找到当前结点的左子树的最右结点
                if (p->right == nullptr) {
                    // 如果最右结点的right指针为空，将其指向当前结点，并进入左子树
                    p->right = root;
                    root = root->left;
                } else {
                    // 最右结点的right指针指回了当前结点，说明左子树已经遍历完毕，需要断开链接，进入右子树
                    // todo cout << root->val << endl;
                    p->right = nullptr;
                    root = root->right;
                }
            } else {
                // 当前结点没有左子结点，进入右子树
                // todo cout << root->val << endl;
                root = root->right;
            }
        }
    }
}
