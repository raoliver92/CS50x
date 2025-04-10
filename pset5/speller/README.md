# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

an artificial long word said to mean a lung disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

returns information describing the resources utilized by the current proces, or all its terminated child processes. 

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

If you pass by reference you can actually return values from the function as for passing by value the values are lost after the function is through being called on the stack. 

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Main reads in a dictionary to use as a reference to check spelling and the second argument is a text file that is opened to check against the dictionary. 

Inside of the 'for loop' the file is then used to read in each character inside of the file one at a time and if it is a Alphabetical character or apostraphe, the character is added into the 'word' array. The index is then increased by 1. If the index is more than 45 characters long, then the index is reset to 0 because it is considered not a word. 
If the character contains digits, it is ignored and index is reset back to 0. 

If the index is is greater than 0, then it proves that there is a word and a terminating character is added to the end of the array. The word counter is then raised by 1 to increase the amount of words found in the text file. A check function is then ran to see if the word is misspelled and put into a bool value to determine misspelled or not, if so the misspelled counter is increased by one. Index is then reset to 0 to prepare for the next word. 

If errors are encountered, the file is closed and a line is written to the command line stating and error along with the word. The dictionary is also unloaded at this time to free memory. 

If all is correct, the file is closed and dictionary is unloaded.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

By using fgetc, we are only reading 1 character at a time to add to the array if needed and skipped if not. If we used fscanf, we would be reading in a chunk of strings at a time and then break down each character which could result in loss of speed and only have to scan the character once instead of twice.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

These will be a pointer to location in memory for these files which will never change at run time. 
