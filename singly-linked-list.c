#include<stdio.h>
#include<stdlib.h>

// �ʿ��� ������� �߰�
typedef struct Node { // (typedef�� ����Ͽ�) listNode ����ü ����
	int key;
	struct Node* link;
} listNode;

typedef struct Head { // (typedef�� ����Ͽ�) headNode ����ü ����
	struct Node* first;
}headNode;


// �Լ� ����Ʈ
headNode* initialize(headNode* h);

int freeList(headNode* h); // �޸� ����

int insertFirst(headNode* h, int key); // list key�� ���� ��� �߰�
int insertNode(headNode* h, int key); // ��� ����
int insertLast(headNode* h, int key); // key�� ���� ��� �߰�

int deleteFirst(headNode* h);  // ��� ����
int deleteNode(headNode* h, int key); // key�� ���� ��� ����
int deleteLast(headNode* h); // ������ ��� ����

int invertList(headNode* h); // list�� link�� �������� ���ġ
void printList(headNode* h); // ���

int main()
{
	char command; 
	int key; 
	headNode* headnode=NULL;

	do{
        printf("[----- [�����]  [2020039102] -----]\n");

		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command �ޱ�

		switch(command) {
		case 'z': case 'Z': // z �Ǵ� Z �� ���
			headnode = initialize(headnode);
			break;
		case 'p': case 'P': //  p �Ǵ� P �� ���
			printList(headnode);
			break;
		case 'i': case 'I': // i �Ǵ� I �� ���
			printf("Your Key = ");
			scanf("%d", &key); // key �� �ޱ�
			insertNode(headnode, key);
			break;
		case 'd': case 'D': //  d �Ǵ� D �� ���
			printf("Your Key = ");
			scanf("%d", &key); // key �ޱ�
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // n �Ǵ� N �� ���
			printf("Your Key = ");
			scanf("%d", &key); // key �� �ޱ�
			insertLast(headnode, key);
			break;
		case 'e': case 'E':// e �Ǵ� E �� ���
			deleteLast(headnode);
			break;
		case 'f': case 'F': //  f �Ǵ� F �� ���
			printf("Your Key = ");
			scanf("%d", &key); // key �ޱ�
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //  t �Ǵ� T �� ���
			deleteFirst(headnode);
			break;
		case 'r': case 'R': //  r �Ǵ� R �� ���
			invertList(headnode);
			break;
		case 'q': case 'Q': //  q �Ǵ� Q �� ���
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // ��� ���
			break;
		}

	}while(command != 'q' && command != 'Q'); // q �Ǵ� Q �� �Է��� �� ���� ����
	return 1;
}

headNode* initialize(headNode* h) {

	// headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ����
	if(h != NULL) 
		freeList(h); // ����
 
	// headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ����
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode type���� �ּ� �ޱ�
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	// h�� ����� listNode �޸� ����
	// headNode�� �����Ǿ�� ��
	listNode* p = h->first; // p�� ����� h�� ����Ű�� �ּҿ� p ����
	listNode* prev = NULL;

	while(p != NULL) { // p�� NULL�� �ƴϸ�
		prev = p; // prev�� p �ּ� ����
		p = p->link; // link �ּ� ����
		free(prev); // �޸� ����
	}
	free(h); // �޸� ����
	return 0;
}

int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode type���� �ּ� �ޱ�
	node->key = key; // node ����Ű�� key�� key ����
	node->link = NULL;

	if (h->first == NULL) // NULL�� ���
	{
		h->first = node; // h�� ����Ű�� firts�� node �ּ� ����
		return 0;
	}

	listNode* n = h->first; // h�� ����Ű�� first�� ����Ű�� ���� n �ּ� ����
	listNode* trail = h->first; // h�� ����Ű�� first�� ����Ű�� ���� trail �ּ� ����

	while(n != NULL) {
		if(n->key >= key) {
			
			if(n == h->first) { // ���� �˻� 
				h->first = node; // h�� ����Ű�� first�� node �ּ� ����
				node->link = n; // node�� ����Ű�� link�� n �ּ� ����
			} else {  
				node->link = n; // node�� ����Ű�� link�� n�� �ִ� �ּ� ����
				trail->link = node; // trail�� ����Ű�� link�� node�� �ּ� ����
			}
			return 0;
		}
		trail = n; // trail�� n ����ִ� �ּ� ����
		n = n->link; // n�� n�� ����Ű�� ���� link�� ����ִ� �ּ� ����
	}
	trail->link = node; // trail�� ����Ű�� link node�� �ּ� ����
	return 0; 
}

// list�� key�� ���� ����ϳ��� �߰�
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode type���� �ּ� �ޱ�
	node->key = key;
	node->link = NULL;

	if (h->first == NULL) //  NULL�� ���
	{
		h->first = node; // h�� ����Ű�� first�� node ����Ű�� �ּ� ����
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) { // NULL�� �ƴ� ���
		n = n->link;
	}
	n->link = node; // n�� ����Ű�� link ����Ű�� �ּҿ� n ����
	return 0;
}

int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode type���� �ּ� �ޱ�
	node->key = key;

	node->link = h->first; // node�� ����Ű�� key�� key ����
	h->first = node; // h-> first�� node �ּ� ����

	return 0;
}

// list���� key�� ���� ��� ����
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // NULL�� ���
	{
		printf("nothing to delete.\n"); // ������ ������ ���ٰ� ���
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;
 
	while(n != NULL) {
		if(n->key == key) {
		
			if(n == h->first) { // ���� �˻� 
				h->first = n->link; // h-> first -> n �ּ� ����
			} else { 
				trail->link = n->link; // trail-> link�� n-> link�� �ּ� ����
			}
			free(n); // ����
			return 0;
		}
		trail = n;
		n = n->link;
	} 
	printf("cannot find the node for key = %d\n", key); // ��ġ���� ��� ���
	return 0;

}

int deleteLast(headNode* h) {

	if (h->first == NULL) //  NULL�� ���
	{
		printf("nothing to delete.\n"); // ��� ���
		return 0;
	}

	listNode* n = h->first;
	// �޸��� Stack ������ n�� �����,
	// h�� ����Ű�� ���� first�� ����Ű�� ���� �ּҸ� n�� �ִ´�.
	listNode* trail = NULL;

	if(n->link == NULL) { // NULL�� ���
		h->first = NULL; // h-> first�� NULL ����
		free(n); // ����
		return 0;
	} 
	while(n->link != NULL) { //  NULL�� �ƴ� ���
		trail = n; // trail�� n ���� �ּ� ����
		n = n->link; // n->n�� ����Ų link�� �ּ� ����
	}
	trail->link = NULL; // n ����, ���� ��� ��ũ NULL 
	free(n); // ��� ����

	return 0;
}

 // ù��° ��� ����
int deleteFirst(headNode* h) {

	if (h->first == NULL) // NULL�� ���
	{
		printf("nothing to delete.\n"); // ��� ���
		return 0;
	}
	listNode* n = h->first; // h-> first ����Ű�� �ּ� n�� ����
	h->first = n->link; // h-> first -> n �ּ� ����
	free(n); // ����

	return 0;
}

 
int invertList(headNode* h) {


	if(h->first == NULL) { // NULL�� ���
		printf("nothing to invert...\n"); // ���ġ ��� ���
		return 0;
	}

	listNode *n = h->first;
	// �޸��� Stack ������ n�� �����,
	// h�� ����Ű�� ���� first�� ����Ű�� ���� �ּҸ� n�� �ִ´�.
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){ // NULL�� �ƴ� ���
		trail = middle; // trail�� middle ���� �ּ� ����
		middle = n; // middle�� n ���� �ּ� ����
		n = n->link; // n�� n-> link �� �ּ� ����
		middle->link = trail; // middle -> link�� trail �� �ּ� ����
	}

	h->first = middle; // h-> first�� middle �� �ּ� ����
	return 0;
}

void printList(headNode* h) { // ���
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // NULL�� ���
		printf("Nothing to print....\n"); // ��� ���
		return;
	}

	p = h->first; // p�� h-> first �� �ּ� ����

	while(p != NULL) { // NULL�� �ƴ� ���
		printf("[ [%d]=%d ] ", i, p->key); // p ����Ű�� key ���
		p = p->link; // p�� p-> link �� �ּ� ����
		i++; // i 1�� ����
	}

	printf("  items = %d\n", i); // ��� ���
}