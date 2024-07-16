#  Find Match Count Given a Set of Pre Defined Words and File

## How to run program?

This project includes a xcode template. The project can be opened using xcode on a mac. The program will contain 2 files, PredefinedWords and File. The program will read values from these two files and print the output into console.

The executable is added in a folder exec under the main project. This will allow program execution without compiling the project. (Given xcode is not available in the given machine). The executable will present an error of file not found and an absolute path to the file will allow the program to ingest content from the file.


## What has been tested? 
'''

Line 1: Detecting first names is tricky to do even with AI. 

Line 2: how do you say a street name is not a first name?  

  

And a sample list of predefined words: 

Name 

Detect 

AI 
'''

The example case provided in the problem state has been tested. In addition an article from nytimes was tested using the program and verified using manual control+F tool in the browser.

'''
The following article from nytimes has been tested. With predefined words of length 1, 2, 3. Used find tool to get the count for words and verified result with output of the program.
https://www.nytimes.com/live/2024/07/15/us/trump-rnc-news-biden
'''

## Assumptions

1. Read line will not cause overflow while reading a line from file input.
2. Match count is not going to cause integer overflow.
3. Results printed to the console are sufficient.
