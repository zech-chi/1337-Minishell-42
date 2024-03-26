void update_lst(t_lst **head)
{
    t_lst *node;
    char *str;
	t_lst *temp;

    node = *head;
    while (node && node->next)
    {
        if (node->type == REDIRECTION && node->next->type == OUTFILE)
        {
            str = ft_strjoin(node->value, node->next->value);
            node->value = str;
            temp = node->next;
			node->prio = node->next->prio;
            node->next = node->next->next;
            free(temp);
        }
    	node = node->next;
    }
}







t_tree* insertIntoBST(t_tree* root, char *value) 
{
   if (!root)
        return (new_node(value));
    else
    {
        if (root->value < value)
            root -> right = insertIntoBST(root->right, value);
        else if (root->value > value)
           root->left = insertIntoBST(root->left, value);
    }
    return (root);
}