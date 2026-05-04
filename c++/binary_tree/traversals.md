```sh
 1
2 3
1,2,3

dfs node                    st=[node]
    if not node return      st.pop node, go to parent, if none exit
    print(node)             process cur node, print/push
    dfs(node->left)         try push node.left.. till no left
    dfs(node->right)        try push node.right.. till no right, then parent

# pre-order
if node
    stack push node
    print node
    node = left-child
else
    if stack empty, exit
    else
        node = stack.top.right
        pop node    
```
```sh
 1
2 3
1,2,3

dfs node                    st.push node
    if not node return      pop node for parents, or EXIT
    dfs(node->left)         push node.left
    print(node)             print node after all left, done
    dfs(node->right)        push node.right

# in-order
if node
    stack push node    
    node = left-child . aka push left till left not null
else
    if stack empty, exit
    else        
        node = stack.top
        pop
        print(node)
        node = node.right     
```
# post-order
```sh
# post order
#  1
# 2 3
# [2,3,1]

#    1
#  2   3
# 4 5 6 7
# [ 4 5 2 6 7 3 1 ]

dfs node                    st.push node
    if not node return      pop node for parents, or EXIT
    dfs(node->left)         push node.left
    dfs(node->right)        push node.right
    print(node)             print node after right, done


n   = n
lv  = 1
st  = []
res = [4,5,2,6,7,3,1]

if node
    push node
    node = node->left
else
    if stack empty EXIT # no parents left, EXIT

    node = st.top

    # go right only once
    if node->right && last_visited != node->right
        node = node->right
    else
        node = st.pop
        last_visited = node
        print(node)
        node = node->right or null?
```
```sh

#    1
#  2   3
# 4 5 6 7

# [ 4 5 2 6 7 3 1 ]
```