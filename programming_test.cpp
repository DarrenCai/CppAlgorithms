
//
// You have 2 hours to complete the test.
//
// Attempt all questions and place your answers directly after each question
// Marks are shown for each question. Questions do not carry equal marks.
// 
// Write code or comments where appropriate, preferably code.
//
// Do not collaborate or use books, the internet or other external sources. 
// 
// Where appropriate you can assume some standard routines already exist
// e.g. sort, binary search etc.

// Enter your name here:  DarrenCai
// Enter the date here (dd/mm/yyyy):  27/09/2019


//------------------------------------------------------------------------------
// 1.
//
// The nth 'Factorial' F(n) for positive integers n is defined by:
//  
// F(0) = 1
// F(n) = 1*2*3*...*(n-1)*n
//
// So:
//    F(2) = 1*2 = 2
//    F(3) = 1*2*3 = 6
//    etc.

int factorial(int n);

// (1a) Write an iterative (non-recursive) function to compute F(n) [3 marks]
// (1b) Write a recursive function to compute F(n)                  [3 marks]
// (1c) Which implementation do you expect to be faster and why?
//      Give at least 3 reasons.                                    [4 marks]

int factorial1a(int n) {
	int f = 1;
	for (int i=2; i<=n; ++n) f *= i;
	return f;
}

int factorial1b(int n) {
	if (n==1) return 1;
	return n*factorial1b(n-1);
}

//1a计算更快  原因如下：
//1、递归运算在进入下次调用前需要保存当前程序的调用位置，等下次调用完全计算出结果后再回到这个位置算出当前结果，返回这个结果
// 而当前运算如果不是初次计算，则又要回到上层调用程序的调用位置继续运算，如此类推，知道回到初次运算得到最终结果才结束
//2、递归运算还要不断保存当前步骤的运算结果供上层调用进一步运算，而直接循环迭代运算是直接更新计算结果
//3、递归调用还有其它额外的堆栈开销


//------------------------------------------------------------------------------
// 2.  [10 marks]
//
// Implement a function reverseAfter() to reverse the elements in a linked list
// from the first occurrence of a given value. 
// e.g. given the input A B C D E F and the value D return the list A B C F E D
// You should do this inplace without creating new nodes. 
// Assume the list is null terminated.

struct Node
{
	struct Node* next;
	int val;
};

void reverseAfter( struct Node* head, int val );

void reverseAfter(struct Node* head, int val) {
	Node* pre = head;
	while (pre->next->val != val) pre = pre->next;
	Node* curr = pre->next;
	Node* next = curr->next;
	while (next != NULL) {
		Node* t = next->next;
		next->next = curr;
		curr = next;
		next = t;
	}
	pre->next->next = NULL;
	pre->next = curr;
}


//------------------------------------------------------------------------------
// 3. 
//
// Explain the differences between buffer1, buffer2 and buffer3 in the
// example code below. Consider:
// i.  Scope & Lifetime							[4 marks]
// ii. Performance & use of system resources	[6 marks]

char buffer1[512];

void func1()
{
	char buffer2[1024];
	//...
}

void func2()
{
	char* buffer3 = static_cast<char*> ( malloc(2048) );
	//...
}

// buffer1是程序的全局变量（数组），占用512bytes内存，直到程序所在进程结束时才会释放
// buffer2是函数func1内的临时变量（数组），func1函数被调用时占据1024bytes的内存，func1执行完毕时自动释放
// buffer3是函数func2内的临时变量，func2函数被调用时开辟2048bytes的堆内存，func2执行完毕时不会自动释放，需要手动销毁（free）


//------------------------------------------------------------------------------
// 4. 
//
// Choose any platform you want and describe what happens at machine level in the
// execution of the code below when func() is called.		[8 marks]
// What changes if foo is inlined?							[2 marks]

int foo( int a, int* b)
{
	return a + *b;
}

extern int x;

void func()
{
	int y = 7;
	int r;
	r = foo( x, &y );
	printf("%d\n", r);
}	


//------------------------------------------------------------------------------	
// 5. [15 marks]
//
// You are implementing simple 'waypoint' following for an AI hover drone 
// in a 3D environment. The drone will consider a destination waypoint 
// acceptable if it is both:
//    i. Less than 10 units away.
//    ii. Inside a 60 degree cone centered around the drone's 'forward' vector.
//
// Implement the function testWayPoint() shown below. If the waypoint is not
// acceptable the method should return REJECTED, otherwise it should return the
// side that the waypoint is on.  This is defined with respect to the drone's
// forward vector and the world up vector (you may choose either 'handedness').

//----

// Assume the following functions and structures are defined elsewhere
// DO NOT IMPLEMENT

// Add v and w, putting the result in sum : sum = v + w
void add(const Vector3& v, const Vector3& w, Vector3& sum);

// Subtract w from v, putting the result in diff: diff = v - w
void subtract(const Vector3& v, const Vector3& w, Vector3& diff);

// Compute dot product of Vector3 v and w
float dot(const Vector3& v, const Vector3& w);

// Compute v X w (cross product): crossOut = v X w
void cross(const Vector3& v, const Vector3& w, Vector3& crossOut);

// Normalize the Vector3 v to unit length
void normalize(Vector3& v);

// Compute length of Vector3
float length(const Vector3& v);

enum Direction 
{
	REJECTED = 0,
	RIGHT,
	LEFT
};

//----

// This is the function you must implement:
Direction testWayPoint(const Vector3& dronePosition, const Vector3& droneForward, 
					   const Vector3& targetWaypoint, const Vector3& worldUp );

Direction testWayPoint(const Vector3& dronePosition, const Vector3& droneForward, 
					   const Vector3& targetWaypoint, const Vector3& worldUp ) {
	Vector3 dif;
	subtract(dronePosition, targetWaypoint, dif);
	if (length(dif) >= 10 || dot(dif, droneForward) <= .5) return REJECTED;
	Vector3 crossOut;
	cross(worldUp, droneForward, crossOut);
	return dot(crossOut, dif) > 0 ? LEFT : RIGHT;
}


//------------------------------------------------------------------------------	
// 6. [10 marks]
//
// Identify as many bugs and assumptions as you can in the following code.
// NOTE that there is/are (at least):
// 1 major algorithmic assumption
// 2 portability issues
// 1 syntax error

// Function to copy 'nBytes' of data from src to dst.
void myMemcpy(char* dst, const char* src, int nBytes)
{
	// Try to be fast and copy a word at a time instead of byte by byte
	int* wordDst = (int*)dst;
	int* wordSrc = (int*)src;
	int numWords = nBytes >> 2;
	for (int i=0; i < numWords; i++)
	{
		*wordDst++ = *wordSrc++;
	}

	int numRemaining = nBytes - (numWords << 2);
	dst = (char*)wordDst; // char* dst1 = (char*)wordDst;
	src = (char*)wordSrc; // char* src1 = (char*)wordSrc;
	for (int i=0 ; i <= numRemaining; i++);  // i<numRemaining
	{
		*dst++ = *src++;	// *dst1++ = *src1++;
	}
	// *dist1 = '\0';
}


//------------------------------------------------------------------------------	
// 7.
//
// (7a) 
// An object foo is written to a new file on platform 1 as:
write( file, &myFoo, sizeof(struct foo) );

// ...and then read on platform 2 using:
read(file, &myFoo, filesize(file) );

// The foo object has the following definition:  
struct foo
{
	char  a;
	int   b; 
	long  c;
	char* d;	// 问题在这里
};


// What kind of issues might arise when loading foo on platform 2? [6 marks]


// (7b)
// You are writing a unit test to confirm the correctness of a function which
// takes 3 float values as arguments. You decide to stress test it by testing
// 1000000 'random' inputs.
// You find that the function will fail, but very rarely, so you include code
// to print out all failure cases, hoping to grab a simple repro case which you
// can debug into.
// Note: All code here is run in a single-threaded environment.

//...
// Some code sets a,b,c
//...
if ( testPasses(a,b,c) )
{
	printf("Pass\n");
}
else // someFunc fails, print the values so we can reproduce
{
	printf("Fail: %f %f %f\n", a, b, c);
}

// where testPasses has the following signature and executes deterministically 
// with no side effects:
bool testPasses(float f1, float f2, float f3);

void testRepro()
{
	float a = // fill in from value printed by above code
		float b = // fill in from value printed by above code
		float c = // fill in from value printed by above code
		bool result = testPasses(a,b,c);
};

// Surprisingly, when you type in the 3 values printed out in testRepro()
// the test does not fail!
// Modify the original code and test bed to reproduce the problem reliably.  [4 marks]


//------------------------------------------------------------------------------
// 8.
//
// Suppose that you have  an array of shorts which corresponds to the vertex ids 
// of a set of T triangles. The shorts would be interpreted 3 at a time, so the 
// array

// 0,2,7,1,3,5,6,2,0

// would represent 3 triangles with vertex ids : (0,2,7), (1,3,5) and (6,2,0) 
// There are 9 edges implicit in the data 
// Triangle 1 : (0,2), (2,7), (7,0) 
// Triangle 2 : (1,3), (3,5), (5,1) 
// Triangle 3 : (6,2), (2,0), (0,6)

// Write a method to find all connectivity information between all triangles. 
// Two triangles are considered connected if they share an edge.  
// For example, triangle 1 and triangle 3 are connected because triangle 1 has
// edge (0,2) and triangle 3 has opposite edge (2,0).

// Your method should fill an output array of size 3T with the corresponding 
// indices of the opposite edge. You may assume that every edge has at most one 
// match. Edges with no opposite are flagged with -1.

// The output for the example above should be 
// 7, -1, -1, -1, -1, -1, -1, 0, -1 

// 8(a) First write the method using a brute force implementation (may be 
// very slow for large T)                                         [10 marks]

// 8(b) Then consider how you might preprocess the data to find 
// the edge matches more quickly for large T. Use code or
// pseudocode to illustrate your approach.                        [15 marks]

// Your method declaration should look like:
void findConnectivity(unsigned short* indexTriples, int T, int* connectivityOut);

//---------------------------------------------------------------------------------

