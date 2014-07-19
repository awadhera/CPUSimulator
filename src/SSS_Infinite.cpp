#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <cstdlib>

void renameRegister(std::vector< std::vector<int> > &allInst, std::vector< std::vector< std::map< int, std::map< int, int > > > > &renInst)
{
	std::vector< std::map< int, std::map< int, int > > > tempVec;
	std::map< int, std::map< int, int > > tempMap, tempMap1, tempMap2, tempMap3;
	tempMap[allInst[0][0]].insert(std::make_pair(0, 0));
	tempVec.push_back(tempMap);
	tempMap.clear();
	tempMap[allInst[0][1]].insert(std::make_pair(0, 0));
	tempVec.push_back(tempMap);
	tempMap.clear();
	tempMap[allInst[0][2]].insert(std::make_pair(0, 0));
	tempVec.push_back(tempMap);
	tempMap.clear();
	renInst.push_back(tempVec);
	tempVec.clear();
	std::vector< std::map< int, std::map< int, int > > >::iterator it, tIt1, tIt2, tIt3;
	std::map< int, std::map< int, int > > tm1, tm2, tm3;
	int k = 0;
	int s1set, s2set, dset, tempVal1, tempVal2;
	for (unsigned int i = 1; i < allInst.size(); ++i)
	{
		s1set = 0;
		s2set = 0;
		dset = 0;
		tempVal1 = 0;
		tempVal2 = 0;
		for (int j = i - 1; j >= 0; j--)
		{
			k = 0;
			tm1.clear();
			tm2.clear();
			tm3.clear();
			for (it = renInst[j].begin(); it != renInst[j].end(); ++it)
			{
				if (k == 0)
				{
					tm1 = *it;
				}
				else if (k == 1)
				{
					tm2 = *it;
				}
				else if (k == 2)
				{
					tm3 = *it;
				}
				k++;
			}
			if (!s1set)
			{
				if (allInst[i][1] == allInst[j][0])
				{
					tempMap1[allInst[i][1]].insert(std::make_pair(tm1[allInst[j][0]].rbegin()->first, 0));
					tempVal1 = tm1[allInst[j][0]].rbegin()->first;
					s1set = 1;
				}
			}
			if (!s2set)
			{
				if (allInst[i][2] == allInst[j][0])
				{
					tempMap2[allInst[i][2]].insert(std::make_pair(tm1[allInst[j][0]].rbegin()->first, 0));
					tempVal2 = tm1[allInst[j][0]].rbegin()->first;
					s2set = 1;
				}
			}
			if (allInst[i][0] != allInst[i][1] && allInst[i][0] != allInst[i][2])
			{
				if (!dset)
				{
					if (allInst[i][0] == allInst[j][0])
					{
						tempMap3[allInst[i][0]].insert(std::make_pair((tm1[allInst[j][0]].rbegin()->first) + 1, 0));
						dset = 1;
					}
					else if (allInst[i][0] == allInst[j][1])
					{
						tempMap3[allInst[i][0]].insert(std::make_pair((tm2[allInst[j][1]].rbegin()->first) + 1, 0));
						dset = 1;
					}
					else if (allInst[i][0] == allInst[j][2])
					{
						tempMap3[allInst[i][0]].insert(std::make_pair((tm3[allInst[j][2]].rbegin()->first) + 1, 0));
						dset = 1;
					}
				}
			}
		}
		if (!s1set)
		{
			tempMap1[allInst[i][1]].insert(std::make_pair(0, 0));
			tempVal1 = 0;
			s1set = 1;
		}
		if (!s2set)
		{
			tempMap2[allInst[i][2]].insert(std::make_pair(0, 0));
			tempVal2 = 0;
			s2set = 1;
		}
		if (!dset)
		{
			if (allInst[i][0] == allInst[i][1])
			{
				tempMap3[allInst[i][0]].insert(std::make_pair(tempVal1 + 1, 0));
				dset = 1;
			}
			else if (allInst[i][0] == allInst[i][2])
			{
				tempMap3[allInst[i][0]].insert(std::make_pair(tempVal2 + 1, 0));
				dset = 1;
			}
			else
			{
				tempMap3[allInst[i][0]].insert(std::make_pair(0, 0));
				dset = 1;
			}
		}
		tempVec.push_back(tempMap3);
		tempMap3.clear();
		tempVec.push_back(tempMap1);
		tempMap1.clear();
		tempVec.push_back(tempMap2);
		tempMap2.clear();
		renInst.push_back(tempVec);
		tempVec.clear();
	}
}

void instParse(std::vector< std::vector< std::map< int, std::map< int, int > > > > &renInst, std::vector< std::vector<int> > &allInst, std::map<int, int> &instMap, std::map<int, int> &prs)
{
	int dep = 0;
	for (unsigned int i = 0; i < renInst.size(); ++i)
	{
		if (instMap[i] == 0)
		{
			dep = 0;
			for (int j = i - 1; j >= 0; j--)
			{
				if (((renInst[i][1].rbegin()->first == renInst[j][0].rbegin()->first)
					&& (renInst[i][1].rbegin()->second.rbegin()->first == renInst[j][0].rbegin()->second.rbegin()->first))
					|| ((renInst[i][2].rbegin()->first == renInst[j][0].rbegin()->first)
					&& (renInst[i][2].rbegin()->second.rbegin()->first == renInst[j][0].rbegin()->second.rbegin()->first)))
				{
					if (renInst[j][0].rbegin()->second.rbegin()->second == 0)
					{
						dep = 1;
						break;
					}
				}
			}
			if (!dep)
			{
				instMap[i] = 1;
				prs[i] = allInst[i][3];
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int numArg = 1;
	if ((argc - 1) != numArg)
	{
		std::cout << "Wrong number of arguments...Exiting\n";
		std::exit(0);
	}
	std::cout << "Evaluating, please wait...\n";
	char *filename = argv[1];
	std::string inst;
	std::vector< std::vector<int> > allInst;
	std::ifstream infile(filename);
	int totCycles = 0;
	std::map<int, int> prs;
	int instCount = 0;
	std::map<int, int> instMap;
	int reg[10] = { 0 };
	int compInst = 0;
	std::map< int, std::map<int, int> > renRegMap;
	std::vector< std::vector< std::map< int, std::map< int, int > > > > renInst;
	if (infile.is_open())
	{
		while (infile >> inst)
		{
			int t1, t2, t3, t4;
			char e1, c1, c2;
			std::vector<int> tempVec;
			std::istringstream ss(inst);
			ss >> t1;
			ss >> e1;
			ss >> t2;
			ss >> c1;
			ss >> t3;
			ss >> c2;
			ss >> t4;
			ss.clear();
			tempVec.push_back(t1);
			tempVec.push_back(t2);
			tempVec.push_back(t3);
			tempVec.push_back(t4);
			allInst.push_back(tempVec);
			++instCount;
		}
		infile.close();
	}
	for (unsigned int i = 0; i < allInst.size(); ++i)
	{
		instMap[i] = 0;
	}
	renameRegister(allInst, renInst);
	do
	{
		instParse(renInst, allInst, instMap, prs);
		for (std::map<int, int>::iterator it = prs.begin(); it != prs.end();)
		{
			(it->second)--;
			if ((it->second) == 0)
			{
				renInst[it->first][0].rbegin()->second.rbegin()->second = 1;
				prs.erase(it++);
				++compInst;
			}
			else
			{
				++it;
			}
		}
		totCycles++;
	} while (compInst!=instCount);
	std::cout << "Total Cycles: " << totCycles << "\n";
	return 0;
}

