/* Hash function used: djb2 */

#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
unsigned long hash(unsigned char *str);
struct Key{
	std::string value;
	Key *next;
};
Key ** copyandrehash(Key *arr[], unsigned long long m);
void insert(std::string s, unsigned long index, Key *arr[]);
int main()
{
	unsigned long long m=7;
	unsigned long long n=0;
	Key **arr = new Key *[m];
	Key **temp;
	for(int i=0;i<m;i++)
	arr[i]=NULL;
	int j; int i;
	unsigned char *str; 
	std::ifstream fin("Database.txt");
	if(!fin.is_open())
	{
	
		std::cout<<"Cannot open file! Terminating...\n";
		return 1;
	}	
	std::string s;
	std::string temps;

	while(getline(fin,s))
	{	i=0;
		while(s[i])
		{	if(s[i]>='A' && s[i]<='Z' || s[i]>='0'&&s[i]<='9'||s[i]>='a' && s[i]<='z')
				temps += s[i++];
			else
			switch(s[i]) {
				case '-':
				
				case '\'':
				{	if(!temps.empty())
						temps+=s[i];
					
					
					i++;
					break;
				}
					
				default: {
					if(!temps.empty())
					{j=0;
			
			str = new unsigned char[temps.length()];
			for(j=0;j<temps.length();j++)
				str[j] = temps[j];
				str[j] = '\0';
				n++;
			if(n>m)
			{
			//std::cout<<n<<"\nrehash\n";
			
			temp = copyandrehash(arr,m);
			delete arr;	
			arr=temp;
			m *=2;
			}	
			insert(temps,hash(str)%m,arr);
			
			delete str;

					//std::cout<<temps<<"\n";	//insert
					temps.clear();
					
					}
					i++;
					break;
				}
				
					
			}			
		}
	
	}
	if(!temps.empty()){
		//std::cout<<temps<<"\n";			//insert!!
	j=0;
			
			str = new unsigned char[temps.length()];
			for(j=0;j<temps.length();j++)
				str[j] = temps[j];
				str[j] = '\0';
				n++;
			if(n>m)
			{
			//std::cout<<"\nrehash\n";
			
			temp = copyandrehash(arr,m);
			delete arr;	
			arr=temp;
			m *=2;
			}	
			insert(temps,hash(str)%m,arr);
			
			delete str;

	}
	
	
	fin.close();

	
	/*		
	Key * temp1;
	for(int i=0;i<m;i++)
	{//std::cout<<"WHAT!!!!!!\n\n";
	temp1 = arr[i];
	while(temp1!=NULL) {
		
		std::cout<<temp1->value<<"\n";
		temp1 = temp1->next;
	}
	
	
	}
	*/
	return 0;
}

Key ** copyandrehash(Key *arr[], unsigned long long m) {
	
	Key **temp= new Key *[2 * m];
	for(unsigned long long i =0;i<2*m;i++)
	temp[i]=NULL;
	
	
	unsigned int j =0;
	Key *temp1;
	Key *temp2;
	for(unsigned long long i=0;i<m;i++)
	{
	temp1 = arr[i];
	while(temp1!=NULL) {
		unsigned char *str = new unsigned char[temp1->value.length()+1];
		for(j=0;j<temp1->value.length();j++)
				str[j] = temp1->value[j];
				str[j] = '\0';
		insert(temp1->value,hash(str)%(2*m),temp);
		delete str;
		temp2 = temp1;
		temp1 = temp1->next;
		delete temp2;
	}
	
	
	}
	
	return temp;
}
void insert(std::string s, unsigned long index, Key *arr[]){
	if(arr[index] == NULL) {
	
	arr[index] = new Key;
	arr[index]->value = s;
	arr[index]->next = NULL;
	
	}
	
	else {
		Key *temp = arr[index];
		bool flag =false;
		while(temp->next!=NULL)
		{
			if(temp->value==s)
			{
				flag=true;
				break;
			}
			temp = temp->next;
		}
		if(temp->value==s)
			{
				flag=true;
				
			}
		if(flag==false){
		
		temp->next = new Key;
		temp->next->value = s;
		temp->next->next = NULL;
		}	
	
		
	}
}


unsigned long hash(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		
        return hash;
    }
