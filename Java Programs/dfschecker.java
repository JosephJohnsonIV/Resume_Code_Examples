/*
 * Fenel A. Joseph
 * Joseph Johnson IV
 *
 * Program to check whether student paths in graphs are proper Depth First Search paths
 * Computer Science 2
 */

import java.io.*;
import java.util.Scanner;

public class dfschecker
{
	// Main Class
	public static void main(String[] args) throws FileNotFoundException
	{
		// Initializing variable(s)
		int numVertices, students, i, j;
		String fileName;
		boolean valid;
		Scanner sc = new Scanner(System.in);

		// Prompting the user to enter the name of the input file
		System.out.println("Please enter the name of the input file (including file extension) :");

		// Storing the name of the file
		fileName = sc.nextLine();

		sc.close();

		// Initializing scanner using the file name entered by the user
		Scanner input = new Scanner(new File(fileName));

		// Our number of verteces is read in first
		numVertices = input.nextInt();

		// Had to do this to get the scanner to the next line
		input.nextLine();

		// Initialing double
		String vertices[][] = new String[ numVertices ][];

		// Reading in the connect verteces. For instance verterces[0] contain the verteces connected to vertex 1
		for (i = 0; i < numVertices; i++) {
			vertices[ i ] = input.nextLine().split(" ");
		}

		// Read in numbers to student paths to check
		students = input.nextInt();

		for (i = 0; i < students; i++)
		{
			int path[] = new int[5];

			// Read in this particular students' path
			for (j = 0; j < 5; j++)
			{
				path[j] = input.nextInt();
			}

			// check whether path is validi DFS. If DFS, valid = true, valid = false otherwise
			valid = check( numVertices, vertices, path);

			// Print feedback to screen, then move on
			if ( valid )
			{
				System.out.println("CORRECT!");
			}
			else
			{
				System.out.println("SORRY, NOT A VALID SEARCH!");
			}

			System.out.println();

		}

		input.close();
	}

	// Function used to determine whether passed in path is valid DFS
	public static boolean check (int numVertices, String[][] vertices, int[] path)
	{
		boolean visited[] = new boolean[ numVertices ];
		int i;

		// Initiate all elements of visited to false as we have not visited any verteces yet
		for ( i = 0; i < numVertices; i++)
		{
			visited[i] = false;
		}

		// traverse through passed in path
		for ( i = 0; i < 5; i++)
		{

			if ( i != 0 )
			{
				// First check if current vertex is connected to previous vertex
				// If true, continue, otherwise return false
				// We only do this for every vertex after the first one
				if ( !(hasEdgeWith( path[i], vertices[ path[i-1]-1 ])) )
				{
					return false;
				}
			}

			// Next check to make sure we have not already visited this vertex.
			// If we have, return false
			if ( visited[ path[i]-1 ] )
			{
				return false;
			}
			// In the case we haven't already, we have now, so make it true
			else
			{
				visited[ path[i]-1 ] = true;
			}
		}

		return true;
	}

	// Function determines whether passed in vertex, edgeTo, is among the vertices of
	// the passed in connections of another node
	public static boolean hasEdgeWith (int edgeTo, String[] edges)
	{
		for (int i = 0; i < edges.length; i++)
		{
			if (edgeTo == Integer.parseInt(edges[i]) )
				return true;
		}

		return false;
	}
}
