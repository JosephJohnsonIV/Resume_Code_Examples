/* Program to Encode, Decode, and Crack Caesar's encryption
 * Computer Science 2
 *
 * Joseph Johnson IV
 * Fenel A. Joseph
 */

public class Cipher {

	private static float[] table = new float[]
			{8.2f,1.5f,2.8f,4.3f,12.7f,2.2f,2.0f,6.1f,7.0f,
			0.2f,0.8f,4.0f,2.4f,6.7f,7.5f,1.9f,0.1f,6.0f,
			6.3f,9.1f,2.8f,1.0f,2.4f,0.2f,2.0f,0.1f};

	// Method to convert a character to a natural number
	private static int Let2Nat(char let)
	{
		return (let - 'a');
	}

	// Method to convert a natural number to a character
	private static char Nat2Let(int nat)
	{
		return (char)(nat + 'a');
	}

	// Method to return a new character after shifting a number of times
	private static char Shift(char let, int shift)
	{
		if (Let2Nat(let) > 25 || Let2Nat(let) < 0)
			return let;

		return Nat2Let((Let2Nat(let) + shift) % 26);
	}

	// Method to encode a string using Caesar's encryption and a shift value
	private static String Encode(int shift, String word)
	{
		// Need to create a character array to hold the shifted characters
		char[] newWord = new char[word.length()];

		// Calculate the new shifted character for each character in the original string
		for (int i = 0; i < word.length(); i++)
			newWord[i] = Shift(word.charAt(i), shift);

		// Create a new string to hold the character array and return it
		return new String(newWord);
	}

	// Method to decode a string encrypted with Caesar's encryption
	private static String Decode(int shift, String coded)
	{
		// Character array to hold the decoded characters
		char[] decoded = new char[coded.length()];

		// Calculate the original character for each shifted character
		for (int i = 0; i < coded.length(); i++)
			decoded[i] = Shift(coded.charAt(i), (shift * -1));

		// Return a new string to hold the character array
		return new String(decoded);
	}

	// Method to count lowercase letters in a string
	private static int Lowers(String word)
	{
		int numLowers = 0;

		// If the character remains within the range of 0-25 after subtracting 'a' then it is a lowercase character
		for (int i = 0; i < word.length(); i++)
			if (Let2Nat(word.charAt(i)) <= 25 && Let2Nat(word.charAt(i)) >= 0)
				numLowers++;

		return numLowers;
	}

	// Method to count the number of appearances of a letter in a string
	private static int count(String word, char key)
	{
		int num = 0;

		for (int i = 0; i < word.length(); i++)
			if (key == word.charAt(i))
				num++;

		return num;
	}

	// Method to find the percentage of an integer wiith respect to another
	private static float percent(int a, int b)
	{
		return ((float) a/b) * 100;
	}

	// Method to calculate the frequency of each character of the alphabet in a string
	private static float[] freqs(String word)
	{
		int[] count = new int[26];
		float[] f = new float[26];

		// Initializing the count for each character
		for (int i = 0; i < 26; i++)
			count[i] = 0;

		// Increment the index associated with each character when we find it
		for (int i = 0; i < word.length(); i++)
			count[Let2Nat(word.charAt(i))]++;

		// Adjust the values to be percentages
		for (int i = 0; i < 26; i++)
			f[i] = ((float) count[i] / word.length()) * 100;

		return f;
	}

	// Method to shift all values in an array by a specified amount
	private static float[] rotate(int n, float[] f)
	{
		int index = 0;
		int length = f.length;

		float[] result = new float[length];

		// Create a new array and fill it with the new order of values
		for(int i = n; i < length; i++)
			result[index++] = f[i];

		// Place the shifted values at the end of the new array
		for(int j = 0; j < n; j++)
			result[index++] = f[j];

		return result;
	}

	// Method to calculate the chisqr
	private static float chisqr(float[] os, float[] es)
	{
		float result = 0;

		// The equation for chisqr
		for (int i = 0; i < os.length; i++)
			result += ((float)(os[i] - es[i]) * (os[i] - es[i])) / es[i];

		return result;
	}

	// Method to find what index a value is stored at
	private static int position(float n, float[] list)
	{
		for(int i = 0; i < list.length; i++)
			if (list[i] == n)
				return i;

		return -1;
	}

	// Method to crack the Caesar encryption
	private static String crack(String s)
	{
		int position = 0;
		float min = 99999;
		float[] freq;
		float[] chiSquaredList;

		freq = freqs(s);
		chiSquaredList = new float[26];

		// Running chisqr on the frequency array for the string for all shift values 0-25 and storing them
		for (int i = 0; i < 26; i++)
		{
			chiSquaredList[i] = chisqr(rotate(i, freq), table);

			// Keeping track of the minimum value of chisqr and its location
			if (min > chiSquaredList[i])
			{
				min = chiSquaredList[i];
				position = i;
			}
		}
		// Returning the result of decoding using the calculated shift value
		return Decode(position, s);
	}


	// Start count at length - n, mod by length.
	public static void main(String[] args)
	{
		//Examples of our helper functions at work
		System.out.println(Decode(3, Encode(3, "haskellisfun")));
		System.out.println(Lowers("haskellisfun"));
		System.out.println(count("haskellisfun", 's'));
		System.out.println(percent(2,12));
		System.out.println();

		//Examples of decode and crack that work
		System.out.println(crack( Encode(3, "wearecomputerengineeringmajors")));

		System.out.println(crack(Encode(3, "wehopetogetanainthisclass")));

		System.out.println(crack(Encode(3, "wealsohopetograduatesoon")));

		System.out.println(crack(Encode(3, "starspangledbanner")));

		System.out.println(crack(Encode(3, "thisisjustatestofmyprogram")));
		System.out.println();

		//Instances when crack() was unsuccessful
		System.out.println(crack(Encode(3, "graham")));

		System.out.println(crack(Encode(3, "unknown")));

		System.out.println(crack(Encode(3, "apple")));
	}

}
