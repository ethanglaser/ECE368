#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv){
	char * map = argv[1];
	char * query = argv[2];
	char * sp = malloc(100 * sizeof(char));
	char * mp = malloc(100 * sizeof(char));
	sprintf(sp, "shortestpath %s %s > bin.txt", map, query);
	sprintf(mp, "mapper %s %s > output.txt", map, query);
	system("gcc -Werror -Wall map.c map.h -o mapper -lm");
	system(sp);
	system(mp);
	system("diff bin.txt output.txt");


	/*system("time unhuffman text5.txt.huff");
	system("xxd -b test1.txt.huff > test1bin.txt");
	system("echo \"Checking Output of test1:\"");
	system("if [[ $(diff test1.txt test1.txt.huff.unhuff) == '' ]]; then echo \"scale = 10 ; $(du -b test1.txt.huff | cut -f1)/$(du -b test1.txt | cut -f1)\" | bc; else echo \"FAILED\"; fi");
	system("echo \"Checking Output 0:\"");
	system("if [[ $(diff text0.txt text0.txt.huff.unhuff) == '' ]]; then echo \"scale = 10 ; $(du -b text0.txt.huff | cut -f1)/$(du -b text0.txt | cut -f1)\" | bc; else echo \"FAILED\"; fi");*/

	return 0;
}
