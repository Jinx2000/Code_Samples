#include "reducer.h"

// create a key value node
finalKeyValueDS *createFinalKeyValueNode(char *word, int count){
	finalKeyValueDS *newNode = (finalKeyValueDS *)malloc (sizeof(finalKeyValueDS));
	strcpy(newNode -> key, word);
	newNode -> value = count;
	newNode -> next = NULL;
	return newNode;
}

// insert or update an key value
finalKeyValueDS *insertNewKeyValue(finalKeyValueDS *root, char *word, int count){
	finalKeyValueDS *tempNode = root;
	if(root == NULL)
		return createFinalKeyValueNode(word, count);
	while(tempNode -> next != NULL){
		if(strcmp(tempNode -> key, word) == 0){
			tempNode -> value += count;
			return root;
		}
		tempNode = tempNode -> next;
	}
	if(strcmp(tempNode -> key, word) == 0){
		tempNode -> value += count;
	} else{
		tempNode -> next = createFinalKeyValueNode(word, count);
	}
	return root;
}

// free the DS after usage. Call this once you are done with the writing of DS into file
void freeFinalDS(finalKeyValueDS *root) {
	if(root == NULL) return;

	finalKeyValueDS *tempNode = NULL;
	while (root != NULL){
		tempNode = root;
		root = root -> next;
		free(tempNode);
	}
}

// reduce function
void reduce(char *key) { // key = path to word.txt

	// read from key (file):
	FILE *fp;
	char buffer[256];
	// using memset to initial string, avoiding null chars:
	memset(buffer, '\0', sizeof(buffer));
	fp = fopen(key, "r");
	// check fopen():
	if (fp == NULL) {
		printf("Cannot open file, error detected");
	}
	// check fgets():
	if (fgets(buffer, sizeof(buffer), fp) == NULL) {// get the first line (word 1 1 1)
		printf("ERROR: error in fgets");
	}
	// check fclose():
	if (fclose(fp)){
		perror("fclose error");
	}

	// extract the word out of buffer:
	char word[MAXKEYSZ];
	int temp_count = 0;
	for (int i = 0; i < sizeof(buffer); i++) {
		if (buffer[i] != ' ') {
			temp_count++;
		} else { // first ' ' encountered.
			break;
		}
	}
	strncpy(word, buffer, temp_count);
	word[temp_count + 1] = '\0'; // manually added end_of_string char;

	// count the 1s in the buffer:
	int count = 0;
	for (int i = temp_count; i < sizeof(buffer); i++) {
		if (buffer[i] == '\0') { // end of buffer
			break;
		}
		if (buffer[i] == '1') { // adding 1s
			count++;
		}
	}

	// store value in DS:
	ReduceDSRoot = insertNewKeyValue(ReduceDSRoot, word, count);
}

// write the contents of the final intermediate structure
// to output/ReduceOut/Reduce_reducerID.txt
void writeFinalDS(int reducerID){

	// construct filename:
	char fileName[256] = "./output/ReduceOut/Reduce_";
	char temp[10];
	sprintf(temp, "%d.txt", reducerID);
	strncat(fileName, temp, sizeof(temp)); // fileName constructed.

	// construct each line of the file from DS,
	// then combine them in master string:
	// initial string:
	char thingsInFile[2048];
	char lineInFile[128];
	char count[10];
	memset(thingsInFile, '\0', sizeof(thingsInFile));
	memset(lineInFile, '\0', sizeof(lineInFile));
	memset(count, '\0', sizeof(count));
	finalKeyValueDS *ptr = ReduceDSRoot;
	while (ptr != NULL) {
		// construct sub string of each line:
		strncpy(lineInFile, ptr->key, sizeof(ptr->key));
		sprintf(count, " %d\n", ptr->value);
		strncat(lineInFile, count, sizeof(count));
		// save to the master string:
		strncat(thingsInFile, lineInFile, sizeof(lineInFile));
		ptr = ptr->next;
	}

	// find the efficient # of chars in the string,
	// and write only them:
	int efficientIndex = 0;
	for (int i = 0; i < sizeof(thingsInFile); i++) {
		// if reached the end of efficient chars:
		if (thingsInFile[i] == '\0') {
			break;
		}
		efficientIndex++;
	}

	// write master string to the file:
	FILE *fp;
	fp = fopen(fileName, "w");
	// check fopen():
	if (fp == NULL) {
		printf("Cannot open file, error detected");
	}
	int writeChecker = fwrite(thingsInFile, efficientIndex, 1, fp);
	// check fwrite():
	if (writeChecker != 1){
		printf("ERROR: numWritten not expected.");
	}
	// check fclose():
	if (fclose(fp)){
		perror("fclose error");
	}

	// free DS:
	freeFinalDS(ReduceDSRoot);
}

int main(int argc, char *argv[]) {

	if(argc < 2){
		printf("Less number of arguments.\n");
		printf("./reducer reducerID");
	}

	// ###### DO NOT REMOVE ######
	// initialize 
	int reducerID = strtol(argv[1], NULL, 10);

    //Print statement for reducer, comment this for final submission
    //printf("Reducer id : %d \n",reducerID);

	// ###### DO NOT REMOVE ######
	// master will continuously send the word.txt files
	// alloted to the reducer
	char key[MAXKEYSZ];
	while(getInterData(key, reducerID))
		reduce(key);

	// You may write this logic. You can somehow store the
	// <key, value> count and write to Reduce_reducerID.txt file
	// So you may delete this function and add your logic
	writeFinalDS(reducerID);

	return 0;
}
