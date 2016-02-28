##Joseph Johnson IV
##Introduction to C Programming
##Program to encrypt and decrypt strings using the ROT13 algorithm

#These are our two messages.

msg1 = 'pythonprogramming'
msg2 = 'isthebest'

#Here are the two rot13 encoding functions from the last project.
#We will re-use these to encrypt the messages.

def encrypt_letter(letter):
    letter_code = ord(letter)-ord('a')
    letter_code = (letter_code+13)%26
    new_letter = chr(letter_code+ord('a'))
    return new_letter
def decrypt_letter(letter):
    letter_code = ord(letter)-ord('a')
    letter_code = (letter_code-13)%26
    new_letter = chr(letter_code+ord('a'))
    return new_letter

#This function will be used to encrypt an entire string.

def encrypt_string(msg):

#First we need to set our initial values.

    out_msg = ''
    i = 0

#Now we create a while loop to encode each letter in our message and print them.

    while i < len(msg):
        out_letter = encrypt_letter(msg[i]) #This step brings in the encrypt_letter function to encrypt each letter in the loop.
        print(out_letter, end = '')
        i += 1 #Have to remember to increase our index after each cycle.

#This function will be used to decrypt a string.

def decrypt_string(msg):

#Again, setting initial values.

    dout_msg = ''
    i = 0

#Again, another while loop for encoding the letters.

    while i < len(msg):
        dout_letter = decrypt_letter(encrypt_letter(msg[i])) #This time we use the decrypt_letter function to decrypt each letter in the loop.
        print(dout_letter, end = '')
        i += 1 #Remembering again to increase our index.

#Finally, call our functions to display the encrypted and decrypted messages.

print('Message 1 encrypted is:')
encrypt_string(msg1)
print('\n')
print('Message 1 decrypted is:')
decrypt_string(msg1)
print('\n')
print('Message 2 encrypted is:')
encrypt_string(msg2)
print('\n')
print('Message 2 decrypted is:')
decrypt_string(msg2)
