#include<stdio.h>
#include<stdlib.h>

// 필요한 헤더파일 추가
typedef struct Node { // (typedef를 사용하여) listNode 구조체 생성
	int key;
	struct Node* link;
} listNode;

typedef struct Head { // (typedef를 사용하여) headNode 구조체 생성
	struct Node* first;
}headNode;


// 함수 리스트
headNode* initialize(headNode* h);

int freeList(headNode* h); // 메모리 해제

int insertFirst(headNode* h, int key); // list key에 대한 노드 추가
int insertNode(headNode* h, int key); // 노드 삽입
int insertLast(headNode* h, int key); // key에 대한 노드 추가

int deleteFirst(headNode* h);  // 노드 삭제
int deleteNode(headNode* h, int key); // key에 대한 노드 삭제
int deleteLast(headNode* h); // 마지막 노드 삭제

int invertList(headNode* h); // list의 link를 역순으로 재배치
void printList(headNode* h); // 출력

int main()
{
	char command; 
	int key; 
	headNode* headnode=NULL;

	do{
        printf("[----- [노관범]  [2020039102] -----]\n");

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
		scanf(" %c", &command); // command 받기

		switch(command) {
		case 'z': case 'Z': // z 또는 Z 일 경우
			headnode = initialize(headnode);
			break;
		case 'p': case 'P': //  p 또는 P 일 경우
			printList(headnode);
			break;
		case 'i': case 'I': // i 또는 I 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			insertNode(headnode, key);
			break;
		case 'd': case 'D': //  d 또는 D 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 받기
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // n 또는 N 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			insertLast(headnode, key);
			break;
		case 'e': case 'E':// e 또는 E 일 경우
			deleteLast(headnode);
			break;
		case 'f': case 'F': //  f 또는 F 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 받기
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //  t 또는 T 일 경우
			deleteFirst(headnode);
			break;
		case 'r': case 'R': //  r 또는 R 일 경우
			invertList(headnode);
			break;
		case 'q': case 'Q': //  q 또는 Q 일 경우
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 경고문 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); // q 또는 Q 를 입력할 때 까지 진행
	return 1;
}

headNode* initialize(headNode* h) {

	// headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
	if(h != NULL) 
		freeList(h); // 해제
 
	// headNode에 대한 메모리를 할당하여 리턴
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode type으로 주소 받기
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	// h와 연결된 listNode 메모리 해제
	// headNode도 해제되어야 함
	listNode* p = h->first; // p를 만들고 h가 가리키는 주소에 p 삽임
	listNode* prev = NULL;

	while(p != NULL) { // p가 NULL이 아니면
		prev = p; // prev에 p 주소 삽임
		p = p->link; // link 주소 삽입
		free(prev); // 메모리 해제
	}
	free(h); // 메모리 해제
	return 0;
}

int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode type으로 주소 받기
	node->key = key; // node 가리키는 key에 key 삽입
	node->link = NULL;

	if (h->first == NULL) // NULL일 경우
	{
		h->first = node; // h가 가리키는 firts에 node 주소 삽입
		return 0;
	}

	listNode* n = h->first; // h가 가리키는 first가 가리키는 곳에 n 주소 삽입
	listNode* trail = h->first; // h가 가리키는 first가 가리키는 곳에 trail 주소 삽입

	while(n != NULL) {
		if(n->key >= key) {
			
			if(n == h->first) { // 인지 검사 
				h->first = node; // h가 가리키는 first에 node 주소 삽입
				node->link = n; // node가 가리키는 link에 n 주소 삽입
			} else {  
				node->link = n; // node가 가리키는 link의 n이 있는 주소 삽입
				trail->link = node; // trail가 가리키는 link에 node의 주소 삽입
			}
			return 0;
		}
		trail = n; // trail에 n 들어있는 주소 삽입
		n = n->link; // n에 n이 가리키는 곳의 link에 들어있는 주소 삽입
	}
	trail->link = node; // trail이 가리키는 link node의 주소 삽입
	return 0; 
}

// list에 key에 대한 노드하나를 추가
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode type으로 주소 받기
	node->key = key;
	node->link = NULL;

	if (h->first == NULL) //  NULL일 경우
	{
		h->first = node; // h가 가리키는 first에 node 가리키는 주소 삽입
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) { // NULL이 아닐 경우
		n = n->link;
	}
	n->link = node; // n이 가리키는 link 가리키는 주소에 n 삽입
	return 0;
}

int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode type으로 주소 받기
	node->key = key;

	node->link = h->first; // node가 가리키는 key에 key 삽입
	h->first = node; // h-> first에 node 주소 삽입

	return 0;
}

// list에서 key에 대한 노드 삭제
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // NULL일 경우
	{
		printf("nothing to delete.\n"); // 삭제할 내용이 없다고 경고
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;
 
	while(n != NULL) {
		if(n->key == key) {
		
			if(n == h->first) { // 인지 검사 
				h->first = n->link; // h-> first -> n 주소 삽입
			} else { 
				trail->link = n->link; // trail-> link에 n-> link의 주소 삽입
			}
			free(n); // 삭제
			return 0;
		}
		trail = n;
		n = n->link;
	} 
	printf("cannot find the node for key = %d\n", key); // 위치없음 경고문 출력
	return 0;

}

int deleteLast(headNode* h) {

	if (h->first == NULL) //  NULL일 경우
	{
		printf("nothing to delete.\n"); // 경고문 출력
		return 0;
	}

	listNode* n = h->first;
	// 메모리의 Stack 영역에 n을 만들고,
	// h가 가리키는 곳의 first가 가리키는 곳의 주소를 n에 넣는다.
	listNode* trail = NULL;

	if(n->link == NULL) { // NULL일 경우
		h->first = NULL; // h-> first에 NULL 삽입
		free(n); // 삭제
		return 0;
	} 
	while(n->link != NULL) { //  NULL이 아닐 경우
		trail = n; // trail에 n 들은 주소 삽입
		n = n->link; // n->n이 가리킨 link에 주소 삽입
	}
	trail->link = NULL; // n 삭제, 이전 노드 링크 NULL 
	free(n); // 노드 삭제

	return 0;
}

 // 첫번째 노드 삭제
int deleteFirst(headNode* h) {

	if (h->first == NULL) // NULL일 경우
	{
		printf("nothing to delete.\n"); // 경고문 출력
		return 0;
	}
	listNode* n = h->first; // h-> first 가리키는 주소 n에 삽입
	h->first = n->link; // h-> first -> n 주소 삽입
	free(n); // 삭제

	return 0;
}

 
int invertList(headNode* h) {


	if(h->first == NULL) { // NULL일 경우
		printf("nothing to invert...\n"); // 재배치 경고문 출력
		return 0;
	}

	listNode *n = h->first;
	// 메모리의 Stack 영역에 n을 만들고,
	// h가 가리키는 곳의 first가 가리키는 곳의 주소를 n에 넣는다.
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){ // NULL이 아닐 경우
		trail = middle; // trail에 middle 안의 주소 삽입
		middle = n; // middle에 n 안의 주소 삽입
		n = n->link; // n에 n-> link 든 주소 삽입
		middle->link = trail; // middle -> link에 trail 안 주소 삽입
	}

	h->first = middle; // h-> first에 middle 안 주소 삽입
	return 0;
}

void printList(headNode* h) { // 출력
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // NULL일 경우
		printf("Nothing to print....\n"); // 경고문 출력
		return;
	}

	p = h->first; // p의 h-> first 안 주소 삽입

	while(p != NULL) { // NULL이 아닐 경우
		printf("[ [%d]=%d ] ", i, p->key); // p 가리키는 key 출력
		p = p->link; // p의 p-> link 안 주소 삽입
		i++; // i 1씩 증가
	}

	printf("  items = %d\n", i); // 노드 출력
}