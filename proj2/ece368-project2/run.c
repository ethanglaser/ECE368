#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv){
	system("gcc -Wall -Werror -O3 huff.c -o huffman");
	system("gcc -Wall -Werror -O3 unhuff.c -o unhuffman");
	system("time huffman test1.txt");
	system("time huffman text0.txt");
	system("time huffman text1.txt");
	system("time huffman text2.txt");
	system("time huffman text3.txt");
	system("time huffman text4.txt");
	system("time huffman text5.txt");
	system("time unhuffman test1.txt.huff");
	system("time unhuffman text0.txt.huff");
	system("time unhuffman text1.txt.huff");
	system("time unhuffman text2.txt.huff");
	system("time unhuffman text3.txt.huff");
	system("time unhuffman text4.txt.huff");
	system("time unhuffman text5.txt.huff");
	//system("du -b test1.txt");
	//system("du -b text0.txt");
	//system("du -b text1.txt");
	//system("du -b text2.txt");
	//system("du -b text3.txt");
	//system("du -b text4.txt");
	//system("du -b text5.txt");
	//system("du -b test1.txt.huff");
	//system("du -b text0.txt.huff");
	//system("du -b text1.txt.huff");
	//system("du -b text2.txt.huff");
	//system("du -b text3.txt.huff");
	//system("du -b text4.txt.huff");
	//system("du -b text5.txt.huff");
	system("xxd -b test1.txt.huff > test1bin.txt");
	system("echo \"Checking Output of test1:\"");
	system("if [[ $(diff test1.txt test1.txt.huff.unhuff) == '' ]]; then echo \"scale = 10 ; $(du -b test1.txt.huff | cut -f1)/$(du -b test1.txt | cut -f1)\" | bc; else echo \"FAILED\"; fi");
	system("echo \"Checking Output 0:\"");
	system("if [[ $(diff text0.txt text0.txt.huff.unhuff) == '' ]]; then echo \"scale = 10 ; $(du -b text0.txt.huff | cut -f1)/$(du -b text0.txt | cut -f1)\" | bc; else echo \"FAILED\"; fi");
	system("echo \"Checking Output 1:\"");
	system("if [[ $(diff text1.txt text1.txt.huff.unhuff) == '' ]]; then echo \"scale = 10 ; $(du -b text1.txt.huff | cut -f1)/$(du -b text1.txt | cut -f1)\" | bc; else echo \"FAILED\"; fi");
	system("echo \"Checking Output 2:\"");
	system("if [[ $(diff text2.txt text2.txt.huff.unhuff) == '' ]]; then echo \"scale = 10 ; $(du -b text2.txt.huff | cut -f1)/$(du -b text2.txt | cut -f1)\" | bc; else echo \"FAILED\"; fi");
	system("echo \"Checking Output 3:\"");
	system("if [[ $(diff text3.txt text3.txt.huff.unhuff) == '' ]]; then echo \"scale = 10 ; $(du -b text3.txt.huff | cut -f1)/$(du -b text3.txt | cut -f1)\" | bc; else echo \"FAILED\"; fi");
	system("echo \"Checking Output 4:\"");
	system("if [[ $(diff text4.txt text4.txt.huff.unhuff) == '' ]]; then echo \"scale = 10 ; $(du -b text4.txt.huff | cut -f1)/$(du -b text4.txt | cut -f1)\" | bc; else echo \"FAILED\"; fi");
	system("echo \"Checking Output 5:\"");
	system("if [[ $(diff text5.txt text5.txt.huff.unhuff) == '' ]]; then echo \"scale = 10 ; $(du -b text5.txt.huff | cut -f1)/$(du -b text5.txt | cut -f1)\" | bc; else echo \"FAILED\"; fi");
	return 0;
}
