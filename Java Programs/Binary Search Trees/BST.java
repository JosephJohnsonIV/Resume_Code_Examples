/*
 * Fenel Joseph
 * Joseph Johnson IV
 *
 * Computer Science 2
 * Program to create a Binary Search tree
 * This file holds the BST Class
 */


public class BST
{
	// This is the root node, which starts off as null
	//   when the BST is empty.
	BSTNode m_objRootNode;

	// Class constructor.
	public BST()
	{
		// Not really necessary, provided for clarity.
		m_objRootNode = null;
	}

	// Method to see if the tree is empty.
	public boolean IsEmpty()
	{
		// Return a boolean indicating whether the
		//   three is empty or not.
		return( m_objRootNode == null );
	}

	/* Functions to search for an element */
    public BSTNode Search( int nKeyValue )
    {
        return( Search( m_objRootNode, nKeyValue ) );
    }

    // Method to search for an element recursively.
    private BSTNode Search( BSTNode objNode, int nKeyValue )
    {

    	if( objNode == null )
    	{
    		return( null );
    	}

    	// First, we get the key value for this node.
    	int nThisKeyValue = objNode.GetKeyValue();

    	// See if the passed in key value is less. If so,
    	//   this indicates that we need to go left.
    	if( nKeyValue < nThisKeyValue )
    	{
    		// Get the left node object reference so we
    		//   can walk down it.
    		objNode = objNode.GetLeftNode();
    	}

    	// See if the passed in key value is greater. If so,
    	//   this indicates that we need to go right.
    	else if( nKeyValue > nThisKeyValue )
    	{
    		// Get the right node object reference so we
    		//   can walk down it.
    		objNode = objNode.GetRightNode();
    	}

    	// Here we have found the node with the key
    	//   value that was passed in.
    	else
    	{
    		return( objNode );
    	}

    	// Now call Search recursively.
    	return( Search( objNode, nKeyValue ) );
	}

    // This method inserts a node based on the key value.
    public void Insert( int nKeyValue )
    {
    	// The root node is returned to m_objRootNode from Insert()
    	m_objRootNode = Insert( nKeyValue, m_objRootNode );
    }

    // Class protected (internal) method to insert nodes. This method
    //   will be called recursively.
    protected BSTNode Insert( int nKeyValue, BSTNode objNode )
    {

    	BSTNode lastLocation = objNode;

    	// This node is null and simply needs to be allocated.
        if( objNode == null )
        {
        	objNode = new BSTNode( nKeyValue );
        	objNode.m_nSubtreeSize++;

        	return objNode;
        }

        // If the value we are inserting is less than 3 away from any of its parent nodes then we cannot insert it
        if (Math.abs(nKeyValue - objNode.GetKeyValue()) < 3 )
        	return null;

        objNode.m_nSubtreeSize++;

        // Here we need to walk left.
        if( nKeyValue < objNode.GetKeyValue() )
        {
        	// Set the left node of this object by recursively walking left.
        	objNode.SetLeftNode( Insert( nKeyValue, objNode.GetLeftNode() ) );

        	// If the node we just attempted to insert failed, we need to go back and fix the subtree sizes
        	if (objNode.GetLeftNode() == null)
        		fixSizing(objNode, lastLocation, nKeyValue);
        }

        // Here we need to talk right.
        else if( nKeyValue > objNode.GetKeyValue() )
        {
        	// Set the right node of this object by recursively walking right.
        	objNode.SetRightNode( Insert( nKeyValue, objNode.GetRightNode() ) );

        	// If the node we just attempted to insert failed, we need to go back and fix the subtree sizes
        	if (objNode.GetLeftNode() == null)
        		fixSizing(objNode, lastLocation, nKeyValue);
        }

        return( objNode );
    }

    //Method to return the node holding the lowest value
    public BSTNode GetMax(BSTNode objNode)
    {
    	//By definition, the right child must be greater than the parent. If there is a right child we will move to it and check again.
    	if (objNode.GetRightNode() != null)
    		GetMax(objNode.GetRightNode());

    	//If the right child is null, then this is the node holding the greatest value
    	return objNode;
    }

    //Method to return the node holding the smallest value
    public BSTNode GetMin(BSTNode objNode)
    {
    	//By definition, the left child must be less than the parent. If there is a left child we will move to it and check again.
    	if (objNode.GetLeftNode() != null)
    		GetMin(objNode.GetLeftNode());

    	//If the left child is null, then this is the node holding the least value
    	return objNode;
    }

    // Method to repair the sub tree sizing in our tree.
    private void fixSizing(BSTNode start, BSTNode finish, int failedValue)
    {
    	// First we go to the beginning node and decrement the subtree size
    	BSTNode temp = start;
    	temp.m_nSubtreeSize--;

    	// If we traversed down the right side, we need to fix the right side
    	if (failedValue > start.GetKeyValue())
    	{
    		// Until we get to the node that we stopped at, we will continue to the right and decrement each subtreesize.
    		while( temp.equals(finish) == false)
    		{
    			temp = start.GetRightNode();
    			temp.m_nSubtreeSize--;
    		}
    	}

    	// If we traversed down the left side, we need to fix the left side
    	if (failedValue < start.GetKeyValue())
    	{
    		// Until we get to the node that we stopped at, we will contiue to the left and decrement each subtreesize
    		while (temp.equals(finish) == false)
    		{
    			temp = start.GetLeftNode();
    			temp.m_nSubtreeSize--;
    		}
    	}
    }

    // Method to find the node holding the key value and delete it
    public BSTNode Delete ( BSTNode objNode, int nKeyValue )
	{
		BSTNode tempNode = Search( objNode, nKeyValue );

		// BASE CASE Condition #1: value not in BST. return null
		if ( tempNode == null )
		{
			return null;
		}

		// BASE CASE Condition #2: value is the root of passed in BST/BST subtree
		if ( objNode.m_nKeyValue == nKeyValue )
		{
			// Root of passed in BST/BST subtree only has one child, so that child replaces it. In this case its the
			// right child that exists
			if ( objNode.m_objLeftNode == null )
				return objNode.m_objRightNode;
			// Root of passed in BST/BST subtree only has one child, so that child replaces it. In this case its the
			// left child that exists
			else if ( objNode.m_objRightNode == null )
				return objNode.m_objLeftNode;
			// Node has two children, we are going to replace our root with the largest value in its left subtree.
			else
			{
				// Set our temp BSTNode to the left subtree of our current root
				BSTNode temp = objNode.m_objLeftNode;

				// Keep going into the right subtree of our temp (if it exists) to get the largest value
				while ( temp.m_objRightNode != null )
				{
					temp.m_nSubtreeSize--;

					temp = temp.m_objRightNode;
				}

				// replace our roots KeyValue with the largest KeyValue in its left subtree
				objNode.m_nKeyValue = temp.m_nKeyValue;

				// Delete that KeyValue from the roots left subtree, finishing the substitution
				Delete( objNode.m_objLeftNode, temp.m_nKeyValue );
			}
		}

		// Value is in subtree so decrement the SubtreeSize
    	objNode.m_nSubtreeSize--;

    	// Condition #4: value is in the only node in the subtree, so when we decremented, the subtree size
    	// is now 0. So just make sure the right and left subtrees are null
    	if ( objNode.m_nSubtreeSize == 0 )
    	{
    		objNode.m_objLeftNode = objNode.m_objRightNode = null;
    		return objNode;
    	}

    	// Condition #5: value is in node that is currently in the left subtree. We now pass the left subtree to our
    	// Delete() function;
    	if ( objNode.m_nKeyValue > nKeyValue )
    	{
    		objNode.m_objLeftNode = Delete( objNode.m_objLeftNode, nKeyValue );
    	}
    	// Condition #6: value is in the node that is currently in the right subtree. We now pass the right subtree to
    	// our Delete() function
    	else
    	{
    		objNode.m_objRightNode = Delete( objNode.m_objRightNode, nKeyValue );
    	}

    	return objNode;
	}

}
