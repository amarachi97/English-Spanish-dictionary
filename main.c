
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//THE STRUCTURE FOR THE HASHTABLE
struct table{
	char* english;
	char* spanish;

};

struct table hash[8000];

//THE STRUCTURE I AM USING FOR THE BINARY TREE
typedef struct node{
	char* english;
	char* spanish;
	struct node* left;
	struct node* right;
}node;
node* tree=NULL;

//THE STRUCTURE I AM USING TO STORE THE TEXT FILE 
struct dict{
	char text[150];
};
struct dict entry[8000];

int notHashed =0;
int arrayProbe[7993];
int totalNodes =0;



void tableAnalysis(int lineCount){
	int i,j;
	int count;
	int totalProbes =0;
	int max = arrayProbe[0];
	for(i=0; i<lineCount; i++){
		if(max < arrayProbe[i])
			max = arrayProbe[i];
	}

	 for (i=0; i<lineCount; i++)
                        totalProbes = totalProbes+arrayProbe[i];


	printf("Probes | keys\n");
	for (i=0; i<=max;i++ ){
		count =0;
		for(j=0; j<lineCount; j++){
			if(arrayProbe[j] == i)
				count +=1;
		}
		printf("%6d | %4d\n", i,count );
		printf("-------------\n");
	}
	printf("Hash Table Analysis:\n");       
        printf("total NOT hashed: %d out of %d items\n", notHashed, lineCount);
        printf("total Probes: %d out of %d items\n", totalProbes, lineCount);
        printf("max_run of probes: %d\n", max);
	printf("average number of probes: %f\n\n", (double)totalProbes/lineCount);
		
}

void SearchbadHash(char* input1, int wordCount){
/*
*THIS EARCH FUNCTION IS FOR THE LINEAR PROBING
*/
	int code;
        int stringHash ;
	int i =0;

        int probes=1;

        stringHash = badHash(input1, wordCount);

        int h = stringHash % wordCount;
        code = (h + i) % wordCount;

        while(hash[code].english != NULL){
                if(strcmp(hash[code].english,input1) != 0){
                        probes +=1;
                        i +=3;
                        code = (h + i) % wordCount;
                }

                else{

                        printf("spanish: %s\n", hash[code].spanish);
                        printf("%d probes\n\n", probes);
                        return;
                }
        }
        printf("not found\n");
        printf("%d probes\n\n", probes);

}
void searchHash(char* input1, int wordCount){
/*
* THIS SEARCH FUNCTION IS FOR THE QUADRATIC PROBING
*/

	int code;
	int stringHash ;
	int i =0;
	
	int probes=1;
	
	stringHash = hashU(input1, wordCount);

        int h = stringHash % wordCount;
        code = (int)(h + (i*i*0.5) + (0.5*i)) % wordCount;
	
        while(hash[code].english != NULL){
		if(strcmp(hash[code].english,input1) != 0){
                	probes +=1;
                	i +=1;
                	code = (int)(h + (0.5*i*i) + (0.5*i)) % wordCount;
		}
		
		else{
			
			printf("spanish: %s\n", hash[code].spanish);
			printf("%d probes\n\n", probes);
			return;
		}
        }
	printf("not found\n");
	printf("%d probes\n\n", probes);



}


int quadraticProbe (int stringHash, int wordCount, int lineCount){
/*
*QUADRATIC PROBING IS FOR MY GOOD HASH TABLE
*/

	int code;
	
	int i=0;
	int probes = 1;

	int h = stringHash % wordCount;
	code = (int)(h + (i*i*0.5)+(0.5*i)) % wordCount;
        while(hash[code].english != 0){
		probes +=1;
                i +=1;
                code = (int)(h + (i*i*0.5)+(i*0.5)) % wordCount;
        }
	

	arrayProbe[lineCount] = probes;
	return code;

}

int linearProbe(int stringHash, int wordCount, int lineCount){
/*
*LINEAR PROBING IS FOR MY BAD HASH TABLE
*/

        int code;
        int i =0;
        int probes = 1;
        int h = stringHash % wordCount;
        code = (h + i) % wordCount;
        while(hash[code].english != 0){
		if(probes == (wordCount +1)){
			printf("not hashed\n");
			notHashed +=1;
			break;
		}

		if(code != (wordCount -1)){	//check if its not the end of the table
                	probes +=1;
       			i +=3;
                        code = (h + i) % wordCount;
         	
			//code = (code +3)%wordCount;
		}
		else
			code =0;
                
        }

        arrayProbe[lineCount] = probes;
        return code;
}


void insertHash(int stringHash, char* english, char* spanish, int wordCount, int option, int lineCount){
	int code;
	int i =0;
	int h = stringHash % wordCount;
		
	
	if(option == 3)
		code = quadraticProbe(stringHash, wordCount, lineCount);
	if (option ==4 )
		code = linearProbe(stringHash, wordCount, lineCount);

	hash[code].english = strdup(english);
        hash[code].spanish = strdup(spanish);

}


int hashU(char *v, int M){
/*
* THIS WAS GOTTEN FROM THE SLIDES ON HASHING IN CLASS
*/

	int h, a = 31415, b = 27183;
	for (h = 0; *v != '\0'; v++, a = a*b % (M-1)){
		h = (a*h + *v) % M;
		
	}
	return h;
 }

int badHash(char *v){
/*SOURCE: http://cseweb.ucsd.edu/~kube/cls/100/Lectures/lec16/lec16-13.html*/

	int h;
	for(h=0; *v != '\0'; v++)
		h += *v;
	return h;
}



int searchTree (struct node* tree, char* input, int nodeCount){
	if(tree == NULL)
		printf("not found\n");
	else if(strcmp(input,tree->english)==0){
		nodeCount +=1;
		printf("spanish: %s\n", tree->spanish);
	}
	else if(strcmp(input, tree->english)<0){
		nodeCount+=1;
		nodeCount = searchTree(tree->left, input, nodeCount);
	}
	else{
		nodeCount +=1;
		nodeCount =searchTree(tree->right, input, nodeCount);
	}

	return nodeCount;
}

struct node* getnewNode(char* english, char* spanish){

	struct node* temp = (struct node*) malloc (sizeof(struct node));
	
	temp -> english = strdup(english);
	temp -> spanish = strdup(spanish);
	temp -> left = NULL;
	temp -> right = NULL;
	return temp;
}
struct node* insertTree (struct node* tree, char* english, char* spanish){

	if(tree == NULL){
		totalNodes +=1;
		tree = getnewNode(english, spanish);

	}

	else if (strcmp(english,tree->english)<0){
		totalNodes +=1;
		tree->left = insertTree(tree->left, english, spanish);

	}

	else{
		totalNodes +=1;
		tree->right = insertTree(tree->right, english, spanish);
		
	}
}

void getbinaryIndices(int count){
	int i=0; char temp[150];
	char* english;
	char* spanish;
	int random = rand()%count;
	char input[100];

	while (i != count-11){		//subtracting the hashtags
		if ((entry[random].text != 0) && (entry[random].text[0] != '#' )){
			
 			strcpy(temp,entry[random].text);
			english= strtok(temp," \t");
        		spanish = strtok(NULL, "\n");	

			tree = insertTree(tree, english, spanish);

			entry[random].text[0] = '#';
			i +=1;
		}
		random = rand()%count;
		
	}	
	
}

int main (){

	FILE *fp;
	char input[150] = "";
	char text [150];
	char* english;
	char* spanish;
	int Wordcount = 0;  //count of words in the file
	int option;
	tree = (struct node*) malloc (sizeof(struct node));
	tree = NULL;
	int stringHash=0;
	int nodeCount;


	printf("\nPress -1 to stop\n1. Random Binary Tree\n2. Non-Random Binary Tree\n3. Good HashTable\n4. Bad HashTable\n\nEnter option: ");
	scanf("%d", &option);
	
	if(option == 1){
		fp = fopen("Spanish.txt", "r");
		while ( fgets(entry[Wordcount].text, 150, fp)!= NULL)
			Wordcount +=1;		
		getbinaryIndices(Wordcount);
		printf("BST: total cost: %d\n", totalNodes);
		Wordcount -=11;
		printf("BST: average cost: %f\n\n", (double)totalNodes/Wordcount);	//subtracting the hashtags
		//SEARCH
		printf("Enter english word: ");
		scanf("%s", &input);

		while (strcmp(input, "-1") != 0){
			nodeCount = 0;
			nodeCount = searchTree(tree, input, nodeCount);
			printf("%d BTS nodes\n\n", nodeCount);
			printf("Enter english word: ");
			scanf("%s", &input);
		}		
	}

	free(tree);
	tree = NULL;

	if(option == 2){
		fp = fopen("Spanish.txt", "r"); 
		while (fgets(text, 150, fp)!= NULL){
			if(text[0] !=  '#'){	
				Wordcount +=1;
				english= strtok(text," \t");
                        	spanish = strtok(NULL, "\n");
				tree = insertTree(tree, english, spanish);
			}
		}
		printf("BST: total cost: %d\n", totalNodes);
                
                printf("BST: average cost: %f\n\n", (double)totalNodes/Wordcount);      //subtracting the hashtags
		
		//SEARCH		
		printf("Enter english word: ");
                scanf("%s", &input);

                while (strcmp(input, "-1") != 0){
                        nodeCount = 0;
                        nodeCount = searchTree(tree, input, nodeCount);
                        printf("%d BTS nodes\n\n", nodeCount);
                        printf("Enter english word: ");
                        scanf("%s", &input);
                }
		
	}

	if (option == 3){
		/*assumed table size is 8000 therefore the wordCount (i.e M) 
		 *is the prime number closest to that, to generate lesser collisions
		 */
		int lineCount =-1;

		Wordcount = 7993;
		fp = fopen("Spanish.txt", "r");
		while (fgets(text, 150, fp)!= NULL){
			if(text[0] !=  '#'){
				english= strtok(text," \t");
                                spanish = strtok(NULL, "\n");
				stringHash = hashU(english, Wordcount);
				lineCount +=1;
				insertHash(stringHash, english, spanish, Wordcount,option, lineCount);
				
			}
		}


		tableAnalysis(lineCount);
		//SEARCH

		char input1[1000];
		 printf("Enter english word: ");
                scanf("%s", &input1);
		
		while(strcmp(input1, "-1")!=0){
                	searchHash(input1, Wordcount);
			printf("Enter english word: ");
                	scanf("%s", &input1);

		}		

	}

	if(option == 4){
		 /*assumed table size is 8000 therefore the wordCount (i.e M)
                  *is also 8000 because a number that has a power of 2
		  *will generate more collisions
                  */

		Wordcount = 8000;
		int lineCount =-1;
                fp = fopen("Spanish.txt", "r");
                while (fgets(text, 150, fp)!= NULL){
                        if(text[0] !=  '#'){
                                english= strtok(text," \t");                
                                spanish = strtok(NULL, "\n");
                                stringHash = badHash(english);
				lineCount +=1;
                                insertHash(stringHash, english, spanish, Wordcount,option, lineCount);
                                
                        }
                }


                //SEARCH
		 tableAnalysis(lineCount);
                char input1[1000];
                 printf("Enter english word: ");
                scanf("%s", &input1);

                while(strcmp(input1, "-1")!=0){
                        SearchbadHash(input1, Wordcount);
                        printf("Enter english word: ");
                        scanf("%s", &input1);

                }

	}

	
	free(tree);
	fclose(fp);

}
