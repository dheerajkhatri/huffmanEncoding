#include <bits/stdc++.h>
#define ALPHASIZE 256
#define MAXHEIGHT 100
using namespace std;

struct node{
	int frequency;
	char ch;
	node *left,*right;
	node(int occur,char cur):frequency(occur),ch(cur),left(NULL),right(NULL){};
};

struct cmp{
	bool operator()(struct node *a,struct node *b){
		return a->frequency>b->frequency;
	}
};

node* getNode(int freq,char ch){
	struct node* newnode = new node(freq,ch);
	return newnode;
}

vector<int> getFreq(string& str){
    int nonAscii = 0;
	vector<int>freq(ALPHASIZE,0);
	for(unsigned int i=0;i<str.length();i++){
	    if(str[i]=='\n')continue;
	    if(int(str[i])>255 || int(str[i])<0){
            nonAscii++;
            continue;
	    }
		freq[int(str[i])]+=1;
	}
	cout<<"Total of "<<nonAscii<<" non Ascii character found in file and ignored"<<endl;
	cout<<"Press Enter to continue"<<endl;
	fflush(stdin);
	getchar();
	return freq;
}

string getData(){
	string fileName;
	cout<<"Enter the fileName which you want to compress"<<endl;
	cin>>fileName;

	ifstream fileReader(fileName);
	string content( (std::istreambuf_iterator<char>(fileReader) ),(std::istreambuf_iterator<char>()) );
	return content;
}

void getCodeUtil(struct node* root, vector<int>& code, int cur, ofstream& out){
	if(root->left){
		code[cur] = 0;
		getCodeUtil(root->left,code,cur+1,out);
	}
	if(root->right){
		code[cur] = 1;
		getCodeUtil(root->right,code,cur+1,out);
	}
	if(!root->left && !root->right){
		out<<root->ch<<": ";
		cout<<root->ch<<": ";
		for(unsigned int i=0;i<cur;i++){
			out<<code[i];
			cout<<code[i];
		}
		out<<endl;
		cout<<endl;
	}
}

void getCode(struct node* root){
	vector<int>code(MAXHEIGHT);
	ofstream writer("enCoding.txt");
	getCodeUtil(root,code,0,writer);
	cout<<"Codes are written to ---enCoding.txt--"<<endl;
	fflush(stdin);
	cout<<"Press Enter to Exit..."<<endl;
	getchar();
}

void huffmanEncoding(){
	string content = getData();
	vector<int>freq = getFreq(content);
	priority_queue<struct node*,vector<struct node*>,cmp> pq;

	for(unsigned int i=0;i<ALPHASIZE;i++){
		if(freq[i]){
			pq.push(getNode(freq[i],char(i)));
		}
	}
    struct node *left,*right;
	while(true){
		left = pq.top();
		pq.pop();
		if(pq.empty())break;
		right = pq.top();
		pq.pop();
		struct node* newnode = getNode('$',left->frequency+right->frequency);
		newnode->left = left;
		newnode->right = right;
		pq.push(newnode);
	}

    getCode(left);

}

int  main()
{
	huffmanEncoding();
}
