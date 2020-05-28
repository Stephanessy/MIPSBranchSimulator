#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

int main (int argc, char** argv) {
	ifstream config;
	config.open(argv[1]);

	int m, k;
	config >> m >> k;
 
	config.close();

	// initial BHR
	int BHR_num = pow(2, k);
	int BHR[k] = { 0 };
	for (int i = 0; i < k; i++)
	{
		BHR[i] = 1;
	}

	// initial saturating counter
	int stg_num = pow(2, m);
	int Stgcnt[BHR_num][stg_num] = { 0 };
	for (int i = 0; i < BHR_num; i++)
	{
		for (int j = 0; j < stg_num; j++)
		{
			Stgcnt[i][j] = 3;
			//cout<<Stgcnt[i][j]<<"	";
		}
		//cout<<endl;
	}

	ofstream out;
	string out_file_name = string(argv[2]) + ".out";
	out.open(out_file_name.c_str());
	
	ifstream trace;
	trace.open(argv[2]);
	unsigned long pc; bool taken;
	trace >> std::hex >> pc >> taken;

	while (!trace.eof()) {
		bool prediction;
		//prediction = true;
		//cout<<"pc:"<<pc<<"	";

		// m LSB
		int lsb = pc & 4095;
		//cout<<"lsb:"<<lsb<<"	";

		/*cout<<"BHR:";
		for(int i = 0; i < k; i++)
		{
			cout<<BHR[i];
		}
		cout<<"	";*/

		// BHR dec
		int BHR_dec = 0;
		for (int i = k; i > 0; i--)
		{
			BHR_dec += BHR[i - 1] * pow(2, k - i);
		}
		//cout<<"BHR_dec:"<<BHR_dec<<"	";

		//cout<<"Stgcnt:"<<Stgcnt[BHR_dec][lsb]<<"      ";
		//cout<<"output:"<<taken<<"	";
		// make prediction
		if (Stgcnt[BHR_dec][lsb] == 3 || Stgcnt[BHR_dec][lsb] == 2)
		{
			prediction = true;
		}
		else
			prediction = false;
		//cout<<"		prediction:"<<prediction<<"	";

		// update saturating counter
		if (Stgcnt[BHR_dec][lsb] == 3)
		{
			if (taken == false)
			{
				Stgcnt[BHR_dec][lsb] = 2;
			}
			else
				Stgcnt[BHR_dec][lsb] = 3;
		}
		else if (Stgcnt[BHR_dec][lsb] == 2)
		{
			if (taken == true)
			{
				Stgcnt[BHR_dec][lsb] = 3;
			}
			else
				Stgcnt[BHR_dec][lsb] = 0;
		}
		else if (Stgcnt[BHR_dec][lsb] == 1)
		{
			if (taken == true)
			{
				Stgcnt[BHR_dec][lsb] = 3;
			}
			else
				Stgcnt[BHR_dec][lsb] = 0;
		}
		else if(Stgcnt[BHR_dec][lsb] == 0)
		{
			if (taken == true)
			{
				Stgcnt[BHR_dec][lsb] = 1;
			}
			else
				Stgcnt[BHR_dec][lsb] = 0;
		}
		// Stgcnt[BHR_dec][lsb] = 1;
		// cout<<"updated Stgcnt:"<<Stgcnt[BHR_dec][lsb]<<"	";

		// update BHR
		for (int i = k; i > 1; i--)
		{
			BHR[i - 1] = BHR[i - 2];
		}
		BHR[0] = taken;

		/*cout<<"updated BHR:";
		for(int i = 0; i < k; i++)
		{
			cout<<BHR[i];
		}*/
		//cout<<endl;

		out << prediction<<endl;
		trace >> std::hex >> pc >> taken;
	}
	 
	trace.close();	
	out.close();
	return 0;
}
