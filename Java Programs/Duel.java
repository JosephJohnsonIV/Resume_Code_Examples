/* Program to help philosophers order a set of essays.
 * Computer Science 2
 *
 * Joseph Johnson IV
 * Fenel A. Joseph
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Duel {

	// Function to count how many different ways the essays can be ordered
	public static int countOrder(int numEssays, int[] numIncoming)
	{
		int numOptions = 0;

		// We number of ways we can order the essays can be counted by counting how many essays are not dependent on others
		for (int i = 1; i < numEssays; i++)
		{
			if (numIncoming[i] == 0)
				numOptions++;
		}

		return numOptions;
	}

	public static void main(String[] args) throws FileNotFoundException {

		// Creating variables to store data that will be read from the file
		int numEssays, numShared, result;
		int  defined, used;
		int[] numIncoming;
		boolean[][] dependency;

		Scanner sc = new Scanner(new File("Essays.txt"));

		// We want the scanner to keep going through the file as long as there is input left
		while (sc.hasNextLine())
		{
			// The first two numbers in each set will represent the number of essays and relationships in each set
			numEssays = sc.nextInt();
			numShared = sc.nextInt();

			// The zeroes at the end signify the end of the file and do not need to be counted
			if (numEssays == 0 && numShared == 0)
				break;

			// This array will hold the number of dependencies each essay has
			numIncoming = new int[numEssays + 1];

			// This will be an adjacency map holding the relationships of each pair
			dependency = new boolean[numEssays + 1][numEssays + 1];

			// For loop to collect the rest of the data in the input
			for (int i = 0; i < numShared; i++)
			{
				// Scanning in the pairings
				defined = sc.nextInt();
				used = sc.nextInt();

				// Setting that pair in the adjacency map to true to signify that they are related
				dependency[defined][used] = true;

				// Incrementing the number of dependencies the second number in the pair has so far
				numIncoming[used]++;
			}

			// Calculating the result of this set
			result = countOrder(numEssays, numIncoming);

			// Outputting the results
			if (result >= 2)
				System.out.println(2);

			else
				System.out.println(result);
		}

		// Remembering to close the scanner
		sc.close();
	}
}
