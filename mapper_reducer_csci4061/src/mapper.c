#include "mapper.h"

// combined value list corresponding to a word <1,1,1,1....>
valueList *createNewValueListNode(char *value){
	valueList *newNode = (valueList *)malloc (sizeof(valueList));
	strcpy(newNode -> value, value);
	newNode -> next = NULL;
	return newNode;
}

// insert new count to value list
valueList *insertNewValueToList(valueList *root, char *count){
	valueList *tempNode = root;
	if(root == NULL)
		return createNewValueListNode(count);
	while(tempNode -> next != NULL)
		tempNode = tempNode -> next;
	tempNode -> next = createNewValueListNode(count);
	return root;
}

// free value list
void freeValueList(valueList *root) {
	if(root == NULL) return;

	valueList *tempNode = NULL;
	while (root != NULL){
		tempNode = root;
		root = root -> next;
		free(tempNode);
	}
}

// create <word, value list>
intermediateDS *createNewInterDSNode(char *word, char *count){
	intermediateDS *newNode = (intermediateDS *)malloc (sizeof(intermediateDS));
	strcpy(newNode -> key, word);
	newNode -> value = NULL;
	newNode -> value = insertNewValueToList(newNode -> value, count);
	newNode -> next = NULL;
	return newNode;
}

// insert or update a <word, value> to intermediate DS
intermediateDS *insertPairToInterDS(intermediateDS *root, char *word, char *count){
	intermediateDS *tempNode = root;
	if(root == NULL)
		return createNewInterDSNode(word, count);
	while(tempNode -> next != NULL) {
		if(strcmp(tempNode -> key, word) == 0){
			tempNode -> value = insertNewValueToList(tempNode -> value, count);
			return root;
		}
		tempNode = tempNode -> next;
		
	}
	if(strcmp(tempNode -> key, word) == 0){
		tempNode -> value = insertNewValueToList(tempNode -> value, count);
	} else {
		tempNode -> next = createNewInterDSNode(word, count);
	}
	return root;
}

// free the DS after usage. Call this once you are done with the writing of DS into file
void freeInterDS(intermediateDS *root) {
	if(root == NULL) return;

	intermediateDS *tempNode = NULL;
	while (root != NULL){
		tempNode = root;
		root = root -> next;
		freeValueList(tempNode -> value);
		free(tempNode);
	}
}

// emit the <key, value> into intermediate DS 
void emit(char *key, char *value) { // how to pass in DS?
	bigListRoot = insertPairToInterDS(bigListRoot, key, value);
}

// map function
void map(char *chunkData){
	int i = 0;
    char *buffer;
    while ((buffer = getWord(chunkData, &i)) != NULL){
		char *temp_value = " 1";
		emit(buffer, temp_value); // pass the single word & i into emit. (what is i tho???)
    }
	// you can use getWord to retrieve words from the 
	// chunkData one by one. Example usage in utils.h
}

// write intermediate data to separate word.txt files
// Each file will have only one line : word 1 1 1 1 1 ...
void writeIntermediateDS() {
	// for each word in the DS:
	intermediateDS* ptr = bigListRoot;
	while (ptr!= NULL) {
		// create the output string:
		char word[256];
		// using memset to initial string, avoiding null chars:
		memset(word, '\0', sizeof(word));
		strcpy(word, ptr->key); //max 256
		valueList *value = ptr->value;
		while (value != NULL) { // loop through value list
			char temp[10] = " 1";
			strncat(word, temp, 2);
			value = value->next;
		}

		// create file name: (.txt)
		// initialize directory:
		char fileName[256] = "./output/MapOut/Map_";
		char temp[256];
		// go to different map_id directory:
		sprintf(temp, "%d/", mapperID);
		// use strncat to add temp onto fileName:
		strncat(fileName, temp, sizeof(temp));
		sprintf(temp, "%s.txt", ptr->key);
		strncat(fileName, temp, sizeof(temp));

		// find the efficient # of chars in the string,
		// and write only them:
		int efficientIndex = 0;
		for (int i = 0; i < sizeof(word); i++) {
			// if reached the end of efficient chars:
			if (word[i] == '\0') {
				break;
			}
			efficientIndex++;
		}

		// write to file:
		FILE *fp;
		fp = fopen(fileName, "w");
		// check fopen():
		if (fp == NULL) {
			printf("Cannot open file, error detected");
		}
		// write only the first [efficientIndex] chars into file:
		int writeChecker = fwrite(word, efficientIndex, 1, fp);
		// check fwrite():
		if (writeChecker != 1){
			printf("ERROR in fwrite");
		}
		if (fclose(fp)){
			perror("fclose error");
		}
		// go to next node:
		ptr = ptr->next;
	}
	// free:
	freeInterDS(bigListRoot);
}

int main(int argc, char *argv[]) {
	
	if (argc < 2) {
		printf("Less number of arguments.\n");
		printf("./mapper mapperID\n");
		exit(0);
	}
	// ###### DO NOT REMOVE ######
	mapperID = strtol(argv[1], NULL, 10);

    //Print statement for mapper, comment this for final submission
    //printf("Mapper id : %d \n",mapperID);

	// ###### DO NOT REMOVE ######
	// create folder specifically for this mapper in output/MapOut
	// mapOutDir has the path to the folder where the outputs of 
	// this mapper should be stored
	mapOutDir = createMapDir(mapperID);

	// ###### DO NOT REMOVE ######
	while(1) {
		// create an array of chunkSize=1024B and intialize all 
		// elements with '\0'
		char chunkData[chunkSize + 1]; // +1 for '\0'
		memset(chunkData, '\0', chunkSize + 1);

		char *retChunk = getChunkData(mapperID);
		if(retChunk == NULL) {
			break;
		}

		strcpy(chunkData, retChunk);
		free(retChunk);

		map(chunkData);
	}
	// ###### DO NOT REMOVE ######
	writeIntermediateDS();

    free(mapOutDir);
	return 0;
}
