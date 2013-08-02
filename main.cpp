#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iomanip>

//using std::istream; using std::ostream;
using namespace std;

//Unit_parameter
class Unit_data
{
public:
	void set_unit(const vector<string>& unitdata);
	const double Unit_data::get_unit(const string& unitname) const;
private:
	map<string,double> unit;
};

//set Unit_parameter
void Unit_data::set_unit(const vector<string>& unitdata)
{
	int origin;
	double value;
	string name,temp;
	for(vector<string>::const_iterator iter=unitdata.begin();iter!=unitdata.end();iter++)
	{
		istringstream line(*iter);
		line>>origin;
		line>>name;
		line>>temp;
		line>>value;
		line.clear();
		unit.insert(make_pair(name,value/origin));
	}
}

const double Unit_data::get_unit(const string& unitname) const
{
	//find s,es
	string unitname_no_s(unitname);
	string unitname_no_es(unitname);
	string::const_iterator iterend=unitname.end();
	string::const_iterator iterbegin=unitname.begin();
	iterend--;
	if(*iterend=='s')
	unitname_no_s.assign(iterbegin,iterend);
	iterend--;
	if(*iterend=='e')
		unitname_no_es.assign(iterbegin,iterend);
	//change ee to oo
	string unitname_ee(unitname);
	string::size_type pos_ee;
	pos_ee=unitname.find("ee");
	if(pos_ee!=-1)
		unitname_ee.replace(pos_ee,2,2,'o');

	map<string,double>::const_iterator ite=unit.begin();
	if(unit.count(unitname))
	{
		ite=unit.find(unitname);
		return ite->second;
	}
	else if(unit.count(unitname_no_s))
	{
		ite=unit.find(unitname_no_s);
		return ite->second;
	}
	else if(unit.count(unitname_no_es))
	{
		ite=unit.find(unitname_no_es);
		return ite->second;
	}
	else if(unit.count(unitname_ee))
	{
		ite=unit.find(unitname_ee);
		return ite->second;
	}
	else 
		return 0;

}
void main(int argc, char **argv)
{
	vector<string> unitdata,data;
	vector<double> result;
	bool input_data(vector<string>& unitdata,vector<string>& data);

	double compute_data(const string& formula,const Unit_data& stored_unit);
	void show_result(const vector<double>& result);
	if(input_data(unitdata,data))
		exit(1);

	Unit_data stored_unit;

	stored_unit.set_unit(unitdata);
	
	
	string formula;
	for(vector<string>::const_iterator it=data.begin();it!=data.end();it++)
	{
		formula=*it;
		result.push_back(compute_data(formula,stored_unit));
	}
	show_result(result);
}

void show_result(const vector<double>& result)
{
	cout<<"mewtwo@sina.com"<<endl;
	cout<<endl;
	for(vector<double>::const_iterator iter_show=result.begin();iter_show!=result.end();iter_show++)
	{
		cout<<setiosflags(ios::fixed)<<setprecision(2)<<*iter_show<<" m"<<endl;
	}
}


//Computed_Data
double compute_data(const string& formula,const Unit_data& stored_unit)
{

	double value,per=0,result=0;
	string units,temp;
	bool pm=1;
	istringstream element(formula);

	while(element>>temp)
	{
		if(temp=="+")
		{
			pm=1;
			continue;
		}
		else if(temp=="-")
		{
			pm=0;
			continue;
		}
		else
		{	
			value=atof(temp.c_str());
			element>>units;
			per=stored_unit.get_unit(units);
			//per=1;
			if(pm==1)
				result+=per*value;
			else
				result-=per*value;
		}
	}
	element.clear();
	return result;
}



//Input_data
bool input_data(vector<string>& unitdata,vector<string>& data)
{
	ifstream infile;
	infile.open("input.txt");
	if(!infile)
	{
		cerr<<"Can not open file!"<<endl;
		return 1;
	}
	string temp;
	while(getline(infile,temp))
	{	
		if( temp!="" && temp.find('=')!=-1)
			unitdata.push_back(temp);
		else if(temp!="")
			data.push_back(temp);
	}
	infile.close();
	return 0;
}