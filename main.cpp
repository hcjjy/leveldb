#include <assert.h>
#include <string.h>
#include <leveldb/db.h>
#include <iostream>

//#include<vector>
//#include <memory>

class Compare
{
public:
	int operator() (int a,int b)
	{
		if (a > b)
			return 1;
		else if( a == b)
			return 0;
		else
			return -1;
	}
};
template<typename Key,class Com>
class Clist
{
public:
	bool Equal(const Key& a,const Key& b){return com(a,b) == 0;}
private:
	Com com;
};
int main(int argc,char** argv){

	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options,"/tmp/testdb", &db);
	assert(status.ok());

	//write key1,value1
	std::string key="key";
	std::string value = "value";


	status = db->Put(leveldb::WriteOptions(), key,value);
	assert(status.ok());

	status = db->Get(leveldb::ReadOptions(), key, &value);
	assert(status.ok());
	std::cout<<value<<std::endl;
	std::string key2 = "key2";

	//move the value under key to key2

	status = db->Put(leveldb::WriteOptions(),key2,value);
	assert(status.ok());
	status = db->Delete(leveldb::WriteOptions(), key);

	assert(status.ok());

	status = db->Get(leveldb::ReadOptions(),key2, &value);

	assert(status.ok());
	std::cout<<key2<<"==="<<value<<std::endl;

	status = db->Get(leveldb::ReadOptions(),key, &value);

	if(!status.ok()) std::cerr<<key<<"  "<<status.ToString()<<std::endl;
	else std::cout<<key<<"="<<value<<std::endl;

	delete db;

	Clist<int,Compare> list;
	std::cout<<list.Equal(1,2)<<std::endl;

	/*std::vector<std::tr1::shared_ptr<int> > a;
	a.push_back(std::tr1::make_shared<int>(10,'9'));
	std::vector<std::tr1::shared_ptr<int> >::iterator iter = a.begin();
	int* p1 = iter->get();
	int* p2 = (*iter).get();
	if (p1 == p2)
	{
		std::cout<<"equal!!\n";
	}*/

	system("pause");
	return 0;
}
