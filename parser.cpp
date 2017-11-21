#include <fstream>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <typeinfo>
#include <cstdlib>
#include <vector>


using namespace std;
void exitWithError(const std::string &error) 
{
	std::cout << error;
	std::cin.ignore();
	std::cin.get();

	exit(EXIT_FAILURE);
}
class Convert
{
public:
	template <typename T>
	static std::string T_to_string(T const &val) 
	{
		std::ostringstream ostr;
		ostr << val;

		return ostr.str();
	}
		
	template <typename T>//=int>
	static T string_to_T(std::string const &val) 
	{
		std::istringstream istr(val);
		T returnVal;
		if (!(istr >> returnVal))
			exitWithError("CFG: Not a valid " + (std::string)typeid(T).name() + " received!\n");

		return returnVal;
	}

};



class ConfigFile
{
private:
	std::map<std::string, std::string> contents;
	std::string fName;

	
	void extractKey(std::string &key, size_t const &sepPos, const std::string &line) const
	{
		key = line.substr(0, sepPos);
		if (key.find('\t') != line.npos || key.find(' ') != line.npos)
			key.erase(key.find_first_of("\t "));
	}
	void extractValue(std::string &value, size_t const &sepPos, const std::string &line) const
	{
		value = line.substr(sepPos + 1);
		value.erase(0, value.find_first_not_of("\t "));
		value.erase(value.find_last_not_of("\t ") + 1);
	}

	void extractContents(const std::string &line) 
	{
		std::string temp = line;
		temp.erase(0, temp.find_first_not_of("\t "));
		size_t sepPos = temp.find('=');

		std::string key, value;
		extractKey(key, sepPos, temp);
		extractValue(value, sepPos, temp);

		if (!keyExists(key))
			contents.insert(std::pair<std::string, std::string>(key, value));
		else
			exitWithError("CFG: Can only have unique key names!\n");
	}

	void parseLine(const std::string &line, size_t const lineNo)
	{
		if (line.find('=') == line.npos)
			exitWithError("CFG: Couldn't find separator on line: " + Convert::T_to_string(lineNo) + "\n");

		//if (!validLine(line))
		//	exitWithError("CFG: Bad format for line: " + Convert::T_to_string(lineNo) + "\n");

		extractContents(line);
	}

	void ExtractKeys()
	{
		std::ifstream file;
		file.open(fName.c_str());
		if (!file)
			exitWithError("CFG: File " + fName + " couldn't be found!\n");

		std::string line;
		size_t lineNo = 0;
		while (std::getline(file, line))
		{
			lineNo++;
			std::string temp = line;

			if (temp.empty())
				continue;
			parseLine(temp, lineNo);
		}

		file.close();
	}
public:
	ConfigFile()
	{
		
	}
	ConfigFile(const std::string &fName)
	{
		this->fName = fName;
		ExtractKeys();
	}

	bool keyExists(const std::string &key) const
	{
		return contents.find(key) != contents.end();
	}

	template <typename ValueType>
	ValueType getValueOfKey(const std::string &key, ValueType const &defaultValue = ValueType()) const
	{
		if (!keyExists(key))
			return defaultValue;

		return Convert::string_to_T<ValueType>(contents.find(key)->second);
	}
};

int main()
{
	ConfigFile cfg("config.cfg");
	
	
	string ns_host = cfg.getValueOfKey<std::string>("host");
	std::cout << ns_host <<"\n";
	
	//~ string ns_port = cfg.getValueOfKey<std::string>("port");
	//~ std::cout << ns_port <<"\n";
	
	string ns_user = cfg.getValueOfKey<std::string>("user");
	std::cout << ns_user <<"\n";
	
	string ns_password = cfg.getValueOfKey<std::string>("password");
	std::cout << ns_password <<"\n";
	
	string m_url = cfg.getValueOfKey<std::string>("url");
	std::cout << m_url <<"\n";
	
	string test_group = cfg.getValueOfKey<std::string>("TestGroup");  
	std::cout << test_group <<"\n";
	
	string log_path = cfg.getValueOfKey<std::string>("log_path");

	string report_path = cfg.getValueOfKey<std::string>("Report_path");

	
	string test_id;
	vector<string> result;
	vector<string> m_TestRange;
	
	test_id = cfg.getValueOfKey<std::string>("TestRange");
	std::cout<<test_id<<"\n";
		
		//~ stringstream ss(test_id);
		
		//~ while(ss.good())
		//~ {
			//~ string substr;
			//~ getline(ss,substr, ',');
			//~ result.push_back(substr);
		//~ }
		//~ cout<<result.size();
	
		int pos;
		string str1,str2;
		int tmp[5];
		int i=0;
		
		
		{
		do
		{
			pos = test_id.find(',');
			if(pos == -1)
			{
				break;
			}
			str1 = test_id.substr(0, pos);
			cout<<"str1:"<<str1<<"\n";
			m_TestRange.push_back(str1);
			str2 = test_id.substr(pos+1);
			test_id = (str2);
	
		}while(1);
		m_TestRange.push_back(test_id);
		}
		
		cout<<"m_TestRange:"<<m_TestRange.size()<<"\n";
		
		
			pos = test_id.find(':');
			if(pos == -1)
			{
				//break;
			}
			str1 = test_id.substr(0, pos);			
			
			int p = str1.find('t');
		    string o1 = str1.substr(p+1);
		    stringstream geek(o1);
			int x1 = 0,x2=0;
			geek >> x1;
			cout<<"X:"<<x1<<"\n";
		
			str2 = test_id.substr(pos+1);
			 p = str2.find('t');
		    string o2 = str2.substr(p+1);
		    stringstream geek2(o2);
			geek2 >> x2;
			cout<<"X:"<<x2<<"\n";
			
			string s;
			string ap = "NS_t";
			for(int i=x1;i<=x2;i++)
			{
				ostringstream oss;
				oss << i;
				s = ap + oss.str();
				cout<<s<<"\n";
			}
				

		    
			cout<<o1<<"\n";
			cout<<o2<<"\n";
			
	cout<<"in rep\n";
	ofstream myfile;
	char* str_now;
	time_t secs_now;
	
	size_t length;
	time(&secs_now);
	str_now = ctime(&secs_now);
	length = strlen(str_now);
	str_now[length-1]=NULL;
	cout<<"LOG:"<<log_path<<"\n";
	
	cout<<"REP:"<<report_path<<"\n";
	FILE* id = popen("tail -f /var/log/nscore.log > log_path","r");

	myfile.open(report_path.c_str(), ios::out | ios::app);

		time(&secs_now);
		str_now = ctime(&secs_now);

		length = strlen(str_now);
		str_now[length-1]=NULL;
		
		
		myfile << 1 <<","<<1 <<"," <<1 <<"," <<1<<"\n";



//	myfile.open("test_report.txt", ios::out | ios::app);
	
	
		
	
}
